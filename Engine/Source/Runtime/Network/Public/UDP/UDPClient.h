#pragma once

#include "Net/Messages.h"

namespace Nanometro {
    class UDPClient
    {
    public:
        UDPClient() {

        }
        ~UDPClient() {

        }

        /*HOST*/
        void setHost(const std::string& ip, const std::string& port)
        {
            host = ip;
            service = port;
        }
        std::string getHost() const { return host; }
        std::string getPort() const { return service; }

        /*THREADS*/
		void setThreadNumber(int value = 2) { pool = std::make_unique<asio::thread_pool>(value); }

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
        std::function<void(std::size_t)> onMessageSent;
        std::function<void(int, const std::string&)> onMessageSentError;
        std::function<void(int, const udpMessage)> onMessageReceived;
        std::function<void(int, const std::string&)> onMessageReceivedError;

    private:
        std::unique_ptr<asio::thread_pool> pool = std::make_unique<asio::thread_pool>(2);
        std::mutex mutexIO;
        std::mutex mutexBuffer;
        FAsioUdp udp;
        std::string host = "localhost";
		std::string service;
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