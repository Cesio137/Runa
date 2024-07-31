#include "TCP/TCPClient.h"

namespace Nanometro
{
    bool TCPClient::send(const std::string& message)
    {
        if (!pool && !isConnected() && !message.empty())
            return false;

        asio::post(*pool, std::bind(&TCPClient::package_string, this, message));
        return true;
    }

    bool TCPClient::sendRaw(const std::vector<std::byte>& buffer)
    {
        if (!pool && !isConnected() && !buffer.empty())
            return false;;

        asio::post(*pool, std::bind(&TCPClient::package_buffer, this, buffer));
        return true;
    }

    bool TCPClient::async_read()
    {
        if (!isConnected())
            return false;

        asio::async_read(tcp.socket, response_buffer, asio::transfer_at_least(1),
                         std::bind(&TCPClient::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred)
        );
        return true;
    }

    bool TCPClient::connect()
    {
        if (!pool && isConnected())
            return false;

        asio::post(*pool, std::bind(&TCPClient::run_context_thread, this));
        return true;
    }

    void TCPClient::package_string(const std::string& str)
    {
        mutexBuffer.lock();
        if (!splitBuffer || str.size() <= maxSendBufferSize)
        {
            asio::async_write(tcp.socket, asio::buffer(str.data(), str.size()),
                              std::bind(&TCPClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred));
            mutexBuffer.unlock();
            return;
        }

        size_t string_offset = 0;
        const size_t max_size = maxSendBufferSize;
        while (string_offset < str.size())
        {
            size_t package_size = std::min(max_size, str.size() - string_offset);
            std::string strshrink(str.begin() + string_offset,
                                  str.begin() + string_offset + package_size);
            asio::async_write(tcp.socket, asio::buffer(strshrink.data(), strshrink.size()),
                              std::bind(&TCPClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            string_offset += package_size;
        }
        mutexBuffer.unlock();
    }

    void TCPClient::package_buffer(const std::vector<std::byte>& buffer)
    {
        mutexBuffer.lock();
        if (!splitBuffer || buffer.size() <= maxSendBufferSize)
        {
            asio::async_write(tcp.socket, asio::buffer(buffer.data(), buffer.size()),
                              std::bind(&TCPClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred)
            );
            mutexBuffer.unlock();
            return;
        }

        size_t buffer_offset = 0;
        const size_t max_size = maxSendBufferSize;
        while (buffer_offset < buffer.size())
        {
            size_t package_size = std::min(max_size, buffer.size() - buffer_offset);
            std::vector<std::byte> sbuffer(buffer.begin() + buffer_offset,
                                           buffer.begin() + buffer_offset + package_size);
            asio::async_write(tcp.socket, asio::buffer(sbuffer.data(), sbuffer.size()),
                              std::bind(&TCPClient::write, this, asio::placeholders::error,
                                        asio::placeholders::bytes_transferred));
            buffer_offset += package_size;
        }
        mutexBuffer.unlock();
    }

    void TCPClient::run_context_thread()
    {
        mutexIO.lock();
        while (tcp.attemps_fail <= maxAttemp)
        {
            if (onConnectionRetry && tcp.attemps_fail > 0)
                onConnectionRetry(tcp.attemps_fail);
            tcp.error_code.clear();
            tcp.context.restart();
            tcp.resolver.async_resolve(host, service,
                                       std::bind(&TCPClient::resolve, this, asio::placeholders::error,
                                                 asio::placeholders::endpoint));
            tcp.context.run();
            if (!tcp.error_code) break;
            tcp.attemps_fail++;
            std::this_thread::sleep_for(std::chrono::seconds(timeout));
        }
        consume_response_buffer();
        tcp.attemps_fail = 0;
        mutexIO.unlock();
    }

    void TCPClient::resolve(const std::error_code& error, const asio::ip::tcp::resolver::results_type& endpoints)
    {
        if (error)
        {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }
        // Attempt a connection to each endpoint in the list until we
        // successfully establish a connection.
        tcp.endpoints = endpoints;

        asio::async_connect(tcp.socket, tcp.endpoints,
                            std::bind(&TCPClient::conn, this, asio::placeholders::error)
        );
    }

    void TCPClient::conn(const std::error_code& error)
    {
        if (error)
        {
            tcp.error_code = error;
            if (onError)
                onError(tcp.error_code.value(), tcp.error_code.message());
            return;
        }

        // The connection was successful;
        consume_response_buffer();
        asio::async_read(tcp.socket, response_buffer, asio::transfer_at_least(1),
                         std::bind(&TCPClient::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred)
        );

        if (onConnected)
            onConnected();
    }

    void TCPClient::write(const std::error_code& error, const size_t bytes_sent)
    {
        if (error)
        {
            if (onError)
                onError(error.value(), error.message());
            return;
        }
        if (onMessageSent)
            onMessageSent(bytes_sent);
    }

    void TCPClient::read(const std::error_code& error, const size_t bytes_recvd)
    {
        if (error)
        {
            if (onError)
                onError(error.value(), error.message());
            return;
        }

        FTcpMessage rbuffer;
        rbuffer.size = response_buffer.size();
        rbuffer.raw_data.resize(rbuffer.size);
        asio::buffer_copy(asio::buffer(rbuffer.raw_data, rbuffer.size), response_buffer.data());

        if (onMessageReceived)
            onMessageReceived(bytes_recvd, rbuffer);

        consume_response_buffer();
        asio::async_read(tcp.socket, response_buffer, asio::transfer_at_least(1),
                         std::bind(&TCPClient::read, this, asio::placeholders::error,
                                   asio::placeholders::bytes_transferred));
    }
} // Nanometro
