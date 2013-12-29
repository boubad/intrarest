// variable.h
///////////////////////////
#ifndef __VARIABLE_H__
#define __VARIABLE_H__
//////////////////////////////////////
#include "dataset_child.h"
////////////////////////////////////////////
namespace intra {
	//////////////////////////////////
	class Variable : public DatasetChild {
	protected:
		bool m_categ;
		int m_etape;
		String m_type;
		String m_genre;
	public:

		Variable();

		Variable(int nId, int nVersion, bool bSelected, int nDatasetId,
			const String &sSigle, const String &sName, const String &sRem,
			bool bCateg, int nEtape, const String &sType, const String &sGenre);
		Variable(int nDatasetId, const String &sSigle, int nEtape, bool bCateg,
			const String &sType, const String &sGenre);
		Variable(const Variable &other);
		Variable & operator=(const Variable &other);
		virtual ~Variable();

		inline bool operator==(const Variable &other) const {
			return (DatasetChild::operator==(other));
		}

		inline bool operator<(const Variable &other) const {
			return (DatasetChild::operator<(other));
		}
	public:

		inline bool is_categ(void) const {
			return (this->m_categ);
		}

		inline void is_categ(bool b) {
			this->m_categ = b;
		}

		inline int etape(void) const {
			return (this->m_etape);
		}

		inline void etape(int n) {
			this->m_etape = n;
		}

		inline const String &var_type(void) const {
			return (this->m_type);
		}

		inline void var_type(const String &s) {
			this->m_type = s;
		}

		inline const String & genre(void) const {
			return (this->m_genre);
		}

		inline void genre(const String &s) {
			this->m_genre = s;
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value);
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const;
	};
	// class Variable
	////////////////////////////////////////
	typedef std::shared_ptr<Variable> VariablePtr;
	////////////////////////////////////////
	template <class ALLOCVEC = std::allocator<VariablePtr> >
	class Variables : public IntraBase {
	public:
		typedef std::vector<VariablePtr, ALLOCVEC> VariablePtrVector;
		typedef Variables<ALLOCVEC> VariablesType;
	protected:
		VariablePtrVector m_vars;
	public:
		Variables(){}
		template <class T>
		Variables(const  std::vector<VariablePtr, T> &vv) :m_vars(vv.begin(), vv.end()){
}
		Variables(const VariablesType &other) :IntraBase(other), m_vars(other.m_vars){
		}
		VariablesType & operator=(const VariablesType &other){
			if (this != &other){
				IntraBase::operator=(other);
				this->m_vars = other.m_vars;
			}
			return (*this);
		}
		virtual ~Variables(){
		}
	public:

		inline const VariablePtrVector & variables(void) const {
			return (this->m_vars);
		}

		inline VariablePtrVector & variables(void) {
			return (this->m_vars);
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value){
			switch (t) {
			case FieldValue::variables: {
											VariablePtrVector &ovec = this->m_vars;
											ovec.clear();
											if ((!value.is_null()) && value.is_array()) {
												const size_t n = value.size();
												for (size_t i = 0; i < n; ++i) {
													const web::json::value &v = value.get(i);
													Variable x;
													x.fill_from_json(v);
													VariablePtr oPtr = std::make_shared < Variable >(x);
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
			if (gen.get_key(FieldValue::variables, key)) {
				const VariablePtrVector &ovec = this->m_vars;
				size_t n = ovec.size();
				web::json::value oAr = web::json::value::array(n);
				for (size_t i = 0; i < n; ++i) {
					VariablePtr oPtr = ovec[i];
					Variable *p = oPtr.get();
					web::json::value v;
					p->write_json(v, gen);
					oAr[i] = v;
				}    // i
				value[key] = oAr;
			}
		}
	};
	// class Variables
	///////////////////////////////////////
}// namespace intra
//////////////////////////////////////////
#endif // __VARIABLE_H__
/////////////////////////////////
// eof: variable.h
