//dataset.h
/////////////////////////
#ifndef __DATASET_H__
#define __DATASET_H__
///////////////////////////////////////
#include "sigle_named_element.h"
//////////////////////////////////////
namespace intra {
	/////////////////////////////////////
	class Dataset : public SigleNamedItem {
	public:
		Dataset();
		Dataset(int nId, int nVersion, bool bSelected, const String &sSigle,
			const String &sName, const String &sRem);
		Dataset(const String &sSigle);
		Dataset(const Dataset &other);
		Dataset & operator=(const Dataset &other);
		virtual ~Dataset();

		inline bool operator==(const Dataset &other) const {
			return (SigleNamedItem::operator==(other));
		}

		inline bool operator<(const Dataset &other) const {
			return (SigleNamedItem::operator<(other));
		}
	};
	// class Dataset
	//////////////////////////////////////////
	typedef std::shared_ptr<Dataset> DatasetPtr;
	//////////////////////////////////////////////////
	template <class ALLOCVEC = std::allocator<DatasetPtr> >
	class Datasets : public IntraBase {
	public:
		typedef std::vector<DatasetPtr, ALLOCVEC> DatasetPtrVector;
		typedef Datasets<ALLOCVEC> DatasetsType;
	protected:
		DatasetPtrVector m_vars;
	public:
		Datasets(){
		}
		template <class T>
		Datasets(const std::vector<DatasetPtr, T> &vv) :m_vars(vv.begin(), vv.end()){
		}
		Datasets(const DatasetsType &other) :IntraBase(other), m_vars(other.m_vars){

		}
		DatasetsType & operator=(const DatasetsType &other){
			if (this != &other){
				IntraBase::operator=(other);
				this->m_vars = other.m_vars;
			}
			return (*this);
		}
		virtual ~Datasets(){
		}
	public:
		inline const DatasetPtrVector & datasets(void) const {
			return (this->m_vars);
		}
		inline DatasetPtrVector & datasets(void) {
			return (this->m_vars);
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value){
			switch (t) {
			case FieldValue::datasets: {
										   DatasetPtrVector &ovec = this->m_vars;
										   ovec.clear();
										   if ((!value.is_null()) && value.is_array()) {
											   const size_t n = value.size();
											   for (size_t i = 0; i < n; ++i) {
												   const web::json::value &v = value.get(i);
												   Dataset x;
												   x.fill_from_json(v);
												   DatasetPtr oPtr = std::make_shared < Dataset >(x);
												   ovec.push_back(oPtr);
											   }    // i
										   }    // value
			}
				return (true);
			default:
				break;
			}    // t
			return (false);
		}
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const{
			IntraBase::write_json(value, gen);
			String key;
			if (gen.get_key(FieldValue::datasets, key)) {
				const DatasetPtrVector &ovec = this->m_vars;
				size_t n = ovec.size();
				web::json::value oAr = web::json::value::array(n);
				for (size_t i = 0; i < n; ++i) {
					DatasetPtr oPtr = ovec[i];
					Dataset *p = oPtr.get();
					web::json::value v;
					p->write_json(v, gen);
					oAr[i] = v;
				}    // i
				value[key] = oAr;
			}
		}
	};// class Datasets
	////////////////////////////////////////////////////
}// namespace intra
////////////////////////////////////////////
#endif // __DATASET_H__
////////////////////////////
// eof: dataset.h
