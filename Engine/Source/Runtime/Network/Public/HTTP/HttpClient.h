#pragma once

#include "Net/Common.h"

namespace Nanometro {
    class HttpClient {
    public:
        HttpClient() {
            request.headers.insert_or_assign("Accept", "*/*");
            request.headers.insert_or_assign("User-Agent", "ASIO 2.30.2");
            request.headers.insert_or_assign("Connection", "close");
        }

        ~HttpClient() {
            tcp.context.stop();
            pool->stop();
            clearRequest();
            clearPayload();
            clearResponse();
        }

        /*HTTP SETTINGS*/

        void setHost(const std::string &url = "localhost", const std::string &port = "") {
            host = url;
            service = port;
        }

        std::string getHost() const { return host; }
        std::string getPort() const { return service; }

        void setTimeout(uint8_t value = 3) { timeout = value; }
        uint8_t getTimeout() const { return timeout; }

        void setMaxAttemp(uint8_t value = 3) { maxAttemp = value; }
        uint8_t getMaxAttemp() const { return timeout; }

        /*REQUEST DATA*/
        void setRequest(const FRequest &value) { request = value; }
        FRequest getRequest() const { return request; }

        void setRequestMethod(EVerb requestMethod = EVerb::GET) { request.verb = requestMethod; }
        EVerb getRequestMethod() const { return request.verb; }

        void setVersion(const std::string &version = "2.0") { request.version = version; }
        std::string getVersion() const { return request.version; }

        void setPath(const std::string &path = "/") { request.path = path.empty() ? "/" : path; }
        std::string getPath() const { return request.path; }

        void appendParams(const std::string &key, const std::string &value) { request.params[key] = value; }
        void clearParams() { request.params.clear(); }
        void removeParam(const std::string &key) { request.params.erase(key); }
        bool hasParam(const std::string &key) const { return request.params.contains(key); }
        std::map<std::string, std::string> getParams() const { return request.params; }

        void AppendHeaders(const std::string &key, const std::string &value) { request.headers[key] = value; }
        void ClearHeaders() { request.headers.clear(); }
        void RemoveHeader(const std::string &key) { request.headers.erase(key); }
        bool hasHeader(const std::string &key) const { return request.headers.contains(key); }
        std::map<std::string, std::string> GetHeaders() const { return request.headers; }

        void SetBody(const std::string &value) { request.body = value; }
        void ClearBody() { request.body.clear(); }
        std::string GetBody() const { return request.body; }

        FRequest getRequestData() const { return request; }

        /*PAYLOAD*/
        void preparePayload();

        void async_preparePayload();

        std::string getPayloadData() const { return payload; }

        /*RESPONSE DATA*/
        FResponse getResponseData() const { return response; }

        /*CONNECTION*/
        bool processRequest();

        void cancelRequest(bool forceClose = false) {
            tcp.context.stop();
            if (forceClose) {
                tcp.socket.close(tcp.error_code);
                if (tcp.error_code && onError)
                    onError(tcp.error_code.value(), tcp.error_code.message());
            } else {
                tcp.socket.shutdown(asio::ip::tcp::socket::shutdown_both, tcp.error_code);
                if (tcp.error_code && onError)
                    onError(tcp.error_code.value(), tcp.error_code.message());
                tcp.socket.close(tcp.error_code);
                if (tcp.error_code && onError)
                    onError(tcp.error_code.value(), tcp.error_code.message());
            }
            pool->join();
            if (onRequestCanceled) onRequestCanceled();
        }

        /*MEMORY MANAGER*/
        void clearRequest() { request.clear(); }
        void clearPayload() { payload.clear(); }
        void clearResponse() { response.clear(); }

        /*ERRORS*/
        int getErrorCode() const { return tcp.error_code.value(); }
        std::string getErrorMessage() const { return tcp.error_code.message(); }

        /*EVENTS*/
        std::function<void()> onAsyncPayloadFinished;
        std::function<void(const FResponse)> onRequestComplete;
        std::function<void()> onRequestCanceled;
        std::function<void(const size_t, const size_t)> onRequestProgress;
        std::function<void(const int)> onRequestWillRetry;
        std::function<void(const int, const std::string &)> onRequestFail;
        std::function<void(const int)> onResponseFail;
        std::function<void(const int, const std::string &)> onError;

