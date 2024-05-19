#include "HTTP/Request.h"
#include <iostream>

namespace Nanometro {
    Request::Request(): resolver(context), socket(context)
    {
        
    }

    Request::~Request()
    {
    }

    void Request::SetHost(const std::string &url, const std::string &service)
    {
        endpoints = resolver.resolve(url, service);
    }

    void Request::SetRequest(const std::string &method, const std::string &version)
    {
        request_method = method;
        http_version = version;
    }

    int Request::SyncProcessRequest()
    {
        try {
            asio::connect(socket, endpoints, error_code);
            if (error_code.value() != 0)
            {
                return error_code.value();
            }
                
            // HTTP request
            std::ostream request_stream(&request);
            request_stream << request_method << " / HTTP/" << http_version << "\r\n";
            request_stream << "Host: localhost\r\n";
            request_stream << "Accept: */*\r\n";
            request_stream << "Connection: close\r\n\r\n";
            size_t bytes_sent = asio::write(socket, request);
            OnRequestProgress(bytes_sent, 0);

            asio::streambuf response;
            asio::read_until(socket, response, "\r\n");

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
            size_t bytes_received = asio::read_until(socket, response, "\r\n\r\n");
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
            while (asio::read(socket, response, asio::transfer_at_least(1), error)) 
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
} // Nanometro