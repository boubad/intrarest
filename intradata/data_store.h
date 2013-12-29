//data_store.h
#ifndef __DATA_STORE_H__
#define __DATA_STORE_H__
//////////////////////////////////
#include "intra_rest_client.h"
/////////////////////////////////////
namespace intra {
	////////////////////////////////////////////
	template <class ALLOCVARVEC = std::allocator<VariablePtr> >
	class DataStore {
	public:
		typedef std::vector<VariablePtr, ALLOCVARVEC> VariablePtrVectorType;
		typedef DataStore<ALLOCVARVEC> DataStoreType;
	private:
		String m_baseUri;
		std::shared_ptr<IntraRESTClient> m_client;
		DatasetPtr m_set;
		VariablePtrVectorType m_vars;
	public:
		DataStore() :m_baseUri(IntraRESTClient::DEFAULT_BASE_URI){

		}
		DataStore(const String &baseUri) :m_baseUri(baseUri){

		}
		DataStore(const DataStoreType &other) :
			m_baseUri(other.m_baseUri), m_client(other.m_client), m_set(
			other.m_set), m_vars(other.m_vars) {
		}
		DataStoreType & operator=(const DataStoreType &other){
			if (this != &other) {
				this->m_baseUri = other.m_baseUri;
				this->m_client = other.m_client;
				this->m_set = other.m_set;
				this->m_vars = other.m_vars;
			}
			return (*this);
		}
		virtual ~DataStore(){

		}
	protected:
		IntraRESTClient *get_client(void) {
			const IntraRESTClient *pRet = this->m_client.get();
			if (pRet == nullptr) {
				DataStoreType *pStore = const_cast<DataStoreType *>(this);
				pStore->m_client = std::make_shared < IntraRESTClient>(pStore->m_baseUri);
			}
			return (this->m_client.get());
		}// get_client
	public:
		static bool convert_value(const String &sInit, const size_t iVarIndex,
			const VariablePtrVectorType &oVars, boost::any &oRet){
			if (sInit.empty()) {
				oRet = boost::any();
				return (true);
			}
			if (iVarIndex >= oVars.size()) {
				return (false);
			}
			VariablePtr oPtr = oVars[iVarIndex];
			const Variable *pVar = oPtr.get();
			if (pVar == nullptr) {
				return (false);
			}
			String stype = boost::to_lower_copy(boost::trim_copy(pVar->sigle()));
			if (stype == U("string")) {
				oRet = boost::any(sInit);
			}
			else if (stype == U("float")) {
				utility::stringstream_t in(sInit);
				float x = 0.0f;
				in >> x;
				oRet = boost::any(x);
			}
			else if (stype == U("int")) {
				utility::stringstream_t in(sInit);
				int x = 0;
				in >> x;
				oRet = boost::any(x);
			}
			else if (stype == U("double")) {
				utility::stringstream_t in(sInit);
				double x = 0.0;
				in >> x;
				oRet = boost::any(x);
			}
			else if (stype == U("bool")) {
				bool x = false;
				String sx = boost::to_lower_copy(boost::trim_copy(sInit));
				if (sx.empty()) {
					oRet = boost::any();
					return (true);
				}
				else {
					utility::char_t c = *(sx.begin());
					if ((c == U('t')) || (c == U('v')) || (c == U('o'))
						|| (c == U('1'))) {
						x = true;
					}
					oRet = boost::any(x);
				}
				oRet = boost::any(x);
			}
			else {
				oRet = boost::any(sInit);
			}
			return (true);
		}// convert_value
	public:
		void set_dataset(DatasetPtr oSet){
			this->m_set = oSet;
			this->get_datalines_variables_async(this->m_vars).get();
		}// set_dataset
		size_t variables_count(void) const{
			if (this->m_vars.empty()) {
				DataStoreType *pStore = const_cast<DataStoreType *>(this);
				pStore->get_datalines_variables_async(pStore->m_vars).get();
				return (pStore->m_vars.size());
			} //
			return (this->m_vars.size());
		}// variables_count
		VariableType variable_type(const size_t ivarIndex) const {
			VariableType oRet = VariableType::unknownType;
			String stype;
			if (this->m_vars.empty()) {
				DataStoreType *pStore = const_cast<DataStoreType *>(this);
				pStore->get_datalines_variables_async(pStore->m_vars).get();
				if (ivarIndex < pStore->m_vars.size()) {
					VariablePtr o = pStore->m_vars[ivarIndex];
					Variable *p = o.get();
					if (p != nullptr) {
						stype = p->var_type();
					}
				}
			}
			else {
				if (ivarIndex < this->m_vars.size()) {
					VariablePtr o = this->m_vars[ivarIndex];
					Variable *p = o.get();
					if (p != nullptr) {
						stype = p->var_type();
					}
				}
			}
			stype = boost::to_lower_copy(boost::trim_copy(stype));
			if (stype == U("bool")) {
				oRet = VariableType::boolType;
			}
			else if (stype == U("int")) {
				oRet = VariableType::intType;
			}
			else if (stype == U("float")) {
				oRet = VariableType::floatType;
			}
			else if (stype == U("double")) {
				oRet = VariableType::doubleType;
			}
			else if (stype == U("string")) {
				oRet = VariableType::stringType;
			}
			else if (stype == U("date")) {
				oRet = VariableType::dateType;
			}
			else if (stype == U("time")) {
				oRet = VariableType::timeType;
			}
			return (oRet);
		}// variable_type
		bool is_categ_variable(const size_t ivarIndex) const{
			bool bRet = false;
			if (this->m_vars.empty()) {
				DataStoreType *pStore = const_cast<DataStoreType *>(this);
				pStore->get_datalines_variables_async(pStore->m_vars).get();
				if (ivarIndex < pStore->m_vars.size()) {
					VariablePtr o = pStore->m_vars[ivarIndex];
					Variable *p = o.get();
					if (p != nullptr) {
						bRet = p->is_categ();
					}
				}
			}
			else {
				if (ivarIndex < this->m_vars.size()) {
					VariablePtr o = this->m_vars[ivarIndex];
					Variable *p = o.get();
					if (p != nullptr) {
						bRet = p->is_categ();
					}
				}
			}
			return (bRet);
		}// is_categ_variable
		const Variable *variable(const size_t ivarIndex) const{
			if (this->m_vars.empty()) {
				DataStoreType *pStore = const_cast<DataStoreType *>(this);
				pStore->get_datalines_variables_async(pStore->m_vars).get();
				if (ivarIndex < pStore->m_vars.size()) {
					const VariablePtr & o = pStore->m_vars[ivarIndex];
					return (o.get());
				}
			}
			else {
				if (ivarIndex < this->m_vars.size()) {
					const VariablePtr & o = this->m_vars[ivarIndex];
					return (o.get());

				}
			}
			return (nullptr);
		}// variable
		//
		pplx::task<bool> is_connected_async(void) {
			return this->get_client()->is_connected_async();
		}
		template <class T>
		pplx::task<bool> get_all_datasets_async(std::vector<DatasetPtr, T> &oRet) {
			const IntraRESTClient *pClient = this->get_client();
			return pClient->get_all_datasets_count_async().then([&oRet, pClient](pplx::task<int> pTask){
				int nc = pTask.get();
				return pClient->get_datasets_async(0, nc, oRet);
			});
		}// get_all_datasets_async
		template <class T>
		pplx::task<bool> get_datalines_header_async(std::vector<String, T> &oRet)  {
			oRet.clear();
			const Dataset *pSet = this->m_set.get();
			if (pSet == nullptr){
				return (pplx::task_from_result(false));
			}
			return this->get_client()->get_datalines_header_async(pSet->id(), oRet);
		}// get_datalines_header_async
		template <class T>
		pplx::task<bool> get_datalines_variables_async(std::vector<VariablePtr, T> &oRet)  {
			oRet.clear();
			const Dataset *pSet = this->m_set.get();
			if (pSet == nullptr){
				return (pplx::task_from_result(false));
			}
			return this->get_client()->get_datalines_variables_async(pSet->id(), oRet);
		}// get_datalines_variables_async
		pplx::task<int> get_datalines_count_async(void)  {
			const Dataset *pSet = this->m_set.get();
			if (pSet == nullptr){
				return (pplx::task_from_result(0));
			}
			return this->get_client()->get_datalines_count_async(pSet->id());
		}// get_datalines_count_async
		template <class T, class V>
		pplx::task<bool> get_datalines_values_async(const int skip, const int taken,
			std::vector<std::shared_ptr<DataLine<T>>, V> &oRet) {
			oRet.clear();
			const Dataset *pSet = this->m_set.get();
			if (pSet == nullptr){
				return (pplx::task_from_result(false));
			}
			return this->get_client()->get_datalines_values_async(pSet->id(), skip, taken, oRet);
		}// get_datalines_values_async
		template <class T, class V>
		pplx::task<bool> get_datalines_async(const int skip, const int taken,
			std::vector<std::shared_ptr<IndivLine<T>>, V> &oRet) {
			oRet.clear();
			const Dataset *pSet = this->m_set.get();
			if (pSet == nullptr){
				return (pplx::task_from_result(false));
			}
			return pplx::create_task([&oRet, this,pSet,skip,taken]{
				DataStoreType *pStore = const_cast<DataStoreType *>(this);
				VariablePtrVectorType *pVars = &(pStore->m_vars);
				if (pVars->empty()) {
					pStore->get_datalines_variables_async(pStore->m_vars).get();
				}
				typedef IndivLine<T> IndivLineType;
				typedef std::shared_ptr<IndivLineType> IndivLinePtrType;
				IntraRESTClient *pClient = this->get_client();
				typedef DataLine<> DataLineType;
				typedef std::shared_ptr<DataLineType> DataLinePtrType;
				std::vector<DataLinePtrType> oVec;
				pClient->get_datalines_values_async(pSet->id(), skip, taken, oVec).get();
				const size_t n = oVec.size();
				for (size_t i = 0; i < n; ++i) {
					DataLinePtrType oPtr = oVec[i];
					DataLineType *pLine = oPtr.get();
					if (pLine != nullptr) {
						auto xxdata = pLine->values();
						const size_t nx = xxdata.size();
						if (nx > 1) {
							IndivLinePtrType o = std::make_shared<IndivLineType>();
							IndivLineType *pp = o.get();
							if (pp != nullptr) {
								typename IndivLine<T>::AnyVectorType &vv = pp->data();
								for (size_t j = 0; j < nx; ++j) {
									String sval = xxdata[j];
									boost::any vz;
									switch (j) {
									case 0:
									{
											  utility::stringstream_t in(sval);
											  int nId = 0;
											  in >> nId;
											  pp->id(nId);
									}
										break;
									case 1:
										pp->sigle(sval);
										break;
									default:
									{
											   size_t jj = (size_t) (j - 1);
											   DataStoreType::convert_value(sval, jj, *pVars, vz);
									}
										break;
									} // j
									vv.push_back(vz);
								} // j
								oRet.push_back(o);
							} // pp
						} // nx
					} // pLine
				} // i
				return (true);
			});
		}// get_datalines_async
		//
	};// class DataSore
	//////////////////////////////////////////////////
}// namespace intra
//////////////////////////////////////
#endif // __DATA_STORE_H__
///////////////////////////
//eof: data_store.h