    private:
        std::unique_ptr<asio::thread_pool> pool = std::make_unique<asio::thread_pool>(
            std::thread::hardware_concurrency());
        std::mutex mutexPayload;
        std::mutex mutexIO;
        std::string host = "localhost";
        std::string service;
        uint8_t timeout = 3;
        uint8_t maxAttemp = 3;
        FRequest request;
        FAsioTcp tcp;
        std::string payload;
        asio::streambuf request_buffer;
        asio::streambuf response_buffer;
        FResponse response;
        const std::map<EVerb, std::string> verb = {
            {EVerb::GET, "GET"},
            {EVerb::POST, "POST"},
            {EVerb::PUT, "PUT"},
            {EVerb::PATCH, "PATCH"},
            {EVerb::DEL, "DELETE"},
            {EVerb::COPY, "COPY"},
            {EVerb::HEAD, "HEAD"},
            {EVerb::OPTIONS, "OPTIONS"},
            {EVerb::LOCK, "LOCK"},
            {EVerb::UNLOCK, "UNLOCK"},
            {EVerb::PROPFIND, "PROPFIND"},
        };

        void run_context_thread();

        void consume_stream_buffers() {
            request_buffer.consume(request_buffer.size());
            response_buffer.consume(request_buffer.size());
        }

        void resolve(const std::error_code &error, const asio::ip::tcp::resolver::results_type &endpoints);

        void connect(const std::error_code &error);

        void write_request(const std::error_code &error, const size_t bytes_sent);

        void read_status_line(const std::error_code &error, const size_t bytes_sent, const size_t bytes_recvd);

        void read_headers(const std::error_code &error);

        void read_content(const std::error_code &error);
    };

    class HttpClientSsl {
    public:
        HttpClientSsl() {
            request.headers.insert_or_assign("Accept", "*/*");
            request.headers.insert_or_assign("User-Agent", "ASIO 2.30.2");
            request.headers.insert_or_assign("Connection", "close");
        }

        ~HttpClientSsl() {
            tcp.context.stop();
            pool->stop();
            clearRequest();
            clearPayload();
            clearResponse();
        }

        /*HTTP SETTINGS*/

        void setHost(const std::string &url = "localhost", const std::string &port = "") {
            host = url;
            service = port;
        }

        std::string getHost() const { return host; }
        std::string getPort() const { return service; }

        void setTimeout(uint8_t value = 3) { timeout = value; }
        uint8_t getTimeout() const { return timeout; }

        void setMaxAttemp(uint8_t value = 3) { maxAttemp = value; }
        uint8_t getMaxAttemp() const { return timeout; }

        /*REQUEST DATA*/
        void setRequest(const FRequest &value) { request = value; }
        FRequest getRequest() const { return request; }

        void setRequestMethod(EVerb requestMethod = EVerb::GET) { request.verb = requestMethod; }
        EVerb getRequestMethod() const { return request.verb; }

        void setVersion(const std::string &version = "2.0") { request.version = version; }
        std::string getVersion() const { return request.version; }

        void setPath(const std::string &path = "/") { request.path = path.empty() ? "/" : path; }
        std::string getPath() const { return request.path; }

        void appendParams(const std::string &key, const std::string &value) { request.params[key] = value; }
        void clearParams() { request.params.clear(); }
        void removeParam(const std::string &key) { request.params.erase(key); }
        bool hasParam(const std::string &key) const { return request.params.contains(key); }
        std::map<std::string, std::string> getParams() const { return request.params; }

        void AppendHeaders(const std::string &key, const std::string &value) { request.headers[key] = value; }
        void ClearHeaders() { request.headers.clear(); }
        void RemoveHeader(const std::string &key) { request.headers.erase(key); }
        bool hasHeader(const std::string &key) const { return request.headers.contains(key); }
        std::map<std::string, std::string> GetHeaders() const { return request.headers; }

        void SetBody(const std::string &value) { request.body = value; }
        void ClearBody() { request.body.clear(); }
        std::string GetBody() const { return request.body; }

        FRequest getRequestData() const { return request; }

