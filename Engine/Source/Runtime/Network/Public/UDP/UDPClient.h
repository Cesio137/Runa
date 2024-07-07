#pragma once

#include "Net/Messages.h"

namespace Nanometro {
    class UDPClient
    {
    public:
        UDPClient() {}
        ~UDPClient() {}

        /*HOST*/
        void setHost(const std::string& ip, const std::string& port)
        {
            host = ip;
            service = port;
        }
        std::string getHost() const { return host; }
        std::string getPort() const { return service; }

        /*SETTINGS*/
        void setTimeout(uint8_t value = 4) { timeout = value; }
        uint8_t getTimeout() const { return timeout; }
        void setMaxAttemp(uint8_t value = 3) { maxAttemp = value; }
        uint8_t getMaxAttemp() const { return timeout; }
        void setMaxBufferSize(int value = 1024) { maxBufferSize = value; }
        int getMaxBufferSize() const { return maxBufferSize; }
        void setSplitPackage(bool value = true) { splitBuffer = value; }
        bool getSplitPackage() const { return splitBuffer; }

        /*MESSAGE*/
        void send(const std::string& message);
        void sendRaw(const std::vector<char>& buffer);

        /*CONNECTION*/
        void connect();
        bool isConnected() const { return udp.socket.is_open(); }
        void close() {             
            udp.context.stop(); 
            udp.socket.close();
        }

        /*EVENTS*/
        std::function<void()> onConnected;
        std::function<void(int, const std::string&)> onConnectionError;
        std::function<void(int)> onConnectionRetry;
        std::function<void(std::size_t)> onMessageSent;
        std::function<void(int, const std::string&)> onMessageSentError;
        std::function<void(int, const udpMessage)> onMessageReceived;
        std::function<void(int, const std::string&)> onMessageReceivedError;

    private:
        std::unique_ptr<asio::thread_pool> pool = std::make_unique<asio::thread_pool>(std::thread::hardware_concurrency());
        std::mutex mutexIO;
        std::mutex mutexBuffer;
        FAsioUdp udp;
        std::string host = "localhost";
		std::string service;
        uint8_t timeout = 4;
        uint8_t maxAttemp = 3;
        bool splitBuffer = true;
        int maxBufferSize = 1024;
        udpMessage rbuffer;

        /*ASYNC HANDLER FUNCTIONS*/
        void runContextThread();
        void resolve(std::error_code error, asio::ip::udp::resolver::results_type results);
        void conn(std::error_code error);
        void package_buffer(const std::vector<char>& buffer);
        void send_to(std::error_code error, std::size_t bytes_sent);
        void receive_from(std::error_code error, std::size_t bytes_recvd);
    };
} //Nanometro