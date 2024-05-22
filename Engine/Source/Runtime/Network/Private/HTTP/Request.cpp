#include "HTTP/Request.h"
#include <iostream>

namespace Nanometro {
    void Request::SyncConstructRequest()
    {
        // HTTP request
        std::ostream request_stream(&request_buffer);

        request_stream << verb.at(request.verb) << " " << request.path;
        if (!request.params.empty())
        {
            request_stream << "?";
            int i = 0;
            for (std::pair<std::string, std::string> params : request.params) {
                if (i > 0) request_stream << "&";
                request_stream << params.first << "=" << params.second;
                if (i == 0) ++i;
            } 
        }
        request_stream << " HTTP/" << request.version << "\r\n";
        
        request_stream << "Host: " << request.host << ":" << request.service << "\r\n";
        if (!request.headers.empty())
        {
            for (std::pair<std::string, std::string> header : request.headers) {
                request_stream << header.first << ": " << header.second << "\r\n";
            } 
            request_stream << "\r\n";
        }

        if (request.headers["Content-Type"] == "application/json" || request.headers["Content-Type"] == "application/javascript")
            if (!request.body.empty())
                request_stream << request.body;
        else if (request.headers["Content-Type"] == "text/html")
            if (!request.content.empty())
                request_stream << request.content;
    }
    /*
    int Request::SyncProcessRequest() 
    {
        try {
            HttpContext.endpoints = HttpContext.resolver.resolve(Req.host, Req.service);
            asio::connect(HttpContext.socket, HttpContext.endpoints, HttpContext.error_code);
            if (HttpContext.error_code.value() != 0)
            {
                return HttpContext.error_code.value();
            }
                
            // Do http request
            size_t bytes_sent = 
            OnRequestProgress(bytes_sent, 0);

            asio::streambuf response;
            asio::read_until(HttpContext.socket, response, "\r\n");

            // Check that response is OK.
            std::istream response_stream(&response);
            std::string _http_version;
            response_stream >> _http_version;
            unsigned int status_code;
            response_stream >> status_code;
            std::string status_message;
            std::getline(response_stream, status_message);
            if (!response_stream || _http_version.substr(0, 5) != "HTTP/")
            {
                exceptions = "Invalid response.";
                return 1;
            }
            if (status_code != 200)
            {
                exceptions = "Response returned with status code " + std::to_string(status_code);
                return status_code;
            }

            // Read the response headers, which are terminated by a blank line.
            size_t bytes_received = asio::read_until(HttpContext.socket, response, "\r\n\r\n");
            OnRequestProgress(bytes_sent, bytes_received);

            // Process the response headers.
            std::string header;
            while (std::getline(response_stream, header) && header != "\r")
                std::cout << header << "\n";
            std::cout << "\n";

            // Write whatever content we already have to output.
            if (response.size() > 0)
                std::cout << &response;

            // Read until EOF, writing data to output as we go.
            std::error_code error;
            while (asio::read(HttpContext.socket, response, asio::transfer_at_least(1), error)) 
            {
                std::cout << &response;
                if (error != asio::error::eof)
                    throw std::system_error(error);
            }
            OnProcessRequestComplete(response);
        }
        catch (std::exception& e)
        {
            exceptions = "Exception: ";
            exceptions.append(e.what());
            return 2;
        }
        

        return 0;
    }
    */
} // Nanometro