        /*SECURITY LAYER*/
        bool load_private_key_data(const std::string &key_data) {
            try {
                const asio::const_buffer buffer(key_data.data(), key_data.size());
                tcp.ssl_context.use_private_key(buffer, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_private_key_file(const std::string &filename) {
            try {
                tcp.ssl_context.use_private_key_file(filename, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_data(const std::string &cert_data) {
            try {
                const asio::const_buffer buffer(cert_data.data(), cert_data.size());
                tcp.ssl_context.use_certificate(buffer, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_file(const std::string &filename) {
            try {
                tcp.ssl_context.use_certificate_file(filename, asio::ssl::context::pem);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_chain_data(const std::string &cert_chain_data) {
            try {
                const asio::const_buffer buffer(cert_chain_data.data(),
                                                cert_chain_data.size());
                tcp.ssl_context.use_certificate_chain(buffer);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_certificate_chain_file(const std::string &filename) {
            try {
                tcp.ssl_context.use_certificate_chain_file(filename);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        bool load_verify_file(const std::string &filename) {
            try {
                tcp.ssl_context.load_verify_file(filename);
            } catch (const std::exception &e) {
                if (onError) onError(-1, e.what());
                return false;
            }
            return true;
        }

        /*PAYLOAD*/
        void preparePayload();

        void async_preparePayload();

        std::string getPayloadData() const { return payload; }

        /*RESPONSE DATA*/
        FResponse getResponseData() const { return response; }

        /*CONNECTION*/
        bool processRequest();

        void cancelRequest(bool forceClose = false) {
            tcp.context.stop();
            tcp.ssl_socket.shutdown(tcp.error_code);
            tcp.ssl_socket.async_shutdown([&](const std::error_code &error) {
                if (error) {
                    tcp.error_code = error;
                    if (onError) onError(error.value(), error.message());
                }

                if (forceClose) {
                    tcp.ssl_socket.lowest_layer().close(tcp.error_code);
                    if (tcp.error_code && onError)
                        onError(tcp.error_code.value(), tcp.error_code.message());
                } else {
                    tcp.ssl_socket.lowest_layer().shutdown(
                        asio::ip::tcp::socket::shutdown_both, tcp.error_code);
                    if (tcp.error_code && onError)
                        onError(tcp.error_code.value(), tcp.error_code.message());

                    tcp.ssl_socket.lowest_layer().close(tcp.error_code);
                    if (tcp.error_code && onError)
                        onError(tcp.error_code.value(), tcp.error_code.message());
                }
                if (onRequestCanceled) onRequestCanceled();
            });
        }

        /*MEMORY MANAGER*/
        void clearRequest() { request.clear(); }
        void clearPayload() { payload.clear(); }
        void clearResponse() { response.clear(); }

        /*ERRORS*/
        int getErrorCode() const { return tcp.error_code.value(); }
        std::string getErrorMessage() const { return tcp.error_code.message(); }

        /*EVENTS*/
        std::function<void()> onAsyncPayloadFinished;
        std::function<void(const FResponse)> onRequestComplete;
        std::function<void()> onRequestCanceled;
        std::function<void(const size_t, const size_t)> onRequestProgress;
        std::function<void(const int)> onRequestWillRetry;
        std::function<void(const int, const std::string &)> onRequestFail;
        std::function<void(const int)> onResponseFail;
        std::function<void(const int, const std::string &)> onError;

    private:
        std::unique_ptr<asio::thread_pool> pool = std::make_unique<asio::thread_pool>(
            std::thread::hardware_concurrency());
        std::mutex mutexPayload;
        std::mutex mutexIO;
        std::string host = "localhost";
        std::string service;
        uint8_t timeout = 3;
        uint8_t maxAttemp = 3;
        FRequest request;
        FAsioTcpSsl tcp;
        std::string payload;
        asio::streambuf request_buffer;
        asio::streambuf response_buffer;
        FResponse response;
        const std::map<EVerb, std::string> verb = {
            {EVerb::GET, "GET"},
            {EVerb::POST, "POST"},
            {EVerb::PUT, "PUT"},
            {EVerb::PATCH, "PATCH"},
            {EVerb::DEL, "DELETE"},
            {EVerb::COPY, "COPY"},
            {EVerb::HEAD, "HEAD"},
            {EVerb::OPTIONS, "OPTIONS"},
            {EVerb::LOCK, "LOCK"},
            {EVerb::UNLOCK, "UNLOCK"},
            {EVerb::PROPFIND, "PROPFIND"},
        };

        void run_context_thread();

        void consume_stream_buffers() {
            request_buffer.consume(request_buffer.size());
            response_buffer.consume(request_buffer.size());
        }

        void resolve(const std::error_code &error, const asio::ip::tcp::resolver::results_type &endpoints);

        void connect(const std::error_code &error);

        void ssl_handshake(const std::error_code &error);

        void write_request(const std::error_code &error, const size_t bytes_sent);

        void read_status_line(const std::error_code &error, const size_t bytes_sent, const size_t bytes_recvd);

        void read_headers(const std::error_code &error);

        void read_content(const std::error_code &error);
    };
} // namespace Nanometro
