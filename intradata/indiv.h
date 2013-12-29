//indiv.h
////////////////////////////////////
#ifndef __INDIV_H__
#define __INDIV_H__
//////////////////////////////////////////
#include "dataset_child.h"
//////////////////////////////////////////////
namespace intra {
	///////////////////////////////////////
	class Indiv : public DatasetChild {
	protected:
		bool m_hasimage;
		size_t m_size;
		std::unique_ptr<byte> m_data;
	public:

		Indiv();
		Indiv(int nId, int nVersion, bool bSelected, int nDatasetId,
			const String &sSigle, const String &sName, const String &sRem,
			const String &sStatus);
		Indiv(int nDatasetId, const String &sSigle);
		Indiv(const Indiv &other);
		Indiv & operator=(const Indiv &other);
		virtual ~Indiv();

		inline bool operator==(const Indiv &other) const {
			return (DatasetChild::operator==(other));
		}

		inline bool operator<(const Indiv &other) const {
			return (DatasetChild::operator<(other));
		}
	public:

		inline bool has_image(void) const {
			return (this->m_hasimage);
		}

		inline void has_image(bool b) {
			this->m_hasimage = b;
		}

		inline const byte *data(size_t &nSize) const {
			nSize = this->m_size;
			return (this->m_data.get());
		}

		void data(const byte *pSrc, const size_t n);
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value);
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const;
	};
	// class Indiv
	////////////////////////////////////////////
	typedef std::shared_ptr<Indiv> IndivPtr;
	/////////////////////////////////////////////
	template <class ALLOCVEC = std::allocator<IndivPtr> >
	class Indivs : public IntraBase {
	public:
		typedef std::vector<IndivPtr, ALLOCVEC> IndivPtrVector;
		typedef Indivs<ALLOCVEC> IndivsType;
	protected:
		IndivPtrVector m_vars;
	public:
		Indivs(){}
		template <class T>
		Indivs(const std::vector<IndivPtr, T> &vv) :m_vars(vv.begin(), vv.end()) {

		}
		Indivs(const IndivsType &other) :IntraBase(other), m_vars(other.m_vars){

		}
		IndivsType & operator=(const IndivsType &other){
			if (this != &other){
				IntraBase::operator=(other);
				this->m_vars = other.m_vars;
			}
			return (*this);
		}
		virtual ~Indivs(){
		}
	public:

		inline const IndivPtrVector & indivs(void) const {
			return (this->m_vars);
		}

		inline IndivPtrVector & indiv(void) {
			return (this->m_vars);
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value){
			switch (t) {
			case FieldValue::indivs: {
										 IndivPtrVector &ovec = this->m_vars;
										 ovec.clear();
										 if ((!value.is_null()) && value.is_array()) {
											 const size_t n = value.size();
											 for (size_t i = 0; i < n; ++i) {
												 const web::json::value &v = value.get(i);
												 Indiv x;
												 x.fill_from_json(v);
												 IndivPtr oPtr = std::make_shared < Indiv >(x);
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
			if (gen.get_key(FieldValue::indivs, key)) {
				const IndivPtrVector &ovec = this->m_vars;
				size_t n = ovec.size();
				web::json::value oAr = web::json::value::array(n);
				for (size_t i = 0; i < n; ++i) {
					IndivPtr oPtr = ovec[i];
					Indiv *p = oPtr.get();
					web::json::value v;
					p->write_json(v, gen);
					oAr[i] = v;
				}    // i
				value[key] = oAr;
			}
		}
	};
	// class Indivs
	/////////////////////////////////////////
}// namespace intra
/////////////////////////////////////////////
#endif // __INDIV_H__
//////////////////////////////
// eof: indiv.h
