#include "Websockets/WebsocketClient.h"

namespace Nanometro {
    bool WebsocketClient::send(const std::string &message) {
        if (!pool && !isConnected() && !message.empty())
            return false;

        asio::post(*pool, std::bind(&WebsocketClient::post_string, this, message));
        return true;
    }

    bool WebsocketClient::send_buffer(const std::vector<std::byte> &buffer) {
        if (!pool && !isConnected() && !buffer.empty())
            return false;

        asio::post(*pool, std::bind(&WebsocketClient::post_buffer, this, EOpcode::BINARY_FRAME, buffer));
        return true;
    }

    bool WebsocketClient::send_ping() {
        if (!pool && !isConnected())
            return false;

        std::vector<std::byte> ping_buffer;
        ping_buffer.push_back(std::byte('\0'));
        asio::post(*pool, std::bind(&WebsocketClient::post_buffer, this, EOpcode::PING, ping_buffer));
        return true;
    }

    bool WebsocketClient::async_read() {
        if (!isConnected())
            return false;

        asio::async_read(tcp.socket, response_buffer, asio::transfer_at_least(2),
                         std::bind(&WebsocketClient::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred)
        );
        return true;
    }

    bool WebsocketClient::connect() {
        if (!pool && isConnected())
            return false;

        asio::post(*pool, std::bind(&WebsocketClient::run_context_thread, this));
        return true;
    }

    void WebsocketClient::post_string(const std::string &str) {
        mutexBuffer.lock();
        sDataFrame.opcode = EOpcode::TEXT_FRAME;
        package_string(str);
        mutexBuffer.unlock();
    }

    void WebsocketClient::post_buffer(EOpcode opcode, const std::vector<std::byte> &buffer) {
        mutexBuffer.lock();
        sDataFrame.opcode = opcode;
        if (opcode == EOpcode::BINARY_FRAME) {
            package_buffer(buffer);
        } else if (opcode == EOpcode::PING || opcode == EOpcode::PONG) {
            std::vector<std::byte> p_buffer = buffer;
            encode_buffer_payload(p_buffer);
            asio::async_write(tcp.socket, asio::buffer(p_buffer.data(), p_buffer.size()),
                              std::bind(&WebsocketClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred));
        }
        mutexBuffer.unlock();
    }

