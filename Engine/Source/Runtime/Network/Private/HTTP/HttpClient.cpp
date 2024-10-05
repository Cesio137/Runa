#include "HTTP/HttpClient.h"

namespace Nanometro {
    void HttpClient::preparePayload() {
        if (!payload.empty())
            payload.clear();

        payload = verb.at(request.verb) + " " + request.path;

        if (!request.params.empty()) {
            payload += "?";
            bool first = true;
            for (const std::pair<std::string, std::string> param: request.params) {
                if (!first) payload += "&";
                payload += param.first + "=" + param.second;
                first = false;
            }
        }
        payload += " HTTP/" + request.version + "\r\n";

        payload += "Host: " + host;
        if (!service.empty()) payload += ":" + service;
        payload += "\r\n";

        if (!request.headers.empty()) {
            for (const std::pair<std::string, std::string> header: request.headers) {
                payload += header.first + ": " + header.second + "\r\n";
            }
            payload += "Content-Length: " + std::to_string(request.body.length()) + "\r\n";
        }
        payload += "\r\n";

        if (!request.body.empty())
            payload += "\r\n" + request.body;
    }

    void HttpClient::async_preparePayload() {
        asio::post(*pool, [this]() {
            mutexPayload.lock();
            preparePayload();
            if (onAsyncPayloadFinished)
                onAsyncPayloadFinished();
            mutexPayload.unlock();
        });
    }

    bool HttpClient::processRequest() {
        if (!pool && !payload.empty())
            return false;

        asio::post(*pool, std::bind(&HttpClient::run_context_thread, this));
        return true;
    }

    void HttpClient::run_context_thread() {
        mutexIO.lock();
        while (tcp.attemps_fail <= maxAttemp) {
            if (onRequestWillRetry && tcp.attemps_fail > 0)
                onRequestWillRetry(tcp.attemps_fail);
            tcp.error_code.clear();
            tcp.context.restart();
            tcp.resolver.async_resolve(getHost(), getPort(),
                                       std::bind(&HttpClient::resolve, this, asio::placeholders::error,
                                                 asio::placeholders::results));
            tcp.context.run();
            if (!tcp.error_code) break;
            tcp.attemps_fail++;
            std::this_thread::sleep_for(std::chrono::seconds(timeout));
        }
        consume_stream_buffers();
        mutexIO.unlock();
    }

    void HttpClient::resolve(const std::error_code &err, const asio::ip::tcp::resolver::results_type &endpoints) {
        if (err) {
            tcp.error_code = err;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Attempt a connection to each endpoint in the list until we
        // successfully establish a connection.
        tcp.endpoints = endpoints;
        asio::async_connect(tcp.socket,
                            tcp.endpoints,
                            std::bind(&HttpClient::connect, this, asio::placeholders::error)
        );
    }

    void HttpClient::connect(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // The connection was successful. Send the request.;
        std::ostream request_stream(&request_buffer);
        request_stream << payload;
        asio::async_write(tcp.socket,
                          request_buffer,
                          std::bind(&HttpClient::write_request, this, asio::placeholders::error,
                                    asio::placeholders::bytes_transferred)
        );
    }

    void HttpClient::write_request(const std::error_code &error, std::size_t bytes_sent) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Read the response status line. The response_ streambuf will
        // automatically grow to accommodate the entire line. The growth may be
        // limited by passing a maximum size to the streambuf constructor.
        bytes_sent = request_buffer.size();
        if (onRequestProgress)
            onRequestProgress(bytes_sent, bytes_sent);
        asio::async_read_until(tcp.socket, response_buffer, "\r\n",
                               std::bind(&HttpClient::read_status_line, this, asio::placeholders::error, bytes_sent,
                                         asio::placeholders::bytes_transferred)
        );
    }

