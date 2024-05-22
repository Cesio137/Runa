#pragma once

#ifndef REQUEST_H
#define REQUEST_H

#include <NetCommon/Netcommon.h>

namespace Nanometro {    

    class Request {
    public:
        Request()
        {
            request.headers.insert_or_assign("Accept", "*/*");
            request.headers.insert_or_assign("User-Agent", "ASIO 2.30.2");
            request.headers.insert_or_assign("Connection", "close");
        }
        Request(const Request& req) 
        {
            request.host = req.GetHost();
            request.path = req.GetPath();
            request.body = req.GetBody();
            request.content = req.GetContent();

            ClearParams();
            request.params = req.GetParams();
            ClearHeaders();
            request.headers = req.GetHeaders();
        }
        Request& operator=(const Request& req) {
            if (this != &req) {
                request.host = req.GetHost();
                request.path = req.GetPath();
                request.body = req.GetBody();
                request.content = req.GetContent();
            }
            return *this;
        }
        ~Request() {}

        void SetHost(const std::string& url = "localhost", const std::string& service = "") { request.host = url; request.service = service; }
        std::string GetHost() const { return request.host; }

        void SetRequest(EHttpVerb request_method = EHttpVerb::GET, const std::string& http_version = "2.0")
        {
            request.verb = request_method;
            request.version = http_version;
        }
        EHttpVerb GetRequestMethod() const { return request.verb; }
        std::string GetHttpVersion() const { return request.version; }

        void SetPath(const std::string& path = "/") 
        {
            if (path.empty()) request.path = "/";
            else request.path = path;
        }
        std::string GetPath() const { return request.path; }

        void AppendParams(const std::string& key, const std::string& value) { request.params.insert_or_assign(key, value); }
        void ClearParams() { request.params.clear(); }
        void RemoveParam(const std::string& key) { request.params.erase(key); }
        std::map<std::string, std::string> GetParams() const { return request.params; }

        void AppendHeaders(const std::string& key, const std::string& value) { request.params.insert_or_assign(key, value); }
        void ClearHeaders() { request.params.clear(); }
        void RemoveHeader(const std::string& key) { request.headers.erase(key); }
        std::map<std::string, std::string> GetHeaders() const { return request.params; }

        void SetBody(const std::string& value) { request.body = value; }
        void ClearBody() { request.body.clear(); }
        std::string GetBody() const { return request.body; }

        void SetContent(const std::string& value) { request.content = value; }
        void ClearContent() { request.content.clear(); }
        std::string GetContent() const { return request.content; }

        void SyncConstructRequest();
        //int SyncProcessRequest();

        std::function<void(const asio::streambuf& res)> OnProcessRequestComplete;
        std::function<void(int BytesSent, int BytesReceived)> OnRequestProgress;

    private:
        std::string exceptions;
        FHttpRequest request;
        const std::map<EHttpVerb, std::string> verb = {
            {EHttpVerb::GET     , "GET"},
            {EHttpVerb::POST    , "POST"},
            {EHttpVerb::PUT     , "PUT"},
            {EHttpVerb::PATCH   , "PATH"},
            {EHttpVerb::DEL     , "DEL"},
            {EHttpVerb::COPY    , "COPY"},
            {EHttpVerb::HEAD    , "HEAD"},
            {EHttpVerb::OPTIONS , "OPTIONS"},
            {EHttpVerb::LOCK    , "LOCK"},
            {EHttpVerb::UNLOCK  , "UNLOCK"},
            {EHttpVerb::PROPFIND, "PROPFIND"}, 
        };
        asio::streambuf request_buffer;
    };

} // Nanometro

#endif //REQUEST_H