    void WebsocketClient::package_string(const std::string &str) {
        std::string payload;
        if (!splitBuffer || str.size() + get_frame_encode_size(str.size()) <= maxSendBufferSize) {
            sDataFrame.fin = true;
            payload = encode_string_payload(str);
            asio::async_write(tcp.socket, asio::buffer(payload.data(), payload.size()),
                              std::bind(&WebsocketClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            return;
        }

        sDataFrame.fin = true;
        size_t string_offset = 0;
        const size_t max_size = maxSendBufferSize - get_frame_encode_size(str.size());
        while (string_offset < str.size()) {
            sDataFrame.fin = string_offset < str.size();
            size_t package_size = std::min(max_size, str.size() - string_offset);
            payload.assign(str.begin() + string_offset, str.begin() + string_offset + package_size);
            payload = encode_string_payload(payload);
            asio::async_write(tcp.socket, asio::buffer(payload, payload.size()),
                              std::bind(&WebsocketClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            string_offset += package_size;
            if (sDataFrame.opcode != EOpcode::FRAME_CON) sDataFrame.opcode = EOpcode::FRAME_CON;
        }
    }

    std::string WebsocketClient::encode_string_payload(const std::string &payload) {
        std::string string_buffer;
        uint64_t payload_length = payload.size();

        // FIN, RSV, Opcode
        uint8_t byte1 = sDataFrame.fin ? 0x80 : 0x00;
        byte1 |= sDataFrame.rsv1 ? (uint8_t) ERSV::RSV1 : 0x00;
        byte1 |= sDataFrame.rsv2 ? (uint8_t) ERSV::RSV2 : 0x00;
        byte1 |= sDataFrame.rsv3 ? (uint8_t) ERSV::RSV3 : 0x00;
        byte1 |= (uint8_t) sDataFrame.opcode & 0x0F;
        string_buffer.push_back(byte1);

        // Mask and payload size
        uint8_t byte2 = sDataFrame.mask ? 0x80 : 0x00;
        if (payload_length <= 125) {
            byte2 |= payload_length;
            string_buffer.push_back(byte2);
        } else if (payload_length <= 65535) {
            byte2 |= 126;
            string_buffer.push_back(byte2);
            string_buffer.push_back((payload_length >> 8) & 0xFF);
            string_buffer.push_back(payload_length & 0xFF);
        } else {
            byte2 |= 127;
            string_buffer.push_back(byte2);
            for (int i = 7; i >= 0; --i) {
                string_buffer.push_back((payload_length >> (8 * i)) & 0xFF);
            }
        }

        std::array<std::byte, 4> masking_key;
        if (sDataFrame.mask) {
            masking_key = mask_gen();
            for (std::byte key: masking_key) string_buffer.push_back(static_cast<uint8_t>(key));
        }

        // payload data and mask
        for (size_t i = 0; i < payload.size(); ++i) {
            if (sDataFrame.mask) {
                string_buffer.push_back(payload[i] ^ static_cast<uint8_t>(masking_key[i % 4]));
            } else {
                string_buffer.push_back(payload[i]);
            }
        }

        return string_buffer;
    }

    void WebsocketClient::package_buffer(const std::vector<std::byte> &buffer) {
        std::vector<std::byte> payload;
        if (!splitBuffer || buffer.size() + get_frame_encode_size(buffer.size()) <= maxSendBufferSize) {
            sDataFrame.fin = true;
            payload = encode_buffer_payload(buffer);
            asio::async_write(tcp.socket, asio::buffer(payload.data(), payload.size()),
                              std::bind(&WebsocketClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            return;
        }

        sDataFrame.fin = false;
        size_t buffer_offset = 0;
        const size_t max_size = maxSendBufferSize - get_frame_encode_size(buffer.size());
        while (buffer_offset < buffer.size()) {
            sDataFrame.fin = buffer_offset < buffer.size();
            size_t package_size = std::min(max_size, buffer.size() - buffer_offset);
            payload.assign(buffer.begin() + buffer_offset, buffer.begin() + buffer_offset + package_size);
            encode_buffer_payload(payload);
            asio::async_write(tcp.socket, asio::buffer(payload, payload.size()),
                              std::bind(&WebsocketClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            buffer_offset += package_size;
            if (sDataFrame.opcode != EOpcode::FRAME_CON) sDataFrame.opcode = EOpcode::FRAME_CON;
        }
    }

    std::vector<std::byte> WebsocketClient::encode_buffer_payload(const std::vector<std::byte> &payload) {
        std::vector<std::byte> buffer;
        uint64_t payload_length = payload.size();

        // FIN, RSV, Opcode
        std::byte byte1 = std::byte(sDataFrame.fin ? 0x80 : 0x00);
        byte1 |= std::byte(sDataFrame.rsv1 ? (uint8_t) ERSV::RSV1 : 0x00);
        byte1 |= std::byte(sDataFrame.rsv2 ? (uint8_t) ERSV::RSV2 : 0x00);
        byte1 |= std::byte(sDataFrame.rsv3 ? (uint8_t) ERSV::RSV3 : 0x00);
        byte1 |= std::byte((uint8_t) sDataFrame.opcode & 0x0F);
        buffer.push_back(byte1);

        // Mask and payload size
        std::byte byte2 = std::byte(sDataFrame.mask ? 0x80 : 0x00);
        if (payload_length <= 125) {
            byte2 |= std::byte(payload_length);
            buffer.push_back(byte2);
        } else if (payload_length <= 65535) {
            byte2 |= std::byte(126);
            buffer.push_back(byte2);
            buffer.push_back(std::byte((payload_length >> 8) & 0xFF));
            buffer.push_back(std::byte(payload_length & 0xFF));
        } else {
            byte2 |= std::byte(127);
            buffer.push_back(byte2);
            for (int i = 7; i >= 0; --i) {
                buffer.push_back(std::byte((payload_length >> (8 * i)) & 0xFF));
            }
        }

        std::array<std::byte, 4> masking_key;
        if (sDataFrame.mask) {
            masking_key = mask_gen();
            for (std::byte key: masking_key) buffer.push_back(key);
        }

        // payload data and mask
        for (size_t i = 0; i < payload.size(); ++i) {
            if (sDataFrame.mask) {
                buffer.push_back(payload[i] ^ masking_key[i % 4]);
            } else {
                buffer.push_back(payload[i]);
            }
        }

        return buffer;
    }

    size_t WebsocketClient::get_frame_encode_size(const size_t buffer_size) {
        size_t size = 2;
        if (buffer_size <= 125) {
            size += 0;
        } else if (buffer_size <= 65535) {
            size += 2;
        } else {
            size += 8;
        }

        if (sDataFrame.mask) size += 4;

        return size;
    }

    std::array<std::byte, 4> WebsocketClient::mask_gen() {
        std::array<std::byte, 4> maskKey;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        for (std::byte &byte: maskKey) {
            byte = std::byte(dis(gen));
        }

        return maskKey;
    }

    bool WebsocketClient::decode_payload(FWsMessage &data_frame) {
        if (asio::buffer_size(response_buffer.data()) < 2) return false;

        size_t size = asio::buffer_size(response_buffer.data());
        std::vector<std::byte> encoded_buffer;
        encoded_buffer.resize(size);
        asio::buffer_copy(asio::buffer(encoded_buffer, encoded_buffer.size()), response_buffer.data());

        size_t pos = 0;
        // FIN, RSV, Opcode
        std::byte byte1 = encoded_buffer[pos++];
        data_frame.data_frame.fin = (uint8_t) byte1 & 0x80;
        data_frame.data_frame.rsv1 = (uint8_t) byte1 & 0x80;
        data_frame.data_frame.rsv2 = (uint8_t) byte1 & 0x40;
        data_frame.data_frame.rsv3 = (uint8_t) byte1 & 0x10;
        data_frame.data_frame.opcode = (EOpcode) ((uint8_t) byte1 & 0x0F);

        // Mask and payload length
        std::byte byte2 = encoded_buffer[pos++];
        data_frame.data_frame.mask = (uint8_t) byte2 & 0x80;
        uint64_t payload_length = (uint8_t) byte2 & 0x7F;
        if (payload_length == 126) {
            if (encoded_buffer.size() < pos + 2) return false;
            payload_length = static_cast<uint64_t>((encoded_buffer[pos] << 8) | encoded_buffer[pos + 1]);
            pos += 2;
        } else if (payload_length == 127) {
            if (encoded_buffer.size() < pos + 8) return false;
            payload_length = 0;
            for (int i = 0; i < 8; ++i) {
                payload_length = static_cast<uint64_t>((std::byte(payload_length) << 8) | encoded_buffer[pos + i]);
            }
            pos += 8;
        }
        data_frame.data_frame.length = payload_length;

        // Masking key
        if (data_frame.data_frame.mask) {
            if (encoded_buffer.size() < pos + 4) return false;
            for (int i = 0; i < 4; ++i) {
                data_frame.data_frame.masking_key[i] = encoded_buffer[pos++];
            }
        }

        // Payload data
        if (encoded_buffer.size() < pos + payload_length) return false;
        data_frame.payload.reserve(payload_length);
        for (size_t i = 0; i < payload_length; ++i) {
            data_frame.payload.push_back(encoded_buffer[pos++]);
            if (data_frame.data_frame.mask) {
                data_frame.payload[i] ^= data_frame.data_frame.masking_key[i % 4];
            }
        }

        return true;
    }

    void WebsocketClient::run_context_thread() {
        mutexIO.lock();
        while (tcp.attemps_fail <= maxAttemp) {
            if (onConnectionRetry && tcp.attemps_fail > 0)
                onConnectionRetry(tcp.attemps_fail);
            tcp.error_code.clear();
            tcp.context.restart();
            tcp.resolver.async_resolve(host, service,
                                       std::bind(&WebsocketClient::resolve, this, asio::placeholders::error,
                                                 asio::placeholders::endpoint));
            tcp.context.run();
            if (!tcp.error_code) break;
            tcp.attemps_fail++;
            std::this_thread::sleep_for(std::chrono::seconds(timeout));
        }
        consume_response_buffer();
        tcp.attemps_fail = 0;
        mutexIO.unlock();
    }

    void WebsocketClient::resolve(const std::error_code &error,
                                  const asio::ip::tcp::resolver::results_type &endpoints) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }

        // Attempt a connection to each endpoint in the list until we
        // successfully establish a connection.
        tcp.endpoints = endpoints;

        asio::async_connect(tcp.socket, tcp.endpoints,
                            std::bind(&WebsocketClient::conn, this, asio::placeholders::error)
        );
    }

    void WebsocketClient::conn(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }

        // The connection was successful;
        std::string request;
        request = "GET /" + handshake.path + " HTTP/" + handshake.version + "\r\n";
        request += "Host: " + host + "\r\n";
        request += "Upgrade: websocket\r\n";
        request += "Connection: Upgrade\r\n";
        request += "Sec-WebSocket-Key: " + handshake.Sec_WebSocket_Key + "\r\n";
        request += "Origin: " + handshake.origin + "\r\n";
        request += "Sec-WebSocket-Protocol: " + handshake.Sec_WebSocket_Protocol + "\r\n";
        request += "Sec-WebSocket-Version: " + handshake.Sec_Websocket_Version + "\r\n";
        request += "\r\n";
        std::ostream request_stream(&request_buffer);
        request_stream << request;
        asio::async_write(tcp.socket, request_buffer,
                          std::bind(&WebsocketClient::write_handshake, this, asio::placeholders::error,
                                    asio::placeholders::bytes_transferred)
        );
    }

    void WebsocketClient::write_handshake(const std::error_code &error, const std::size_t bytes_sent) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Read the response status line. The response_ streambuf will
        // automatically grow to accommodate the entire line. The growth may be
        // limited by passing a maximum size to the streambuf constructor.
        asio::async_read_until(tcp.socket, response_buffer, "\r\n",
                               std::bind(&WebsocketClient::read_handshake, this, asio::placeholders::error,
                                         bytes_sent, asio::placeholders::bytes_transferred)
        );
    }

    void WebsocketClient::read_handshake(const std::error_code &error, const std::size_t bytes_sent,
                                         const std::size_t bytes_recvd) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Check that response is OK.
        std::istream response_stream(&response_buffer);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            if (onError)
                onError(-1, "Invalid response.");
            close();
            return;
        }
        if (status_code != 101) {
            if (onError)
                onError(status_code, "Invalid status code.");
            close();
            return;
        }

        asio::async_read_until(tcp.socket, response_buffer, "\r\n\r\n",
                               std::bind(&WebsocketClient::consume_header_buffer, this, asio::placeholders::error)
        );
    }

    void WebsocketClient::consume_header_buffer(const std::error_code &error) {
        consume_response_buffer();
        asio::async_read(tcp.socket, response_buffer, asio::transfer_at_least(1),
                         std::bind(&WebsocketClient::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred));

        // The connection was successful
        if (onConnected)
            onConnected();
    }

    void WebsocketClient::write(const std::error_code &error, const std::size_t bytes_sent) {
        if (error) {
            if (onError)
                onError(error.value(), error.message());

            return;
        }

        if (onMessageSent)
            onMessageSent(bytes_sent);
    }

    void WebsocketClient::read(const std::error_code &error, const size_t bytes_recvd) {
        if (error) {
            if (onError)
                onError(error.value(), error.message());
            return;
        }

        FWsMessage rDataFrame;
        if (!decode_payload(rDataFrame)) {
            response_buffer.consume(response_buffer.size());
            asio::async_read(tcp.socket, response_buffer, asio::transfer_at_least(1),
                             std::bind(&WebsocketClient::read, this, asio::placeholders::error,
                                       asio::placeholders::bytes_transferred)
            );
            return;
        }


        if (rDataFrame.data_frame.opcode == EOpcode::PING) {
            std::vector<std::byte> pong_buffer;
            pong_buffer.resize(1);
            if (pong_buffer.back() != std::byte('\0'))
                pong_buffer.push_back(std::byte('\0'));
            post_buffer(EOpcode::PONG, pong_buffer);
        } else if (rDataFrame.data_frame.opcode == EOpcode::PONG) {
            if (onPongReceived)
                onPongReceived();
        } else if (rDataFrame.data_frame.opcode == EOpcode::CONNECTION_CLOSE) {
            if (onCloseNotify)
                onCloseNotify();
        } else {
            if (onMessageReceived)
                onMessageReceived(bytes_recvd, rDataFrame);
        }

        consume_response_buffer();
        asio::async_read(tcp.socket, response_buffer, asio::transfer_at_least(1),
                         std::bind(&WebsocketClient::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred)
        );
    }

    bool WebsocketClientSsl::send(const std::string &message) {
        if (!pool && !isConnected() && !message.empty())
            return false;

        asio::post(*pool, std::bind(&WebsocketClientSsl::post_string, this, message));
        return true;
    }

    bool WebsocketClientSsl::send_buffer(const std::vector<std::byte> &buffer) {
        if (!pool && !isConnected() && !buffer.empty())
            return false;

        asio::post(*pool, std::bind(&WebsocketClientSsl::post_buffer, this, EOpcode::BINARY_FRAME, buffer));
        return true;
    }

    bool WebsocketClientSsl::send_ping() {
        if (!pool && !isConnected())
            return false;

        std::vector<std::byte> ping_buffer;
        ping_buffer.push_back(std::byte('\0'));
        asio::post(*pool, std::bind(&WebsocketClientSsl::post_buffer, this, EOpcode::PING, ping_buffer));
        return true;
    }

    bool WebsocketClientSsl::async_read() {
        if (!isConnected())
            return false;

        asio::async_read(tcp.ssl_socket, response_buffer, asio::transfer_at_least(2),
                         std::bind(&WebsocketClientSsl::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred)
        );
        return true;
    }

    bool WebsocketClientSsl::connect() {
        if (!pool && isConnected())
            return false;

        asio::post(*pool, std::bind(&WebsocketClientSsl::run_context_thread, this));
        return true;
    }

    void WebsocketClientSsl::post_string(const std::string &str) {
        mutexBuffer.lock();
        sDataFrame.opcode = EOpcode::TEXT_FRAME;
        package_string(str);
        mutexBuffer.unlock();
    }

    void WebsocketClientSsl::post_buffer(EOpcode opcode, const std::vector<std::byte> &buffer) {
        mutexBuffer.lock();
        sDataFrame.opcode = opcode;
        if (opcode == EOpcode::BINARY_FRAME) {
            package_buffer(buffer);
        } else if (opcode == EOpcode::PING || opcode == EOpcode::PONG) {
            std::vector<std::byte> p_buffer = buffer;
            encode_buffer_payload(p_buffer);
            asio::async_write(tcp.ssl_socket, asio::buffer(p_buffer.data(), p_buffer.size()),
                              std::bind(&WebsocketClientSsl::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred));
        }
        mutexBuffer.unlock();
    }

    void WebsocketClientSsl::package_string(const std::string &str) {
        std::string payload;
        if (!splitBuffer || str.size() + get_frame_encode_size(str.size()) <= maxSendBufferSize) {
            sDataFrame.fin = true;
            payload = encode_string_payload(str);
            asio::async_write(tcp.ssl_socket, asio::buffer(payload.data(), payload.size()),
                              std::bind(&WebsocketClientSsl::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            return;
        }

        sDataFrame.fin = true;
        size_t string_offset = 0;
        const size_t max_size = maxSendBufferSize - get_frame_encode_size(str.size());
        while (string_offset < str.size()) {
            sDataFrame.fin = string_offset < str.size();
            size_t package_size = std::min(max_size, str.size() - string_offset);
            payload.assign(str.begin() + string_offset, str.begin() + string_offset + package_size);
            payload = encode_string_payload(payload);
            asio::async_write(tcp.ssl_socket, asio::buffer(payload, payload.size()),
                              std::bind(&WebsocketClientSsl::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            string_offset += package_size;
            if (sDataFrame.opcode != EOpcode::FRAME_CON) sDataFrame.opcode = EOpcode::FRAME_CON;
        }
    }

    std::string WebsocketClientSsl::encode_string_payload(const std::string &payload) {
        std::string string_buffer;
        uint64_t payload_length = payload.size();

        // FIN, RSV, Opcode
        uint8_t byte1 = sDataFrame.fin ? 0x80 : 0x00;
        byte1 |= sDataFrame.rsv1 ? (uint8_t) ERSV::RSV1 : 0x00;
        byte1 |= sDataFrame.rsv2 ? (uint8_t) ERSV::RSV2 : 0x00;
        byte1 |= sDataFrame.rsv3 ? (uint8_t) ERSV::RSV3 : 0x00;
        byte1 |= (uint8_t) sDataFrame.opcode & 0x0F;
        string_buffer.push_back(byte1);

        // Mask and payload size
        uint8_t byte2 = sDataFrame.mask ? 0x80 : 0x00;
        if (payload_length <= 125) {
            byte2 |= payload_length;
            string_buffer.push_back(byte2);
        } else if (payload_length <= 65535) {
            byte2 |= 126;
            string_buffer.push_back(byte2);
            string_buffer.push_back((payload_length >> 8) & 0xFF);
            string_buffer.push_back(payload_length & 0xFF);
        } else {
            byte2 |= 127;
            string_buffer.push_back(byte2);
            for (int i = 7; i >= 0; --i) {
                string_buffer.push_back((payload_length >> (8 * i)) & 0xFF);
            }
        }

        std::array<std::byte, 4> masking_key;
        if (sDataFrame.mask) {
            masking_key = mask_gen();
            for (std::byte key: masking_key) string_buffer.push_back(static_cast<uint8_t>(key));
        }

        // payload data and mask
        for (size_t i = 0; i < payload.size(); ++i) {
            if (sDataFrame.mask) {
                string_buffer.push_back(payload[i] ^ static_cast<uint8_t>(masking_key[i % 4]));
            } else {
                string_buffer.push_back(payload[i]);
            }
        }

        return string_buffer;
    }

    void WebsocketClientSsl::package_buffer(const std::vector<std::byte> &buffer) {
        std::vector<std::byte> payload;
        if (!splitBuffer || buffer.size() + get_frame_encode_size(buffer.size()) <= maxSendBufferSize) {
            sDataFrame.fin = true;
            payload = encode_buffer_payload(buffer);
            asio::async_write(tcp.ssl_socket, asio::buffer(payload.data(), payload.size()),
                              std::bind(&WebsocketClientSsl::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            return;
        }

        sDataFrame.fin = false;
        size_t buffer_offset = 0;
        const size_t max_size = maxSendBufferSize - get_frame_encode_size(buffer.size());
        while (buffer_offset < buffer.size()) {
            sDataFrame.fin = buffer_offset < buffer.size();
            size_t package_size = std::min(max_size, buffer.size() - buffer_offset);
            payload.assign(buffer.begin() + buffer_offset, buffer.begin() + buffer_offset + package_size);
            encode_buffer_payload(payload);
            asio::async_write(tcp.ssl_socket, asio::buffer(payload, payload.size()),
                              std::bind(&WebsocketClientSsl::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            buffer_offset += package_size;
            if (sDataFrame.opcode != EOpcode::FRAME_CON) sDataFrame.opcode = EOpcode::FRAME_CON;
        }
    }

    std::vector<std::byte> WebsocketClientSsl::encode_buffer_payload(const std::vector<std::byte> &payload) {
        std::vector<std::byte> buffer;
        uint64_t payload_length = payload.size();

        // FIN, RSV, Opcode
        std::byte byte1 = std::byte(sDataFrame.fin ? 0x80 : 0x00);
        byte1 |= std::byte(sDataFrame.rsv1 ? (uint8_t) ERSV::RSV1 : 0x00);
        byte1 |= std::byte(sDataFrame.rsv2 ? (uint8_t) ERSV::RSV2 : 0x00);
        byte1 |= std::byte(sDataFrame.rsv3 ? (uint8_t) ERSV::RSV3 : 0x00);
        byte1 |= std::byte((uint8_t) sDataFrame.opcode & 0x0F);
        buffer.push_back(byte1);

        // Mask and payload size
        std::byte byte2 = std::byte(sDataFrame.mask ? 0x80 : 0x00);
        if (payload_length <= 125) {
            byte2 |= std::byte(payload_length);
            buffer.push_back(byte2);
        } else if (payload_length <= 65535) {
            byte2 |= std::byte(126);
            buffer.push_back(byte2);
            buffer.push_back(std::byte((payload_length >> 8) & 0xFF));
            buffer.push_back(std::byte(payload_length & 0xFF));
        } else {
            byte2 |= std::byte(127);
            buffer.push_back(byte2);
            for (int i = 7; i >= 0; --i) {
                buffer.push_back(std::byte((payload_length >> (8 * i)) & 0xFF));
            }
        }

        std::array<std::byte, 4> masking_key;
        if (sDataFrame.mask) {
            masking_key = mask_gen();
            for (std::byte key: masking_key) buffer.push_back(key);
        }

        // payload data and mask
        for (size_t i = 0; i < payload.size(); ++i) {
            if (sDataFrame.mask) {
                buffer.push_back(payload[i] ^ masking_key[i % 4]);
            } else {
                buffer.push_back(payload[i]);
            }
        }

        return buffer;
    }

    size_t WebsocketClientSsl::get_frame_encode_size(const size_t buffer_size) {
        size_t size = 2;
        if (buffer_size <= 125) {
            size += 0;
        } else if (buffer_size <= 65535) {
            size += 2;
        } else {
            size += 8;
        }

        if (sDataFrame.mask) size += 4;

        return size;
    }

    std::array<std::byte, 4> WebsocketClientSsl::mask_gen() {
        std::array<std::byte, 4> maskKey;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 255);

        for (std::byte &byte: maskKey) {
            byte = std::byte(dis(gen));
        }

        return maskKey;
    }

    bool WebsocketClientSsl::decode_payload(FWsMessage &data_frame) {
        if (asio::buffer_size(response_buffer.data()) < 2) return false;

        size_t size = asio::buffer_size(response_buffer.data());
        std::vector<std::byte> encoded_buffer;
        encoded_buffer.resize(size);
        asio::buffer_copy(asio::buffer(encoded_buffer, encoded_buffer.size()), response_buffer.data());

        size_t pos = 0;
        // FIN, RSV, Opcode
        std::byte byte1 = encoded_buffer[pos++];
        data_frame.data_frame.fin = (uint8_t) byte1 & 0x80;
        data_frame.data_frame.rsv1 = (uint8_t) byte1 & 0x80;
        data_frame.data_frame.rsv2 = (uint8_t) byte1 & 0x40;
        data_frame.data_frame.rsv3 = (uint8_t) byte1 & 0x10;
        data_frame.data_frame.opcode = (EOpcode) ((uint8_t) byte1 & 0x0F);

        // Mask and payload length
        std::byte byte2 = encoded_buffer[pos++];
        data_frame.data_frame.mask = (uint8_t) byte2 & 0x80;
        uint64_t payload_length = (uint8_t) byte2 & 0x7F;
        if (payload_length == 126) {
            if (encoded_buffer.size() < pos + 2) return false;
            payload_length = static_cast<uint64_t>((encoded_buffer[pos] << 8) | encoded_buffer[pos + 1]);
            pos += 2;
        } else if (payload_length == 127) {
            if (encoded_buffer.size() < pos + 8) return false;
            payload_length = 0;
            for (int i = 0; i < 8; ++i) {
                payload_length = static_cast<uint64_t>((std::byte(payload_length) << 8) | encoded_buffer[pos + i]);
            }
            pos += 8;
        }
        data_frame.data_frame.length = payload_length;

        // Masking key
        if (data_frame.data_frame.mask) {
            if (encoded_buffer.size() < pos + 4) return false;
            for (int i = 0; i < 4; ++i) {
                data_frame.data_frame.masking_key[i] = encoded_buffer[pos++];
            }
        }

        // Payload data
        if (encoded_buffer.size() < pos + payload_length) return false;
        data_frame.payload.reserve(payload_length);
        for (size_t i = 0; i < payload_length; ++i) {
            data_frame.payload.push_back(encoded_buffer[pos++]);
            if (data_frame.data_frame.mask) {
                data_frame.payload[i] ^= data_frame.data_frame.masking_key[i % 4];
            }
        }

        return true;
    }

    void WebsocketClientSsl::run_context_thread() {
        mutexIO.lock();
        while (tcp.attemps_fail <= maxAttemp) {
            if (onConnectionRetry && tcp.attemps_fail > 0)
                onConnectionRetry(tcp.attemps_fail);
            tcp.error_code.clear();
            tcp.context.restart();
            tcp.resolver.async_resolve(host, service,
                                       std::bind(&WebsocketClientSsl::resolve, this, asio::placeholders::error,
                                                 asio::placeholders::endpoint));
            tcp.context.run();
            if (!tcp.error_code) break;
            tcp.attemps_fail++;
            std::this_thread::sleep_for(std::chrono::seconds(timeout));
        }
        consume_response_buffer();
        tcp.attemps_fail = 0;
        mutexIO.unlock();
    }

    void WebsocketClientSsl::resolve(const std::error_code &error,
                                     const asio::ip::tcp::resolver::results_type &endpoints) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }

        // Attempt a connection to each endpoint in the list until we
        // successfully establish a connection.
        tcp.endpoints = endpoints;
        asio::async_connect(tcp.ssl_socket.lowest_layer(), tcp.endpoints,
                            std::bind(&WebsocketClientSsl::conn, this, asio::placeholders::error)
        );
    }

    void WebsocketClientSsl::conn(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // The connection was successful;
        tcp.ssl_socket.async_handshake(asio::ssl::stream_base::client,
                                       std::bind(&WebsocketClientSsl::ssl_handshake, this,
                                                 asio::placeholders::error));
    }

    void WebsocketClientSsl::ssl_handshake(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        std::string request;
        request = "GET /" + handshake.path + " HTTP/" + handshake.version + "\r\n";
        request += "Host: " + host + "\r\n";
        request += "Upgrade: websocket\r\n";
        request += "Connection: Upgrade\r\n";
        request += "Sec-WebSocket-Key: " + handshake.Sec_WebSocket_Key + "\r\n";
        request += "Origin: " + handshake.origin + "\r\n";
        request += "Sec-WebSocket-Protocol: " + handshake.Sec_WebSocket_Protocol + "\r\n";
        request += "Sec-WebSocket-Version: " + handshake.Sec_Websocket_Version + "\r\n";
        request += "\r\n";
        std::ostream request_stream(&request_buffer);
        request_stream << request;
        asio::async_write(tcp.ssl_socket, request_buffer,
                          std::bind(&WebsocketClientSsl::write_handshake, this, asio::placeholders::error,
                                    asio::placeholders::bytes_transferred)
        );
    }

    void WebsocketClientSsl::write_handshake(const std::error_code &error, const std::size_t bytes_sent) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Read the response status line. The response_ streambuf will
        // automatically grow to accommodate the entire line. The growth may be
        // limited by passing a maximum size to the streambuf constructor.
        asio::async_read_until(tcp.ssl_socket, response_buffer, "\r\n",
                               std::bind(&WebsocketClientSsl::read_handshake, this, asio::placeholders::error,
                                         bytes_sent, asio::placeholders::bytes_transferred)
        );
    }

    void WebsocketClientSsl::read_handshake(const std::error_code &error, const std::size_t bytes_sent,
                                            const std::size_t bytes_recvd) {
        if (error) {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Check that response is OK.
        std::istream response_stream(&response_buffer);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            if (onError)
                onError(-1, "Invalid response.");
            close();
            return;
        }
        if (status_code != 101) {
            if (onError)
                onError(status_code, "Invalid status code.");
            close();
            return;
        }

        asio::async_read_until(tcp.ssl_socket, response_buffer, "\r\n\r\n",
                               std::bind(&WebsocketClientSsl::consume_header_buffer, this,
                                         asio::placeholders::error)
        );
    }

    void WebsocketClientSsl::consume_header_buffer(const std::error_code &error) {
        consume_response_buffer();
        asio::async_read(tcp.ssl_socket, response_buffer, asio::transfer_at_least(1),
                         std::bind(&WebsocketClientSsl::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred));

        // The connection was successful
        if (onConnected)
            onConnected();
    }

    void WebsocketClientSsl::write(const std::error_code &error, const std::size_t bytes_sent) {
        if (error) {
            if (onError)
                onError(error.value(), error.message());

            return;
        }

        if (onMessageSent)
            onMessageSent(bytes_sent);
    }

    void WebsocketClientSsl::read(const std::error_code &error, const size_t bytes_recvd) {
        if (error) {
            if (onError)
                onError(error.value(), error.message());
            return;
        }

        FWsMessage rDataFrame;
        if (!decode_payload(rDataFrame)) {
            response_buffer.consume(response_buffer.size());
            asio::async_read(tcp.ssl_socket, response_buffer, asio::transfer_at_least(1),
                             std::bind(&WebsocketClientSsl::read, this, asio::placeholders::error,
                                       asio::placeholders::bytes_transferred)
            );
            return;
        }


        if (rDataFrame.data_frame.opcode == EOpcode::PING) {
            std::vector<std::byte> pong_buffer;
            pong_buffer.resize(1);
            if (pong_buffer.back() != std::byte('\0'))
                pong_buffer.push_back(std::byte('\0'));
            post_buffer(EOpcode::PONG, pong_buffer);
        } else if (rDataFrame.data_frame.opcode == EOpcode::PONG) {
            if (onPongReceived)
                onPongReceived();
        } else if (rDataFrame.data_frame.opcode == EOpcode::CONNECTION_CLOSE) {
            if (onCloseNotify)
                onCloseNotify();
        } else {
            if (onMessageReceived)
                onMessageReceived(bytes_recvd, rDataFrame);
        }

        consume_response_buffer();
        asio::async_read(tcp.ssl_socket, response_buffer, asio::transfer_at_least(1),
                         std::bind(&WebsocketClientSsl::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred)
        );
    }
}
