#include "TCP/TCPClient.h"

namespace Nanometro {
    void TCPClient::send(const std::string &message)
    {
        if (!pool || !isConnected())
        	return;

        asio::post(*pool, [this, message]() {
			std::vector<char> buffer(message.begin(), message.end());
			if (buffer.back() != '\0')
				buffer.push_back('\0');
			package_buffer(buffer);
		});
    }

    void TCPClient::sendRaw(const std::vector<char> &buffer)
    {
        if (!pool || !isConnected())
            return;

        asio::post(*pool, [this, buffer]() {
            package_buffer(buffer);
        });
    }

    void TCPClient::connect()
    {
        if (!pool)
			return;

		asio::post(*pool, [this]() {
		    runContextThread();
		});
    }

    void TCPClient::runContextThread()
    {
        mutexIO.lock();
        tcp.context.restart();
        tcp.resolver.async_resolve(host, service, 
            std::bind(&TCPClient::resolve, this, asio::placeholders::error, asio::placeholders::endpoint)
        );
        tcp.context.run();
        if (tcp.error_code && maxAttemp > 0 && timeout > 0) {
        	uint8_t attemp = 0;
        	while(attemp < maxAttemp) {
        		if (onConnectionRetry)
        			onConnectionRetry(attemp + 1);
        		tcp.error_code.clear();
        		tcp.context.restart();
        		asio::steady_timer timer(tcp.context, asio::chrono::seconds(timeout));
        		timer.async_wait([this](const std::error_code& error) {
					if (error) {
						if (onConnectionError)
							onConnectionError(error.value(), error.message());
					}
        			tcp.resolver.async_resolve(host, service,
						std::bind(&TCPClient::resolve, this, asio::placeholders::error, asio::placeholders::endpoint)
					);
				});
        		tcp.context.run();
        		attemp += 1;
        		if(!tcp.error_code)
        			break;
        	}
        }
        mutexIO.unlock();
    }

    void TCPClient::resolve(const std::error_code &error, const asio::ip::tcp::resolver::results_type &endpoints)
    {
        if (error) {
			tcp.error_code = error;
			if (onConnectionError)
				onConnectionError(tcp.error_code.value(), tcp.error_code.message());
			return;
		}
		// Attempt a connection to each endpoint in the list until we
		// successfully establish a connection.
		tcp.endpoints = endpoints;
		asio::async_connect(tcp.socket, tcp.endpoints,
			std::bind(&TCPClient::conn, this, asio::placeholders::error)
		);
    }

    void TCPClient::conn(std::error_code error)
    {
        if (error) {
			tcp.error_code = error;
			if (onConnectionError)
				onConnectionError(tcp.error_code.value(), tcp.error_code.message());
			return;
		}
		// The connection was successful;
        asio::async_read(tcp.socket, asio::buffer(rbuffer.message, rbuffer.message.size()), asio::transfer_at_least(1),
			std::bind(&TCPClient::read, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
		);
		if (onConnected)
			onConnected();
    }
    
    void TCPClient::package_buffer(const std::vector<char>& buffer)
    {
        mutexBuffer.lock();
        if (!splitBuffer || buffer.size() <= maxBufferSize) {
            asio::async_write(tcp.socket, asio::buffer(buffer.data(), buffer.size()),
                std::bind(&TCPClient::write, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            );
            mutexBuffer.unlock();
            return;
        }
        size_t buffer_offset = 0;
        const size_t max_size = maxBufferSize - 1;
        while (buffer_offset < buffer.size()) {
            size_t package_size = std::min(max_size, buffer.size() - buffer_offset);
            std::vector<char> sbuffer = std::vector<char>(buffer.begin() + buffer_offset, buffer.begin() + buffer_offset + package_size);
            if (sbuffer.back() != '\0')
                sbuffer.push_back('\0');
            asio::async_write(tcp.socket, asio::buffer(sbuffer.data(), sbuffer.size()),
                std::bind(&TCPClient::write, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
            );
            buffer_offset += package_size;
        }
        mutexBuffer.unlock();
    }

    void TCPClient::write(std::error_code error, std::size_t bytes_sent)
    {
        if (error) {
        	if (onMessageSentError)
        		onMessageSentError(error.value(), error.message());
        	return;
        }
        if (onMessageSent)
        	onMessageSent(bytes_sent);
    }

    void TCPClient::read(std::error_code error, std::size_t bytes_recvd)
    {
        if (error) {
            if (onMessageReceivedError)
                onMessageReceivedError(error.value(), error.message());
            return;
        }
        rbuffer.size = bytes_recvd;
        if (onMessageReceived)
            onMessageReceived(bytes_recvd, rbuffer);
        asio::async_read(tcp.socket, asio::buffer(rbuffer.message, rbuffer.message.size()), asio::transfer_at_least(1),
			std::bind(&TCPClient::read, this, asio::placeholders::error, asio::placeholders::bytes_transferred)
		);
    }
} // Nanometro
