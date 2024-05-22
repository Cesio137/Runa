#pragma once

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "HTTP/Request.h"

namespace Nanometro
{
    class HttpClient
    {
    public:
        HttpClient()
        {
            HttpContext.resolver = asio::ip::tcp::resolver(HttpContext.context);
            HttpContext.socket = asio::ip::tcp::socket(HttpContext.context);
        }
        ~HttpClient(){}

        int SyncProcessRequest();
        
        void SetRequest(const Request& req) 
        { 
            request = req;
        }

        Request GetRequest() { return request; }

    private:
        FAsio HttpContext;
        Request request;
    };
    
} // namespace Nanometro


#endif // HTTPCLIENT_H