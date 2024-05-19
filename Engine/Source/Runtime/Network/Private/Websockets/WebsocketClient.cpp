#include "Websockets/WebsocketClient.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

namespace Nanometro {
    WebsocketClient::WebsocketClient(): resolver(context), socket(context), idle_work(context)
    {
    }

    WebsocketClient::~WebsocketClient()
    {
    }

    int WebsocketClient::Connect(const std::string& host, const std::string& port)
    {
        // Criação do resolver e resolução do DNS
        asio::ip::basic_resolver_results<asio::ip::tcp> endpoints = resolver.resolve(host, port, error_code);

        // Criação do socket


        // Conexão ao endpoint
        asio::connect(socket, endpoints, error_code);

        if (!error_code) {
            std::cout << "Conectado com sucesso!" << std::endl;
        } else {
            std::cerr << "Falha ao conectar: " << error_code.message() << std::endl;
            return 1;
        }

        // Enviando o handshake do WebSocket
        request =
            "GET / HTTP/1.1\r\n"
            "Host: " + endpoints->host_name() + "\r\n"
            "Upgrade: websocket\r\n"
            "Connection: Upgrade\r\n"
            "Sec-WebSocket-Key: x3JJHMbDL1EzLkh9GBhXDw==\r\n"
            "Sec-WebSocket-Protocol: chat, superchat\r\n"
            "Sec-WebSocket-Version: " + protocol_version + "\r\n"
            "\r\n";

        socket.write_some(asio::buffer(request.data(), request.size()), error_code);

        // Lendo a resposta do handshake
        asio::streambuf buffer;
        asio::read_until(socket, buffer, "\r\n\r\n", error_code);

        // Verificando se o handshake foi bem-sucedido
        std::istream response_stream(&buffer);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);

        if (status_code != 101) {
            std::cerr << "Handshake falhou! Código de status: " << status_code << std::endl;
            return 1;
        } else {

        }

        // Enviando e recebendo dados do WebSocket
        // O código para enviar e receber dados vai aqui

        return 0;
    }

    void WebsocketClient::Close()
    {
        socket.close(error_code);
    }

    bool WebsocketClient::is_open()
    {
        return socket.is_open();
    }

    void WebsocketClient::Send(const std::string &message)
    {
        socket.write_some(asio::buffer(message.data(), message.size()));
    }
}

