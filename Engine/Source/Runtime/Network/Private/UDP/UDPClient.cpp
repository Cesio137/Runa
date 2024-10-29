#include "UDP/UDPClient.h"

namespace Nanometro
{
    bool UDPClient::send(const std::string& message)
    {
        if (!pool && !isConnected() && !message.empty())
            return false;

        asio::post(*pool, std::bind(&UDPClient::package_string, this, message));
        return true;
    }

    bool UDPClient::sendRaw(const std::vector<std::byte>& buffer)
    {
        if (!pool && !isConnected() && !buffer.empty())
            return false;

        asio::post(*pool, std::bind(&UDPClient::package_buffer, this, buffer));
        return true;
    }

    bool UDPClient::async_read()
    {
        if (!isConnected())
            return false;

        udp.socket.async_receive_from(asio::buffer(rbuffer.rawData, rbuffer.rawData.size()), udp.endpoints,
                                      std::bind(&UDPClient::receive_from, this, asio::placeholders::error,
                                                asio::placeholders::bytes_transferred));
        return true;
    }

    bool UDPClient::connect()
    {
        if (!pool && isConnected())
            return false;

        asio::post(*pool, std::bind(&UDPClient::run_context_thread, this));
        return true;
    }

    void UDPClient::package_string(const std::string& str)
    {
        mutexBuffer.lock();
        if (!splitBuffer || str.size() <= maxSendBufferSize)
        {
            udp.socket.async_send_to(asio::buffer(str.data(), str.size()), udp.endpoints,
                                     std::bind(&UDPClient::send_to, this, asio::placeholders::error,
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
            udp.socket.async_send_to(asio::buffer(strshrink.data(), strshrink.size()), udp.endpoints,
                                     std::bind(&UDPClient::send_to, this, asio::placeholders::error,
                                               asio::placeholders::bytes_transferred));
            string_offset += package_size;
        }
        mutexBuffer.unlock();
    }

    void UDPClient::package_buffer(const std::vector<std::byte>& buffer)
    {
        mutexBuffer.lock();
        if (!splitBuffer || buffer.size() <= maxSendBufferSize)
        {
            udp.socket.async_send_to(asio::buffer(buffer.data(), buffer.size()), udp.endpoints,
                                     std::bind(&UDPClient::send_to, this, asio::placeholders::error,
                                               asio::placeholders::bytes_transferred));
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
            udp.socket.async_send_to(asio::buffer(sbuffer.data(), sbuffer.size()), udp.endpoints,
                                     std::bind(&UDPClient::send_to, this, asio::placeholders::error,
                                               asio::placeholders::bytes_transferred));
            buffer_offset += package_size;
        }
        mutexBuffer.unlock();
    }

    void UDPClient::run_context_thread()
    {
        mutexIO.lock();
        while (udp.attemps_fail <= maxAttemp)
        {
            if (onConnectionRetry && udp.attemps_fail > 0)
                onConnectionRetry(udp.attemps_fail);
            udp.error_code.clear();
            udp.context.restart();
            udp.resolver.async_resolve(asio::ip::udp::v4(), host, service,
                                       std::bind(&UDPClient::resolve, this, asio::placeholders::error,
                                                 asio::placeholders::results));
            udp.context.run();
            if (!udp.error_code) break;
            udp.attemps_fail++;
            std::this_thread::sleep_for(std::chrono::seconds(timeout));
        }
        consume_receive_buffer();
        udp.attemps_fail = 0;
        mutexIO.unlock();
    }

    void UDPClient::resolve(const std::error_code& error, const asio::ip::udp::resolver::results_type& results)
    {
        if (error)
        {
            udp.error_code = error;
            if (onError) onError(error.value(), error.message());
            return;
        }
        udp.endpoints = *results;
        udp.socket.async_connect(udp.endpoints,
                                 std::bind(&UDPClient::conn, this, asio::placeholders::error));
    }

    void UDPClient::conn(const std::error_code& error)
    {
        if (error)
        {
            udp.error_code = error;
            if (onError) onError(error.value(), error.message());
            return;
        }
        consume_receive_buffer();
        udp.socket.async_receive_from(asio::buffer(rbuffer.rawData, rbuffer.rawData.size()), udp.endpoints,
                                      std::bind(&UDPClient::receive_from, this, asio::placeholders::error,
                                                asio::placeholders::bytes_transferred));

        if (onConnected)
            onConnected();
    }

    void UDPClient::send_to(const std::error_code& error, const size_t bytes_sent)
    {
        if (error)
        {
            udp.error_code = error;
            if (onError) onError(error.value(), error.message());
            return;
        }

        if (onMessageSent)
            onMessageSent(bytes_sent);
    }

    void UDPClient::receive_from(const std::error_code& error, const size_t bytes_recvd)
    {
        if (error)
        {
            udp.error_code = error;
            if (onError) onError(error.value(), error.message());
            return;
        }

        udp.attemps_fail = 0;
        rbuffer.size = bytes_recvd;
        rbuffer.rawData.resize(bytes_recvd);
        if (onMessageReceived)
            onMessageReceived(bytes_recvd, rbuffer);

        consume_receive_buffer();
        udp.socket.async_receive_from(asio::buffer(rbuffer.rawData, rbuffer.rawData.size()), udp.endpoints,
                                      std::bind(&UDPClient::receive_from, this, asio::placeholders::error,
                                                asio::placeholders::bytes_transferred));
    }
} // Nanometro
