#pragma once

#include <Net/Common.h>

namespace Nanometro {
    class WebsocketClient
    {
    public:
        WebsocketClient() {}
        ~WebsocketClient() {}

        std::function<void()> onOpen;
        std::function<void()> onConnectionError;
        std::function<void()> onClose;
        std::function<void(const std::string&)> onMessage;

    private:
        std::string host = "localhost";
        std::string service;
        FAsioTcp tcp;
    };
}