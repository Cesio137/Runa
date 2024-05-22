#pragma once

#ifndef NETCOMMON_H
#define NETCOMMON_H

#include <asio.hpp>
#include <map>

namespace Nanometro
{
    enum EHttpVerb : uint8_t
    {
        GET      = 0, 
        POST     = 1, 
        PUT      = 2, 
        PATCH    = 3, 
        DEL      = 4, 
        COPY     = 5, 
        HEAD     = 6, 
        OPTIONS  = 7,
        LOCK     = 8, 
        UNLOCK   = 9, 
        PROPFIND = 10
    };

    struct FAsio
    {
        asio::error_code error_code;
        std::string exceptions;
        asio::io_context context;
        std::optional<asio::ip::tcp::resolver> resolver;
        asio::ip::tcp::resolver::results_type endpoints;
        std::optional<asio::ip::tcp::socket> socket;
    };

    struct FHttpRequest
    {
        std::string host;
        std::string service;
        std::map<std::string, std::string> params;
        EHttpVerb verb = EHttpVerb::GET;
        std::string path = "/";
        std::string version = "2.0";
        std::map<std::string, std::string> headers;
        std::string body;
        std::string content;
        float timeout = 3.0f;
    };

} // namespace Nanometro


#endif //NETCOMMON_H