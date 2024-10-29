#pragma once

#include <iostream>

#include "Net/Messages.h"

namespace Nanometro {
    class TCPClient {
    public:
        TCPClient() {
        }

        ~TCPClient() {
            tcp.context.stop();
            pool->stop();
            consume_response_buffer();
        }

        /*HOST | LOCAL*/
        void setHost(const std::string &ip, const std::string &port) {
            host = ip;
            service = port;
        }

        std::string getLocalAdress() const {
            if (isConnected()) return tcp.socket.local_endpoint().address().to_string();
            return "";
        }

        std::string getLocalPort() const {
            if (isConnected())
                return std::to_string(tcp.socket.local_endpoint().port());
            return "";
        }

        std::string getRemoteAdress() const {
            if (isConnected())
                return tcp.socket.remote_endpoint().address().to_string();
            return host;
        }

        std::string getRemotePort() const {
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

        /*MESSAGE*/
        bool send(const std::string &message);

        bool sendRaw(const std::vector<std::byte> &buffer);

        bool async_read();

        /*CONNECTION*/
        bool connect();

        bool isConnected() const { return tcp.socket.is_open(); }

        void close(bool forceClose = false) {
            tcp.context.stop();
            if (forceClose) {
                tcp.socket.close(tcp.error_code);
                if (tcp.error_code && onError)
                    onError(tcp.error_code.value(), tcp.error_code.message());
            } else {
                tcp.socket.shutdown(asio::ip::tcp::socket::shutdown_both, tcp.error_code);
                if (tcp.error_code && onError)
                    onError(tcp.error_code.value(), tcp.error_code.message());
                tcp.socket.close(tcp.error_code);
                if (tcp.error_code && onError)
                    onError(tcp.error_code.value(), tcp.error_code.message());
            }
            pool->join();
        }

        /*ERRORS*/
        int getErrorCode() const { return tcp.error_code.value(); }
        std::string getErrorMessage() const { return tcp.error_code.message(); }

        /*EVENTS*/
        std::function<void()> onConnected;
        std::function<void()> onClose;
        std::function<void(const int)> onConnectionRetry;
        std::function<void(const size_t)> onMessageSent;
        std::function<void(const size_t, const FTcpMessage)> onMessageReceived;
        std::function<void(const int, const std::string &)> onError;

    private:
        std::unique_ptr<asio::thread_pool> pool =
                std::make_unique<asio::thread_pool>(std::thread::hardware_concurrency());
        std::mutex mutexIO;
        std::mutex mutexBuffer;
        FAsioTcp tcp;
        std::string host = "localhost";
        std::string service;
        uint8_t timeout = 3;
        uint8_t maxAttemp = 3;
        bool splitBuffer = true;
        int maxSendBufferSize = 1400;
        asio::streambuf response_buffer;

        void package_string(const std::string &str);

        void package_buffer(const std::vector<std::byte> &buffer);

        void consume_response_buffer() {
            response_buffer.consume(response_buffer.size());
        }

        void run_context_thread();

        void resolve(const std::error_code &error,
                     const asio::ip::tcp::resolver::results_type &endpoints);

        void conn(const std::error_code &error);

        void write(const std::error_code &error, const size_t bytes_sent);

        void read(const std::error_code &error, const size_t bytes_recvd);
    };

    class TCPClientSsl {
    public:
        TCPClientSsl() {
        }

        ~TCPClientSsl() {
            tcp.context.stop();
            pool->stop();
            consume_response_buffer();
        }

        /*HOST | LOCAL*/
        void setHost(const std::string &ip, const std::string &port) {
            host = ip;
            service = port;
        }

        std::string getLocalAdress() const {
            if (isConnected())
                return tcp.ssl_socket.lowest_layer()
                        .local_endpoint()
                        .address()
                        .to_string();
            return "";
        }

        std::string getLocalPort() const {
            if (isConnected())
                return std::to_string(
                    tcp.ssl_socket.lowest_layer().local_endpoint().port());
            return "";
        }

        std::string getRemoteAdress() const {
            if (isConnected())
                return tcp.ssl_socket.lowest_layer()
                        .remote_endpoint()
                        .address()
                        .to_string();
            return host;
        }

