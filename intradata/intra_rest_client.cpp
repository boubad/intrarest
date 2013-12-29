//intra_rest_client.cpp
/////////////////////////////
#include "intra_rest_client.h"
///////////////////////////////////
namespace intra {
	////////////////////////////////
	using namespace web;
	using namespace web::http;
	using namespace web::http::client;
	////////////////////////////////////
	const Char *IntraRESTClient::DEFAULT_BASE_URI = U("http://caprica");
	//////////////////////////////////////
	IntraRESTClient::IntraRESTClient(const String &baseUri) :
		m_baseUri(baseUri) {
	}

	IntraRESTClient::IntraRESTClient(const IntraRESTClient & orig) :
		m_baseUri(orig.m_baseUri) {
	}

	IntraRESTClient::~IntraRESTClient() {
	}
	/////////////////////////////////////////
	pplx::task<String> IntraRESTClient::intern_get_text_task(const String &uri) const{
		const String &baseUri = this->baseUri();
		web::http::client::http_client client(baseUri);
		web::http::http_request request(web::http::methods::GET);
		request.headers().add(U("accept"), U("text/plain"));
		utility::stringstream_t os;
		os << U("predserver/api/global/") << uri;
		String s = os.str();
		request.set_request_uri(s);
		return client.request(request).then([](web::http::http_response response){
			if (response.status_code() == web::http::status_codes::OK){
				return (response.extract_string());
			}
			else {
				return (pplx::task_from_result(String()));
			}
		});
	}// intern_get_text_task
	
	pplx::task<String> IntraRESTClient::intern_get_text_task(const String &uri, const int arg1) const{
		const String &baseUri = this->baseUri();
		web::http::client::http_client client(baseUri);
		web::http::http_request request(web::http::methods::GET);
		request.headers().add(U("accept"), U("text/plain"));
		utility::stringstream_t os;
		os << U("predserver/api/global/") << uri << U("/") << arg1;
		String s = os.str();
		request.set_request_uri(s);
		return client.request(request).then([](web::http::http_response response){
			if (response.status_code() == web::http::status_codes::OK){
				return (response.extract_string());
			}
			else {
				return (pplx::task_from_result(String()));
			}
		});
	}// intern_get_text_task
	pplx::task<web::json::value> IntraRESTClient::intern_get_json_task(const String &uri) const{
		const String &baseUri = this->baseUri();
		web::http::client::http_client client(baseUri);
		web::http::http_request request(web::http::methods::GET);
		request.headers().add(U("accept"), U("application/json"));
		utility::stringstream_t os;
		os << U("predserver/api/global/") << uri;
		String s = os.str();
		request.set_request_uri(s);
		return client.request(request).then([](web::http::http_response response){
			if (response.status_code() == web::http::status_codes::OK){
				return (response.extract_json());
			}
			else {
				return (pplx::task_from_result(web::json::value()));
			}
		});
	}// intern_get_json_task
	pplx::task<web::json::value> IntraRESTClient::intern_get_json_task(const String &uri, const int arg1) const{
		const String &baseUri = this->baseUri();
		web::http::client::http_client client(baseUri);
		web::http::http_request request(web::http::methods::GET);
		request.headers().add(U("accept"), U("application/json"));
		utility::stringstream_t os;
		os << U("predserver/api/global/") << uri << U("/") << arg1;
		String s = os.str();
		request.set_request_uri(s);
		return client.request(request).then([](web::http::http_response response){
			if (response.status_code() == web::http::status_codes::OK){
				return (response.extract_json());
			}
			else {
				return (pplx::task_from_result(web::json::value()));
			}
		});
	}// intern_get_json_task
	pplx::task<web::json::value> IntraRESTClient::intern_get_json_task(const String &uri, const int arg1, const int arg2) const{
		const String &baseUri = this->baseUri();
		web::http::client::http_client client(baseUri);
		web::http::http_request request(web::http::methods::GET);
		request.headers().add(U("accept"), U("application/json"));
		utility::stringstream_t os;
		os << U("predserver/api/global/") << uri << U("/") << arg1 << U("/") << arg2;
		String s = os.str();
		request.set_request_uri(s);
		return client.request(request).then([](web::http::http_response response){
			if (response.status_code() == web::http::status_codes::OK){
				return (response.extract_json());
			}
			else {
				return (pplx::task_from_result(web::json::value()));
			}
		});
	}// intern_get_json_task
	pplx::task<web::json::value> IntraRESTClient::intern_get_json_task(const String &uri, const int arg1, const int arg2, const int arg3) const{
		const String &baseUri = this->baseUri();
		web::http::client::http_client client(baseUri);
		web::http::http_request request(web::http::methods::GET);
		request.headers().add(U("accept"), U("application/json"));
		utility::stringstream_t os;
		os << U("predserver/api/global/") << uri << U("/") << arg1 << U("/") << arg2 << U("/") << arg3;
		String s = os.str();
		request.set_request_uri(s);
		return client.request(request).then([](web::http::http_response response){
			if (response.status_code() == web::http::status_codes::OK){
				return (response.extract_json());
			}
			else {
				return (pplx::task_from_result(web::json::value()));
			}
		});
	}// intern_get_json_task
	/////////////////////////////////////
	pplx::task<bool> IntraRESTClient::is_connected_async(void) const {
		return this->intern_get_text_task(U("status")).then([](pplx::task<String> pTask){
			bool oRet = false;
			try {
				String s = pTask.get();
				oRet = (s == U("OK"));
			}
			catch (const http_exception & /*e */) {

			}
			return pplx::task_from_result(oRet);
		});
	}    //is_connected_async
	pplx::task<int> IntraRESTClient::get_all_datasets_count_async(void) const{
		return this->intern_get_json_task(U("dataset/count")).then([](pplx::task<json::value> pTask){
			int oRet = 0;
			try {
				const json::value &vv = pTask.get();
				if ((!vv.is_null()) && vv.is_number()) {
					oRet = vv.as_integer();
				}
			}
			catch (const http_exception & /*e */) {

			}
			return pplx::task_from_result(oRet);
		});
	}// get_all_datasets_count_async
	pplx::task<int> IntraRESTClient::get_datalines_count_async(const int datasetid) const{
		return this->intern_get_json_task(U("reader/count"),datasetid).then([](pplx::task<json::value> pTask){
			int oRet = 0;
			try {
				const json::value &vv = pTask.get();
				if ((!vv.is_null()) && vv.is_number()) {
					oRet = vv.as_integer();
				}
			}
			catch (const http_exception & /*e */) {

			}
			return pplx::task_from_result(oRet);
		});
	}// get_datalines_count_async 
	////////////////////////////////
}// namespace intra
//////////////////////////////////
//eof: intra_rest_client.cpp

