#pragma once

#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <asio.hpp>

namespace Nanometro {
    class WebsocketClient
    {
    public:
        WebsocketClient();
        ~WebsocketClient();

        int Connect(const std::string& host, const std::string& port);
        void Close();
        bool is_open();
        void Send(const std::string& message);

        std::function<void()> OnOpen;
        std::function<void()> OnConnectionError;
        std::function<void()> OnClose;
        std::function<void(const std::string&)> OnMessage;

    private:
        asio::error_code error_code;
        asio::io_context context;
        asio::io_context::work idle_work;
        asio::ip::tcp::resolver resolver;
        asio::ip::tcp::socket socket;

        std::string _host;
        std::string protocol_version = "13";

        std::string request;
    };
}

#endif// WEBSOCKETCLIENT_H