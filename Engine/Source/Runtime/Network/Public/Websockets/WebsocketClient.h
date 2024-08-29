#pragma once

#include <Net/Messages.h>

namespace Nanometro
{
    class WebsocketClient
    {
    public:
        WebsocketClient()
        {
        }

        ~WebsocketClient()
        {
            tcp.context.stop();
            pool->stop();
            consume_response_buffer();
        }

        /*HOST*/
        void setHost(const std::string& url = "localhost", const std::string& port = "")
        {
            host = url;
            service = port;
        }

        std::string getLocalAdress() const
        {
            if (isConnected())
                return tcp.socket.local_endpoint().address().to_string();
            return "";
        }

        std::string getLocalPort() const
        {
            if (isConnected())
                return tcp.socket.local_endpoint().address().to_string();
            return "";
        }

        std::string getRemoteAdress() const
        {
            if (isConnected())
                return tcp.socket.remote_endpoint().address().to_string();
            return host;
        }

        std::string getRemotePort() const
        {
            if (isConnected())
                return std::to_string(tcp.socket.remote_endpoint().port());
            return service;
        }

        /*SETTINGS*/
        void setTimeout(uint8_t value = 3) { timeout = value; }
        uint8_t getTimeout() const { return timeout; }
        void setMaxAttemp(uint8_t value = 3) { maxAttemp = value; }
        uint8_t getMaxAttemp() const { return timeout; }
        void setMaxSendBufferSize(int value = 1400) { maxSendBufferSize = value; }
        int getMaxSendBufferSize() const { return maxSendBufferSize; }
        void setSplitPackage(bool value = true) { splitBuffer = value; }
        bool getSplitPackage() const { return splitBuffer; }


        /*HANDSHAKE*/
        void setPath(const std::string& value = "chat") { handshake.path = value; }
        std::string getPath() const { return handshake.path; }
        void setVersion(const std::string& value = "1.1") { handshake.version = value; }
        std::string getVersion() const { return handshake.version; }
        void setKey(const std::string& value = "dGhlIHNhbXBsZSBub25jZQ==") { handshake.Sec_WebSocket_Key = value; }
        std::string getKey() const { return handshake.Sec_WebSocket_Key; }
        void setOrigin(const std::string& value = "client") { handshake.origin = value; }
        std::string getOrigin() const { return handshake.origin; }
        void setSecProtocol(const std::string& value = "chat, superchat") { handshake.Sec_WebSocket_Protocol = value; }
        std::string getSecProtocol() const { return handshake.Sec_WebSocket_Protocol; }
        void setSecVersion(const std::string& value = "13") { handshake.Sec_Websocket_Version = value; }
        std::string getSecVersion() const { return handshake.Sec_Websocket_Version; }

        /*DATAFRAME*/
        void setRSV1(bool value = false) { sDataFrame.rsv1 = value; }
        bool useRSV1() const { return sDataFrame.rsv1; }
        void setRSV2(bool value = false) { sDataFrame.rsv2 = value; }
        bool useRSV2() const { return sDataFrame.rsv2; }
        void setRSV3(bool value = false) { sDataFrame.rsv3 = value; }
        bool useRSV3() const { return sDataFrame.rsv3; }
        void setMask(bool value = true) { sDataFrame.mask = value; }
        bool useMask() const { return sDataFrame.mask; }

        /*MESSAGE*/
        bool send(const std::string& message);
        bool send_buffer(const std::vector<std::byte>& buffer);
        bool send_ping();
        bool async_read();

        /*CONNECTION*/
        bool connect();
        bool isConnected() const { return tcp.socket.is_open(); }

        void close()
        {
            tcp.context.stop();
            tcp.socket.shutdown(asio::ip::tcp::socket::shutdown_both, tcp.error_code);
            if (tcp.error_code && onError) onError(tcp.error_code.value(), tcp.error_code.message());

            tcp.socket.close(tcp.error_code);
            pool->join();
            if (tcp.error_code && onError) onError(tcp.error_code.value(), tcp.error_code.message());
            if (onClose) onClose();
        }

        /*EVENTS*/
        std::function<void()> onConnected;
        std::function<void(int)> onConnectionRetry;
        std::function<void()> onClose;
        std::function<void()> onCloseNotify;
        std::function<void(const size_t)> onMessageSent;
        std::function<void(const size_t, const FWsMessage)> onMessageReceived;
        std::function<void()> onPongReceived;
        std::function<void(const int, const std::string&)> onError;

    private:
        std::unique_ptr<asio::thread_pool> pool = std::make_unique<asio::thread_pool>(
            std::thread::hardware_concurrency());
        std::mutex mutexIO;
        std::mutex mutexBuffer;
        std::string host = "localhost";
        std::string service;
        uint8_t timeout = 3;
        uint8_t maxAttemp = 3;
        bool splitBuffer = false;
        int maxSendBufferSize = 1400;
        FAsioTcp tcp;
        asio::streambuf request_buffer;
        asio::streambuf response_buffer;
        FHandShake handshake;
        FDataFrame sDataFrame;

        void post_string(const std::string& str);
        void post_buffer(EOpcode opcode, const std::vector<std::byte>& buffer);
        void package_string(const std::string& str);
        std::string encode_string_payload(const std::string& payload);
        void package_buffer(const std::vector<std::byte>& buffer);
        std::vector<std::byte> encode_buffer_payload(const std::vector<std::byte>& payload);
        size_t get_frame_encode_size(const size_t buffer_size);
        std::array<std::byte, 4> mask_gen();
        bool decode_payload(FWsMessage& data_frame);

        void consume_response_buffer()
        {
            request_buffer.consume(request_buffer.size());
            response_buffer.consume(response_buffer.size());
        }

        void run_context_thread();
        void resolve(const std::error_code& error, const asio::ip::tcp::resolver::results_type& endpoints);
        void conn(const std::error_code& error);
        void write_handshake(const std::error_code& error, const std::size_t bytes_sent);
        void read_handshake(const std::error_code& error, const std::size_t bytes_sent, const std::size_t bytes_recvd);
        void consume_header_buffer(const std::error_code& error);
        void write(const std::error_code& error, const std::size_t bytes_sent);
        void read(const std::error_code& error, const size_t bytes_recvd);
    };
}