        std::string getRemotePort() const {
            if (isConnected())
                return std::to_string(
                    tcp.ssl_socket.lowest_layer().remote_endpoint().port());
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

        /*SECURITY LAYER*/
        bool load_private_key_data(const std::string &key_data) {
            try {
                const asio::const_buffer buffer(key_data.data(), key_data.size());
                tcp.ssl_context.use_private_key(buffer, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_private_key_file(const std::string &filename) {
            try {
                tcp.ssl_context.use_private_key_file(filename, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_data(const std::string &cert_data) {
            try {
                const asio::const_buffer buffer(cert_data.data(), cert_data.size());
                tcp.ssl_context.use_certificate(buffer, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_file(const std::string &filename) {
            try {
                tcp.ssl_context.use_certificate_file(filename, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_chain_data(const std::string &cert_chain_data) {
            try {
                const asio::const_buffer buffer(cert_chain_data.data(),
                                                cert_chain_data.size());
                tcp.ssl_context.use_certificate_chain(buffer);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_chain_file(const std::string &filename) {
            try {
                tcp.ssl_context.use_certificate_chain_file(filename);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_verify_file(const std::string &filename) {
            try {
                tcp.ssl_context.load_verify_file(filename);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        /*MESSAGE*/
        bool send(const std::string &message);

        bool sendRaw(const std::vector<std::byte> &buffer);

        bool async_read();

        /*CONNECTION*/
        bool connect();

        bool isConnected() const { return tcp.ssl_socket.lowest_layer().is_open(); }

        void close(bool forceClose = false) {
            tcp.context.stop();
            tcp.ssl_socket.shutdown(tcp.error_code);
            tcp.ssl_socket.async_shutdown([&](const std::error_code &error) {
                if (error) {
                    tcp.error_code = error;
                    if (onError) onError(error.value(), error.message());
                }

                if (forceClose) {
                    tcp.ssl_socket.lowest_layer().close(tcp.error_code);
                    if (tcp.error_code && onError)
                        onError(tcp.error_code.value(), tcp.error_code.message());
                } else {
                    tcp.ssl_socket.lowest_layer().shutdown(
                        asio::ip::tcp::socket::shutdown_both, tcp.error_code);
                    if (tcp.error_code && onError)
                        onError(tcp.error_code.value(), tcp.error_code.message());

                    tcp.ssl_socket.lowest_layer().close(tcp.error_code);
                    if (tcp.error_code && onError)
                        onError(tcp.error_code.value(), tcp.error_code.message());
                }
                if (onClose) onClose();
            });
        }

        /*ERRORS*/
        int getErrorCode() const { return tcp.error_code.value(); }
        std::string getErrorMessage() const { return tcp.error_code.message(); }

        /*EVENTS*/
        std::function<void()> onConnected;
        std::function<void()> onClose;
        std::function<void(const int)> onConnectionRetry;
        std::function<void(const size_t)> onMessageSent;
        std::function<void(const size_t, const FTcpMessage)> onMessageReceived;
        std::function<void(const int, const std::string &)> onError;

    private:
        std::unique_ptr<asio::thread_pool> pool =
                std::make_unique<asio::thread_pool>(std::thread::hardware_concurrency());
        std::mutex mutexIO;
        std::mutex mutexBuffer;
        FAsioTcpSsl tcp;
        std::string host = "localhost";
        std::string service;
        uint8_t timeout = 3;
        uint8_t maxAttemp = 3;
        bool splitBuffer = true;
        int maxSendBufferSize = 1400;
        asio::streambuf response_buffer;

        void package_string(const std::string &str);

        void package_buffer(const std::vector<std::byte> &buffer);

        void consume_response_buffer() {
            response_buffer.consume(response_buffer.size());
        }

        void run_context_thread();

        void resolve(const std::error_code &error,
                     const asio::ip::tcp::resolver::results_type &endpoints);

        void conn(const std::error_code &error);

        void ssl_handshake(const std::error_code &error);

        void write(const std::error_code &error, const size_t bytes_sent);

        void read(const std::error_code &error, const size_t bytes_recvd);
    };
} // namespace Nanometro
