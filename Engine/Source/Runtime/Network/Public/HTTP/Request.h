#pragma once

#ifndef REQUEST_H
#define REQUEST_H

#include <NetCommon/Netcommon.h>

namespace Nanometro {    

    class Request {
    public:
        Request();
        ~Request();

        void SetHost(const std::string& url = "localhost", const std::string& service = "");
        std::string GetHost() const { return Req.host; }

        void SetRequest(EHttpVerb request_method = EHttpVerb::GET, const std::string& http_version = "2.0");
        EHttpVerb GetRequestMethod() const { return Req.verb; }
        std::string GetHttpVersion() const { return Req.version; }

        void SetPath(const std::string& path = "/");
        std::string GetPath() const { return Req.path; }

        void AppendParams(const std::string& key, const std::string& value);
        void ClearParams();
        void RemoveParam(const std::string& key) { Req.params.erase(key); }
        std::map<std::string, std::string> GetParams() const { return Req.params; }

        void AppendHeader(const std::string& key, const std::string& value);
        void ClearHeader();
        void RemoveHeader(const std::string& key) { Req.headers.erase(key); }
        std::map<std::string, std::string> GetHeader() const { return Req.params; }

        void SetBody(const std::string& value);
        void ClearBody();
        std::string GetBody() const { return Req.body; }

        void SetContent(const std::string& value);
        void ClearContent();
        std::string GetContent() const { return Req.content; }

        int SyncConstructRequest();
        int SyncProcessRequest();

        std::function<void(const asio::streambuf& res)> OnProcessRequestComplete;
        std::function<void(int BytesSent, int BytesReceived)> OnRequestProgress;

    private:
        std::string exceptions;
        FAsio HttpContext;
        FHttpRequest Req;
        std::map<EHttpVerb, std::string> const verb = { 
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
        asio::streambuf request;
        std::ostream request_stream;
    };

} // Nanometro

#endif //REQUEST_H
