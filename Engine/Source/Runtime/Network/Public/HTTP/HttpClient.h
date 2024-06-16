#pragma once

#include "Net/Common.h"

namespace Nanometro {
    class HttpClient
	{
	public:
		HttpClient() {
			request.headers.insert_or_assign("Accept", "*/*");
			request.headers.insert_or_assign("User-Agent", "ASIO 2.30.2");
			request.headers.insert_or_assign("Connection", "close");
		}
		~HttpClient() {
			clearRequest();
			clearPayload();
			clearResponse();
		}

		/*HTTP SETTINGS*/

		void setHost(const std::string& url = "localhost", const std::string& port = "")
		{
			host = url;
			service = port;
		}
		std::string getHost() const { return host; }
		std::string getPort() const { return service; }

		void setRetryTime(int value = 3.) { retrytime = value; }
		void resetRetryTime() { retrytime = 5; }
		int getRetryTime() const { return retrytime; }

		void setMaxRetry(int value = 1) { maxretry = value; }
		void resetMaxRetry() { maxretry = 1; }
		int getMaxRetry() const { return  maxretry; }
		
		/*REQUEST DATA*/
		void setRequest(const FRequest& value) { request = value; }
		FRequest getRequest() const { return request; }
		
		void setRequestMethod(EVerb requestMethod = EVerb::GET) { request.verb = requestMethod; }
		EVerb getRequestMethod() const { return request.verb; }

		void setVersion(const std::string& version = "2.0")	{ request.version = version; }
		std::string getVersion() const { return request.version; }

		void setPath(const std::string& path = "/") { request.path = path.empty() ? "/" : path; }
		std::string getPath() const { return request.path; }

		void appendParams(const std::string& key, const std::string& value) { request.params[key] = value; }
		void clearParams() { request.params.clear(); }
		void removeParam(const std::string& key) { request.params.erase(key); }
		bool hasParam(const std::string& key) const { return request.params.contains(key); }
		std::map<std::string, std::string> getParams() const { return request.params; }

		void AppendHeaders(const std::string& key, const std::string& value) { request.headers[key] = value; }
		void ClearHeaders() { request.headers.clear(); }
		void RemoveHeader(const std::string& key) { request.headers.erase(key); }
		bool hasHeader(const std::string& key) const { return request.headers.contains(key); }
		std::map<std::string, std::string> GetHeaders() const { return request.headers; }

		void SetBody(const std::string& value) { request.body = value; }
		void ClearBody() { request.body.clear(); }
		std::string GetBody() const { return request.body; }

		FRequest getRequestData() const { return request; }

		/*PAYLOAD*/
		void preparePayload();
		void async_preparePayload();
		std::string getPayloadData() const { return payload; }

		/*RESPONSE DATA*/
		FResponse getResponseData() const { return response; }

		/*THREADS*/
		void setThreadNumber(int value = 2) { pool = std::make_unique<asio::thread_pool>(value); }

		/*CONNECTION*/
		int processRequest();

		void cancelRequest() { tcp.context.stop(); }

		/*MEMORY MANAGER*/
		void clearRequest() { request.clear(); }
		void clearPayload() { payload.clear(); }
		void clearResponse() { response.clear(); }

		/*ERRORS*/
		int getErrorCode() const { return tcp.error_code.value(); }
		std::string getErrorMessage() const { return tcp.error_code.message(); }

		/*EVENTS*/
		std::function<void()> onConnected;
		std::function<void()> onAsyncPayloadFinished;
		std::function<void(const FResponse)> onRequestComplete;
		std::function<void(int, int)> onRequestProgress;
		std::function<void(int, int)> onRequestWillRetry;
		std::function<void(int, const std::string&)> onRequestFail;
		std::function<void(EStatusCode)> onResponseFail;
		
	private:
		std::unique_ptr<asio::thread_pool> pool = std::make_unique<asio::thread_pool>(2);
		std::mutex mutexPayload;
		std::mutex mutexIO;
		std::string host = "localhost";
		std::string service;
		int maxretry = 1;
		int retrytime = 3;
		FRequest request;
		FAsioTcp tcp;
		std::string payload;
		asio::streambuf request_buffer;
		asio::streambuf response_buffer;
		FResponse response;
		int bytes_sent = 0;
		int bytes_received = 0;
		const std::map<EVerb, std::string> verb = {
			{EVerb::GET     , "GET"},
			{EVerb::POST    , "POST"},
			{EVerb::PUT     , "PUT"},
			{EVerb::PATCH   , "PATCH"},
			{EVerb::DEL     , "DELETE"},
			{EVerb::COPY    , "COPY"},
			{EVerb::HEAD    , "HEAD"},
			{EVerb::OPTIONS , "OPTIONS"},
			{EVerb::LOCK    , "LOCK"},
			{EVerb::UNLOCK  , "UNLOCK"},
			{EVerb::PROPFIND, "PROPFIND"},
		};

		void runContextThread();
		void clearStreamBuffers()
		{
			request_buffer.consume(request_buffer.size());
			response_buffer.consume(request_buffer.size());
			bytes_sent = 0;
			bytes_received = 0;
		}
		
		void resolve(const std::error_code& err, const asio::ip::tcp::resolver::results_type& endpoints);
		void connect(const std::error_code& err);
		void write_request(const std::error_code& err);
		void read_status_line(const std::error_code& err);
		void read_headers(const std::error_code& err);
		void read_content(const std::error_code& err);
	};
    
} // namespace Nanometro