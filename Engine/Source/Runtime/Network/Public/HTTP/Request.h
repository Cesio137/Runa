#pragma once

#ifndef REQUEST_H
#define REQUEST_H

#include <asio.hpp>


namespace Nanometro {

    class Request {
    public:
        Request();
        ~Request();

        void SetHost(const std::string& url = "localhost", const std::string& service = "");
        void SetRequest(const std::string& method = "GET", const std::string& version = "2.0");
        int SyncProcessRequest();

        std::function<void(const asio::streambuf& res)> OnProcessRequestComplete;
        std::function<void(int BytesSent, int BytesReceived)> OnRequestProgress;

    private:
        asio::error_code error_code;
        std::string exceptions;
        asio::io_context context;
        asio::ip::tcp::resolver resolver;
        asio::ip::tcp::resolver::results_type endpoints;
        asio::ip::tcp::socket socket;

        std::string request_method = "GET";
        std::string http_version = "2.0";
        asio::streambuf request;
    };

} // Nanometro

#endif //REQUEST_H