    void HttpClient::read_status_line(const std::error_code &error, std::size_t bytes_sent, std::size_t bytes_recvd) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Check that response is OK.
        if (onRequestProgress)
            onRequestProgress(bytes_sent, bytes_recvd);
        std::istream response_stream(&response_buffer);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            if (onResponseFail)
                onResponseFail(-1);
            return;
        }
        if (status_code != 200) {
            if (onResponseFail)
                onResponseFail(status_code);
            return;
        }
        // Read the response headers, which are terminated by a blank line.
        asio::async_read_until(tcp.socket,
                               response_buffer, "\r\n\r\n",
                               std::bind(&HttpClient::read_headers, this, asio::placeholders::error)
        );
    }

    void HttpClient::read_headers(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Process the response headers.
        response.clear();
        std::istream response_stream(&response_buffer);
        std::string header;
        while (std::getline(response_stream, header) && header != "\r")
            response.appendHeader(header);
        // Write whatever content we already have to output.
        std::ostringstream content_buffer;
        if (response_buffer.size() > 0) {
            content_buffer << &response_buffer;
            response.setContent(content_buffer.str());
        }
        // Start reading remaining data until EOF.
        asio::async_read(tcp.socket,
                         response_buffer,
                         asio::transfer_at_least(1),
                         std::bind(&HttpClient::read_content, this, asio::placeholders::error)
        );
    }

    void HttpClient::read_content(const std::error_code &error) {
        if (error) {
            if (onRequestComplete)
                onRequestComplete(response);
            return;
        }
        // Write all of the data that has been read so far.
        std::ostringstream stream_buffer;
        stream_buffer << &response_buffer;
        if (!stream_buffer.str().empty())
            response.setContent(stream_buffer.str());
        // Continue reading remaining data until EOF.
        asio::async_read(tcp.socket,
                         response_buffer,
                         asio::transfer_at_least(1),
                         std::bind(&HttpClient::read_content, this, asio::placeholders::error)
        );
    }

    void HttpClientSsl::preparePayload() {
        if (!payload.empty())
            payload.clear();

        payload = verb.at(request.verb) + " " + request.path;

        if (!request.params.empty()) {
            payload += "?";
            bool first = true;
            for (const std::pair<std::string, std::string> param: request.params) {
                if (!first) payload += "&";
                payload += param.first + "=" + param.second;
                first = false;
            }
        }
        payload += " HTTP/" + request.version + "\r\n";

        payload += "Host: " + host;
        if (!service.empty()) payload += ":" + service;
        payload += "\r\n";

        if (!request.headers.empty()) {
            for (const std::pair<std::string, std::string> header: request.headers) {
                payload += header.first + ": " + header.second + "\r\n";
            }
            payload += "Content-Length: " + std::to_string(request.body.length()) + "\r\n";
        }
        payload += "\r\n";

        if (!request.body.empty())
            payload += "\r\n" + request.body;
    }

    void HttpClientSsl::async_preparePayload() {
        asio::post(*pool, [this]() {
            mutexPayload.lock();
            preparePayload();
            if (onAsyncPayloadFinished)
                onAsyncPayloadFinished();
            mutexPayload.unlock();
        });
    }

    bool HttpClientSsl::processRequest() {
        if (!pool && !payload.empty() && !isCALoaded)
            return false;

        asio::post(*pool, std::bind(&HttpClientSsl::run_context_thread, this));
        return true;
    }

    void HttpClientSsl::run_context_thread() {
        mutexIO.lock();
        while (tcp.attemps_fail <= maxAttemp) {
            if (onRequestWillRetry && tcp.attemps_fail > 0)
                onRequestWillRetry(tcp.attemps_fail);
            tcp.error_code.clear();
            tcp.context.restart();
            tcp.resolver.async_resolve(getHost(), getPort(),
                                       std::bind(&HttpClientSsl::resolve, this, asio::placeholders::error,
                                                 asio::placeholders::results));
            tcp.context.run();
            if (!tcp.error_code) break;
            tcp.attemps_fail++;
            std::this_thread::sleep_for(std::chrono::seconds(timeout));
        }
        consume_stream_buffers();
        mutexIO.unlock();
    }

    void HttpClientSsl::resolve(const std::error_code &error, const asio::ip::tcp::resolver::results_type &endpoints) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Attempt a connection to each endpoint in the list until we
        // successfully establish a connection.
        tcp.endpoints = endpoints;
        tcp.ssl_socket.async_handshake(asio::ssl::stream_base::client,
                                       std::bind(&HttpClientSsl::ssl_handshake, this, asio::placeholders::error));
    }

    void HttpClientSsl::ssl_handshake(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        asio::async_connect(tcp.ssl_socket.lowest_layer(), tcp.endpoints,
                            std::bind(&HttpClientSsl::connect, this, asio::placeholders::error)
        );
    }

    void HttpClientSsl::connect(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // The connection was successful. Send the request.;
        std::ostream request_stream(&request_buffer);
        request_stream << payload;
        asio::async_write(tcp.ssl_socket.lowest_layer(), request_buffer,
                          std::bind(&HttpClientSsl::write_request, this, asio::placeholders::error,
                                    asio::placeholders::bytes_transferred)
        );
    }

    void HttpClientSsl::write_request(const std::error_code &error, const size_t bytes_sent) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Read the response status line. The response_ streambuf will
        // automatically grow to accommodate the entire line. The growth may be
        // limited by passing a maximum size to the streambuf constructor.
        if (onRequestProgress)
            onRequestProgress(bytes_sent, 0);
        asio::async_read_until(tcp.ssl_socket.lowest_layer(), response_buffer, "\r\n",
                               std::bind(&HttpClientSsl::read_status_line, this, asio::placeholders::error, bytes_sent,
                                         asio::placeholders::bytes_transferred)
        );
    }

    void HttpClientSsl::read_status_line(const std::error_code &error, const size_t bytes_sent,
                                         const size_t bytes_recvd) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Check that response is OK.
        if (onRequestProgress)
            onRequestProgress(bytes_sent, bytes_recvd);
        std::istream response_stream(&response_buffer);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            if (onResponseFail)
                onResponseFail(-1);
            return;
        }
        if (status_code != 200) {
            if (onResponseFail)
                onResponseFail(status_code);
            return;
        }

        // Read the response headers, which are terminated by a blank line.
        asio::async_read_until(tcp.ssl_socket.lowest_layer(), response_buffer, "\r\n\r\n",
                               std::bind(&HttpClientSsl::read_headers, this, asio::placeholders::error)
        );
    }

    void HttpClientSsl::read_headers(const std::error_code &error) {
        if (error) {
            tcp.error_code = error;
            if (onRequestFail)
                onRequestFail(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Process the response headers.
        response.clear();
        std::istream response_stream(&response_buffer);
        std::string header;

        while (std::getline(response_stream, header) && header != "\r")
            response.appendHeader(header);

        // Write whatever content we already have to output.
        std::ostringstream content_buffer;
        if (response_buffer.size() > 0) {
            content_buffer << &response_buffer;
            response.setContent(content_buffer.str());
        }

        // Start reading remaining data until EOF.
        asio::async_read(tcp.ssl_socket.lowest_layer(), response_buffer, asio::transfer_at_least(1),
                         std::bind(&HttpClientSsl::read_content, this, asio::placeholders::error)
        );
    }

    void HttpClientSsl::read_content(const std::error_code &error) {
        if (error) {
            if (onRequestComplete)
                onRequestComplete(response);
            return;
        }
        // Write all of the data that has been read so far.
        std::ostringstream stream_buffer;
        stream_buffer << &response_buffer;
        if (!stream_buffer.str().empty())
            response.setContent(stream_buffer.str());


        // Continue reading remaining data until EOF.
        asio::async_read(tcp.ssl_socket.lowest_layer(), response_buffer, asio::transfer_at_least(1),
                         std::bind(&HttpClientSsl::read_content, this, asio::placeholders::error)
        );
    }
}
