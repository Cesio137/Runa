#pragma once

#include "Net/Messages.h"

namespace Nanometro
{
    class UDPClient
    {
    public:
        UDPClient()
        {
        }

        ~UDPClient()
        {
            udp.context.stop();
            pool->stop();
            consume_receive_buffer();
        }

        /*HOST | LOCAL*/
        void setHost(const std::string& ip, const std::string& port)
        {
            host = ip;
            service = port;
        }

        std::string getLocalAdress() const
        {
            if (isConnected())
                return udp.socket.local_endpoint().address().to_string();
            return "";
        }

        std::string getLocalPort() const
        {
            if (isConnected())
                return std::to_string(udp.socket.local_endpoint().port());
            return "";
        }

        std::string getRemoteAdress() const
        {
            if (isConnected())
                return udp.socket.remote_endpoint().address().to_string();
            return host;
        }

        std::string getRemovePort() const
        {
            if (isConnected())
                return std::to_string(udp.socket.remote_endpoint().port());
            return service;
        }

        /*SETTINGS*/
        void setTimeout(uint8_t value = 3) { timeout = value; }
        uint8_t getTimeout() const { return timeout; }
        void setMaxAttemp(uint8_t value = 3) { maxAttemp = value; }
        uint8_t getMaxAttemp() const { return timeout; }
        void setMaxSendBufferSize(int value = 1024) { maxSendBufferSize = value; }
        int getMaxSendBufferSize() const { return maxSendBufferSize; }
        void setMaxReceiveBufferSize(int value = 1024) { maxReceiveBufferSize = value; }
        int getMaxReceiveBufferSize() const { return maxReceiveBufferSize; }
        void setSplitPackage(bool value = true) { splitBuffer = value; }
        bool getSplitPackage() const { return splitBuffer; }

        /*MESSAGE*/
        bool send(const std::string& message);
        bool sendRaw(const std::vector<std::byte>& buffer);
        bool async_read();

        /*CONNECTION*/
        bool connect();
        bool isConnected() const { return udp.socket.is_open(); }

        void close()
        {
            udp.context.stop();
            udp.socket.close(udp.error_code);
            pool->join();
            if (udp.error_code && onError)
                onError(udp.error_code.value(), udp.error_code.message());
            if (onClose)
                onClose();
        }

        /*ERRORS*/
        int getErrorCode() const { return udp.error_code.value(); }
        std::string getErrorMessage() const { return udp.error_code.message(); }

        /*EVENTS*/
        std::function<void()> onConnected;
        std::function<void()> onClose;
        std::function<void(int)> onConnectionRetry;
        std::function<void(const size_t)> onMessageSent;
        std::function<void(const size_t, const FUdpMessage)> onMessageReceived;
        std::function<void(const int, const std::string&)> onError;

    private:
        std::unique_ptr<asio::thread_pool> pool = std::make_unique<asio::thread_pool>(
            std::thread::hardware_concurrency());
        std::mutex mutexIO;
        std::mutex mutexBuffer;
        FAsioUdp udp;
        std::string host = "localhost";
        std::string service;
        uint8_t timeout = 3;
        uint8_t maxAttemp = 3;
        bool splitBuffer = true;
        int maxSendBufferSize = 1024;
        int maxReceiveBufferSize = 1024;
        FUdpMessage rbuffer;

        void package_string(const std::string& str);
        void package_buffer(const std::vector<std::byte>& buffer);

        void consume_receive_buffer()
        {
            rbuffer.rawData.clear();
            rbuffer.rawData.resize(maxReceiveBufferSize);
        }

        /*ASYNC HANDLER FUNCTIONS*/
        void run_context_thread();
        void resolve(const std::error_code& error, const asio::ip::udp::resolver::results_type& results);
        void conn(const std::error_code& error);
        void send_to(const std::error_code& error, const size_t bytes_sent);
        void receive_from(const std::error_code& error, const size_t bytes_recvd);
    };
} //Nanometro
