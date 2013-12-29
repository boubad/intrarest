//data_line.h
#ifndef __DATA_LINE_H__
#define __DATA_LINE_H__
///////////////////////////////////////////
#include "intra_base.h"
/////////////////////////////////////////////////
namespace intra {
	////////////////////////////////////////
	template <class ALLOCSTRING = std::allocator<String> >
	class DataLine : public IntraBase {
	public:
		typedef std::vector<String, ALLOCSTRING> StringVector;
		typedef DataLine<ALLOCSTRING> DataLineType;
		typedef std::shared_ptr<DataLineType> DataLinePtr;
	protected:
		StringVector m_vars;
	public:
		DataLine(){}
		template <class T>
		DataLine(const std::vector<String, T> &vv) :m_vars(vv.begin(), vv.end()){
		}
		DataLine(const DataLineType &other) : IntraBase(other), m_vars(other.m_vars){
		}
		DataLineType & operator=(const DataLineType &other){
			if (this != &other){
				IntraBase::operator=(other);
				this->m_vars = other.m_vars;
			}
			return (*this);
		}
		virtual ~DataLine(){}
	public:

		inline const StringVector & values(void) const {
			return (this->m_vars);
		}

		inline StringVector & values(void) {
			return (this->m_vars);
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value) {
			switch (t) {
			case FieldValue::values: {
										 StringVector &ovec = this->m_vars;
										 ovec.clear();
										 if ((!value.is_null()) && value.is_array()) {
											 const size_t n = value.size();
											 for (size_t i = 0; i < n; ++i) {
												 const web::json::value &v = value.get(i);
												 String x;
												 if ((!v.is_null()) && v.is_string()) {
													 x = v.as_string();
												 }
												 ovec.push_back(x);
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
			const ItemGenerator &gen) const {
			IntraBase::write_json(value, gen);
			String key;
			if (gen.get_key(FieldValue::values, key)) {
				const StringVector &ovec = this->m_vars;
				size_t n = ovec.size();
				web::json::value oAr = web::json::value::array(n);
				for (size_t i = 0; i < n; ++i) {
					String s = ovec[i];
					web::json::value v;
					if (!s.empty()) {
						v = web::json::value::string(s);
					}
					oAr[i] = v;
				}    // i
				value[key] = oAr;
			}
		}
	}; // class DataLine<ALLOCSTRING>
	///////////////////////////////////////////////
	template < class ALLOCSTRING = std::allocator<String>,
	class ALLOCVEC = std::allocator<std::shared_ptr<DataLine<ALLOCSTRING> > > >
	class DataLines : public IntraBase {
	public:
		typedef std::vector<String, ALLOCSTRING> StringVector;
		typedef intra::DataLine<ALLOCSTRING> DataLineType;
		typedef std::shared_ptr<DataLineType> DataLinePtr;
		typedef std::vector<DataLinePtr, ALLOCVEC> DataLinePtrVector;
		typedef DataLines<ALLOCSTRING, ALLOCVEC> DataLinesType;
	protected:
		DataLinePtrVector m_vars;
	public:
		DataLines(){}
		template <class T>
		DataLines(const std::vector<DataLinePtr, T> &vv) :m_vars(vv.begin(), vv.end()){
		}
		DataLines(const DataLinesType &other) : IntraBase(other), m_vars(other.m_vars){
		}
		DataLinesType & operator=(const DataLinesType &other){
			if (this != &other){
				IntraBase::operator=(other);
				this->m_vars = other.m_vars;
			}
			return (*this);
		}
		virtual ~DataLines(){
		}
	public:

		inline const DataLinePtrVector & values(void) const {
			return (this->m_vars);
		}

		inline DataLinePtrVector & values(void) {
			return (this->m_vars);
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value){
			switch (t) {
			case FieldValue::datalines: {
											DataLinePtrVector &ovec = this->m_vars;
											ovec.clear();
											if ((!value.is_null()) && value.is_array()) {
												const size_t n = value.size();
												for (size_t i = 0; i < n; ++i) {
													const web::json::value &v = value.get(i);
													DataLineType x;
													x.fill_from_json(v);
													DataLinePtr oPtr = std::make_shared < DataLineType >(x);
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
			if (gen.get_key(FieldValue::datalines, key)) {
				const DataLinePtrVector &ovec = this->m_vars;
				size_t n = ovec.size();
				web::json::value oAr = web::json::value::array(n);
				for (size_t i = 0; i < n; ++i) {
					const DataLinePtr & o = ovec[i];
					const DataLineType * x = o.get();
					web::json::value v;
					x->write_json(v, gen);
					oAr[i] = v;
				}    // i
				value[key] = oAr;
			}
		}

	}; // class DataLines<ALLOCSTRING,ALLOCVEC>
	///////////////////////////////////////////
}// namespace intra
///////////////////////////////////////////////
#endif // __DATA_LINE_H__
///////////////////////////////
// eof: data_line_h