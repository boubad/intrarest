//intra_rest_client.h
#ifndef __INTRA_REST_CLIENT_H__
#define __INTRA_REST_CLIENT_H__
////////////////////////////////////
#include "dataset.h"
#include "indiv.h"
#include "variable.h"
#include "intra_value.h"
#include "data_line.h"
#include "indiv_line.h"
//////////////////////////////////////
namespace intra {
	/////////////////////////////////////////////
	class IntraRESTClient {
	public:
		static const Char *DEFAULT_BASE_URI;
	private:
		String m_baseUri;
		ItemGenerator m_gen;
	protected:
		inline const ItemGenerator &generator(void) const {
			return (this->m_gen);
		}
		pplx::task<String> intern_get_text_task(const String &uri) const;
		pplx::task<String> intern_get_text_task(const String &uri,const int arg1) const;
		pplx::task<web::json::value> intern_get_json_task(const String &uri) const;
		pplx::task<web::json::value> intern_get_json_task(const String &uri, const int arg1) const;
		pplx::task<web::json::value> intern_get_json_task(const String &uri, const int arg1,const int arg2) const;
		pplx::task<web::json::value> intern_get_json_task(const String &uri, const int arg1, const int arg2,const int arg3) const;
	public:
		IntraRESTClient(const String &baseUri = DEFAULT_BASE_URI);
		IntraRESTClient(const IntraRESTClient & orig);
		virtual ~IntraRESTClient();
	public:
		inline const String & baseUri(void) const {
			return (this->m_baseUri);
		}
		inline void baseUri(const String &s){
			this->m_baseUri = s;
		}
	public:
		pplx::task<bool> is_connected_async(void) const;
		pplx::task<int> get_all_datasets_count_async(void) const;
		template <class T>
		pplx::task<bool> get_datasets_async(const int skip, const int taken, std::vector<DatasetPtr, T> &oRet) const {
			typedef std::vector<DatasetPtr, T> DatasetPtrVector;
			oRet.clear();
			if ((skip < 0) || (taken < 1)) {
				return (pplx::task_from_result(false));
			}
			return this->intern_get_json_task(U("dataset"), skip, taken).then([&oRet,this](pplx::task<web::json::value> pTask){
				bool bRet = false;
				try {
					const web::json::value &jsonvalue = pTask.get();
					if (!jsonvalue.is_null()) {
						Datasets<T> xx;
						const ItemGenerator &gen = this->generator();
						xx.fill_from_json(jsonvalue, gen);
						oRet = xx.datasets();
						bRet = true;
					}    //
				}
				catch (const web::http::http_exception & /*e */) {

				}
				return (pplx::task_from_result(bRet));
			});
		}// get_datasets_async
		template <class T>
		pplx::task<bool> get_datalines_variables_async(const int datasetid, std::vector<VariablePtr, T> &oRet) const {
			return this->intern_get_json_task(U("reader/variables"), datasetid).then([&oRet, this](pplx::task<web::json::value> pTask){
				bool bRet = false;
				try {
					const web::json::value &jsonvalue = pTask.get();
					if (!jsonvalue.is_null()) {
						Variables<T> xx;
						const ItemGenerator &gen = this->generator();
						xx.fill_from_json(jsonvalue, gen);
						oRet = xx.variables();
						bRet = true;
					}    //
				}
				catch (const web::http::http_exception & /*e */) {
				}
				return (pplx::task_from_result(bRet));
			});
		}// get_datalines_variables_async
		template <class T>
		pplx::task<bool> get_datalines_header_async(const int datasetid, std::vector<String, T> &oRet) const {
			return this->intern_get_json_task(U("reader/header"), datasetid).then([&oRet, this](pplx::task<web::json::value> pTask){
				bool bRet = false;
				try {
					const web::json::value &jsonvalue = pTask.get();
					if (!jsonvalue.is_null()) {
						DataLine<T> xx;
						const ItemGenerator &gen = this->generator();
						xx.fill_from_json(jsonvalue, gen);
						oRet = xx.values();
						bRet = true;
					}    //
				}
				catch (const web::http::http_exception & /*e */) {
				}
				return (pplx::task_from_result(bRet));
			});
		}//get_datalines_header_async
		pplx::task<int> get_datalines_count_async(const int datasetid) const;
		template <class T, class V>
		pplx::task<bool> get_datalines_values_async(const int datasetid,  const int skip, const int taken,
			std::vector<std::shared_ptr<DataLine<T>>, V> &oRet) {
			oRet.clear();
			if ((skip < 0) || (taken < 1)) {
				return (pplx::task_from_result(false));
			}
			typedef DataLine<T> DataLineType;
			typedef std::shared_ptr<DataLineType> DataLineTypePtr;
			const ItemGenerator &gen = this->generator();
			return this->intern_get_json_task(U("reader/values"), datasetid,skip,taken).then([gen](pplx::task<web::json::value> pTask){
				std::vector<std::shared_ptr<DataLine<T>>, V> vv;
				try {
					const web::json::value &jsonvalue = pTask.get();
					if (!jsonvalue.is_null()) {
						DataLines<T> xx;
						xx.fill_from_json(jsonvalue, gen);
						const typename DataLines<T>::DataLinePtrVector & temp = xx.values();
						for (auto it = temp.begin(); it != temp.end(); ++it){
							DataLineTypePtr o = *it;
							if (o.get() != nullptr){
								vv.push_back(o);
							}
						}// it
					}    //
				}
				catch (const web::http::http_exception & /*e */) {
				}
				return pplx::create_task([vv]{
					return vv;
				});
			}).then([&oRet](pplx::task<std::vector<std::shared_ptr<DataLine<T>>, V>> ppTask){
				oRet = ppTask.get();
				return (pplx::task_from_result(!oRet.empty()));
			});
		}//get_datalines_values 
		//

	}; // class IntraRESTClient
	/////////////////////////////////////////////////
}// namespace intra
/////////////////////////////////////
#endif // __INTRA_REST_CLIENT_H__
////////////////////////////////
//eof: intra_rest_client.h
