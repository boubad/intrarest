// intra_value.h
#ifndef __INTRA_VALUE_H__
#define __INTRA_VALUE_H__
////////////////////////////////////////
#include "baseitem.h"
////////////////////////////////////////////
namespace intra {
	//////////////////////////////////////////
	class Value : public BaseItem {
	protected:
		int m_variableid;
		int m_individ;
		String m_val;
		String m_varsigle;
		String m_indsigle;
	public:

		Value();

		Value(int nId, int nVersion, bool bSelected, int nVarId, int nIndId,
			const String &sStatus);
		Value(int nVarId, int nIndId);
		Value(const Value &other);
		Value & operator=(const Value &other);
		virtual ~Value(); bool operator==(const Value &other) const; bool operator<(
			const Value &other) const;
	public:
		inline const String & variable_sigle(void) const {
			return (this->m_varsigle);
		}
		inline void variable_sigle(const String &s){
			this->m_varsigle = s;
		}
		inline const String & indiv_sigle(void) const {
			return (this->m_indsigle);
		}
		void indiv_sigle(const String &s){
			this->m_indsigle = s;
		}
		inline int variable_id(void) const {
			return (this->m_variableid);
		}

		inline void variable_id(int n) {
			this->m_variableid = n;
		}

		inline int indiv_id(void) const {
			return (this->m_individ);
		}

		inline void indiv_id(int n) {
			this->m_individ = n;
		}

		inline const String &value(void) const {
			return (this->m_val);
		}

		inline void value(const String &s) {
			this->m_val = s;
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value);
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const;
	};
	// class Value
	////////////////////////////////////////////////
	typedef std::shared_ptr<Value> ValuePtr;
	///////////////////////////////////////////////
	template <class ALLOCVEC = std::allocator<ValuePtr> >
	class Values : public IntraBase {
	public:
		typedef std::vector<ValuePtr, ALLOCVEC> ValuePtrVector;
		typedef Values<ALLOCVEC> ValuesType;
	protected:
		ValuePtrVector m_vars;
	public:
		Values(){}
		template <class T>
		Values(const std::vector<ValuePtr, T> &vv) :m_vars(vv.begin(), vv.end()){
		}
		Values(const ValuesType &other) :IntraBase(other), m_vars(other.m_vars){
		}
		ValuesType & operator=(const ValuesType &other){
			if (this != &other){
				IntraBase::operator=(other);
				this->m_vars = other.m_vars;
			}
			return (*this);
		}
		virtual ~Values(){}
	public:

		inline const ValuePtrVector & values(void) const {
			return (this->m_vars);
		}

		inline ValuePtrVector & values(void) {
			return (this->m_vars);
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value){
			switch (t) {
			case FieldValue::values: {
										 ValuePtrVector &ovec = this->m_vars;
										 ovec.clear();
										 if ((!value.is_null()) && value.is_array()) {
											 const size_t n = value.size();
											 for (size_t i = 0; i < n; ++i) {
												 const web::json::value &v = value.get(i);
												 Value x;
												 x.fill_from_json(v);
												 ValuePtr oPtr = std::make_shared < Value >(x);
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
				const ValuePtrVector &ovec = this->m_vars;
				size_t n = ovec.size();
				web::json::value oAr = web::json::value::array(n);
				for (size_t i = 0; i < n; ++i) {
					ValuePtr oPtr = ovec[i];
					Value *p = oPtr.get();
					web::json::value v;
					p->write_json(v, gen);
					oAr[i] = v;
				}    // i
				value[key] = oAr;
			}
		}
	};
	// class Values
	//////////////////////////////////////////////
}// namespace intra
//////////////////////////////////////////
#endif // __INTRA_VALUE_H__
////////////////////////////////
// eof: intra_value.h

