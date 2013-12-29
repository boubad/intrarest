// indiv_line.h
#ifndef __INDIV_LINE_H__
#define __INDIV_LINE_H__
////////////////////////////////////////
#include <vector>
#include <cpprest/basic_types.h>
#include <boost/any.hpp>
#include <boost/algorithm/string.hpp>
/////////////////////////////////////
namespace intra {
	///////////////////////////////////////
	enum VariableType {
		unknownType,
		boolType,
		intType,
		floatType,
		doubleType,
		stringType,
		dateType,
		timeType
	};
	///////////////////////////////////////////
	template <class ALLOCANY = std::allocator<boost::any> >
	class IndivLine {
	public:
		typedef utility::string_t StringType;
		typedef std::vector<boost::any, ALLOCANY> AnyVectorType;
		typedef IndivLine<ALLOCANY> IndivLineType;
	private:
		int m_id;
		StringType m_sigle;
		AnyVectorType m_data;
	public:
		IndivLine() :m_id(0){
		}
		IndivLine(int nId, const StringType &s) :m_id(nId), m_sigle(s){}
		template <class T>
		IndivLine(int nId, const StringType &s, const std::vector<boost::any, T> &v) : m_id(nId), m_sigle(s), m_data(v.begin(), v.end()){
		}
		IndivLine(const IndivLine &other) :m_id(other.m_id), m_sigle(other.m_sigle), m_data(other.m_data){
		}
		IndivLineType & operator=(const IndivLineType &other) {
			if (this != &other){
				this->m_id = other.m_id;
				this->m_sigle = other.m_sigle;
				this->m_data = other.m_data;
			}
			return (*this);
		}
		virtual ~IndivLine(){}
	public:
		inline size_t size(void) const {
			return (this->m_data.size());
		}
		inline int id(void) const {
			return (this->m_id);
		}
		inline void id(int n) {
			this->m_id = n;
		}
		inline const StringType & sigle(void) const {
			return (this->m_sigle);
		}
		inline void sigle(const StringType &s) {
			this->m_sigle = s;
		}
		inline const AnyVectorType & data(void) const {
			return (this->m_data);
		}
		inline AnyVectorType & data(void) {
			return (this->m_data);
		}
		bool value(const size_t index, boost::any &v) const{
			bool bRet = false;
			v = boost::any();
			const AnyVectorType &vv = this->m_data;
			if (index < vv.size()) {
				v = vv[index];
				bRet = true;
			}
			return (bRet);
		}
		bool is_empty(const size_t index) const{
			bool bRet = true;
			const AnyVectorType &vv = this->m_data;
			if (index < vv.size()) {
				const boost::any & v = vv[index];
				bRet = !v.empty();
			}
			return (bRet);
		}
		bool double_value(const size_t index, double &d) const{
			bool bRet = false;
			const AnyVectorType &vv = this->m_data;
			if (index < vv.size()) {
				const boost::any & v = vv[index];
				if (!v.empty()) {
					d = IndivLineType::to_double(v);
					bRet = true;
				}
			}
			return (bRet);
		}
		bool int_value(const size_t index, int &d) const{
			bool bRet = false;
			const AnyVectorType &vv = this->m_data;
			if (index < vv.size()) {
				const boost::any & v = vv[index];
				if (!v.empty()) {
					d = IndivLineType::to_int(v);
					bRet = true;
				}
			}
			return (bRet);
		}
		bool string_value(const size_t index, StringType &d) const{
			bool bRet = false;
			const AnyVectorType &vv = this->m_data;
			if (index < vv.size()) {
				const boost::any & v = vv[index];
				if (!v.empty()) {
					IndivLine::to_string(v, d);
					bRet = true;
				}
			}
			return (bRet);
		}
		bool bool_value(const size_t index, StringType &d) const{
			bool bRet = false;
			const AnyVectorType &vv = this->m_data;
			if (index < vv.size()) {
				const boost::any & v = vv[index];
				if (!v.empty()) {
					d = IndivLineType::to_bool(v);
					bRet = true;
				}
			}
			return (bRet);
		}
		utility::ostream_t & writeTo(utility::ostream_t &out) const {
			out << this->m_id << U(",") << this->m_sigle;
			for (auto it = this->m_data.begin(); it != this->m_data.end(); ++it) {
				StringType s;
				const boost::any & v = *it;
				IndivLineType::to_string(v, s);
				out << U(',') << s;
			} // it
			out << std::endl;
			return out;
		}
	public:
		static bool to_bool(const boost::any &v){
			bool oRet = false;
			if (v.empty()) {
				return (oRet);
			}
			if (v.type() == typeid(int)) {
				int val = boost::any_cast<int>(v);
				oRet = (val != 0);
			}
			else if (v.type() == typeid(float)) {
				float val = boost::any_cast<float>(v);
				oRet = (val != 0.0f);
			}
			else if (v.type() == typeid(double)) {
				double val = boost::any_cast<double>(v);
				oRet = (val != 0.0);
			}
			else if (v.type() == typeid(StringType)) {
				StringType s = boost::any_cast<StringType>(v);
				StringType sx = boost::to_lower_copy(boost::trim_copy(s));
				if (!sx.empty()) {
					utility::char_t c = *(sx.begin());
					if ((c == U('t')) || (c == U('v')) || (c == U('o'))
						|| (c == U('1'))) {
						oRet = true;
					}
				}
			}
			else if (v.type() == typeid(bool)) {
				oRet = boost::any_cast<bool>(v);
			}
			else {
				try {
					StringType s = boost::any_cast<StringType>(v);
					StringType sx = boost::to_lower_copy(boost::trim_copy(s));
					if (!sx.empty()) {
						utility::char_t c = *(sx.begin());
						if ((c == U('t')) || (c == U('v')) || (c == U('o'))
							|| (c == U('1'))) {
							oRet = true;
						}
					}
				}
				catch (const boost::bad_any_cast &) {
				}
			}
			return (oRet);
		}
		static double to_double(const boost::any &v){
			double oRet = 0.0;
			if (v.empty()) {
				return (oRet);
			}
			if (v.type() == typeid(int)) {
				oRet = (double) boost::any_cast<int>(v);
			}
			else if (v.type() == typeid(float)) {
				float val = boost::any_cast<float>(v);
				oRet = (double) val;
			}
			else if (v.type() == typeid(double)) {
				oRet = boost::any_cast<double>(v);
			}
			else if (v.type() == typeid(StringType)) {
				StringType s = boost::any_cast<StringType>(v);
				utility::stringstream_t in(s);
				in >> oRet;
			}
			else if (v.type() == typeid(bool)) {
				bool val = boost::any_cast<bool>(v);
				oRet = (val) ? 1.0 : 0.0;
			}
			else {
				try {
					StringType s = boost::any_cast<StringType>(v);
					utility::stringstream_t in(s);
					in >> oRet;
				}
				catch (const boost::bad_any_cast &) {
				}
			}
			return (oRet);
		}
		static int to_int(const boost::any &v){
			int oRet = 0;
			if (v.empty()) {
				return (oRet);
			}
			if (v.type() == typeid(int)) {
				oRet = boost::any_cast<int>(v);
			}
			else if (v.type() == typeid(float)) {
				float val = boost::any_cast<float>(v);
				oRet = (int) val;
			}
			else if (v.type() == typeid(double)) {
				double val = boost::any_cast<double>(v);
				oRet = (int) val;
			}
			else if (v.type() == typeid(StringType)) {
				StringType s = boost::any_cast<StringType>(v);
				utility::stringstream_t in(s);
				in >> oRet;
			}
			else if (v.type() == typeid(bool)) {
				bool val = boost::any_cast<bool>(v);
				oRet = (val) ? 1 : 0;
			}
			else {
				try {
					StringType s = boost::any_cast<StringType>(v);
					utility::stringstream_t in(s);
					in >> oRet;
				}
				catch (const boost::bad_any_cast &) {
				}
			}
			return (oRet);
		}
		static void to_string(const boost::any &v, StringType &s){
			if (v.empty()) {
				s.clear();
				return;
			}
			if (v.type() == typeid(int)) {
				int val = boost::any_cast<int>(v);
				utility::stringstream_t out;
				out << val;
				s = out.str();
			}
			else if (v.type() == typeid(float)) {
				float val = boost::any_cast<float>(v);
				utility::stringstream_t out;
				out << val;
				s = out.str();
			}
			else if (v.type() == typeid(double)) {
				double val = boost::any_cast<double>(v);
				utility::stringstream_t out;
				out << val;
				s = out.str();
			}
			else if (v.type() == typeid(StringType)) {
				s = boost::any_cast<StringType>(v);
			}
			else if (v.type() == typeid(bool)) {
				bool val = boost::any_cast<bool>(v);
				s = (val) ? U("True") : U("False");
			}
			else {
				try {
					s = boost::any_cast<StringType>(v);
				}
				catch (const boost::bad_any_cast &) {
					s.clear();
				}
			}
		}

	}; // class IndivLine<ALLOCANY>
	/////////////////////////////////////////
}// namespace intra
////////////////////////////////////////////
template <class ALLOCANY>
utility::ostream_t & operator<<(utility::ostream_t &out, const intra::IndivLine<ALLOCANY> &d){
	return d.writeTo(out);
}
/////////////////////////////////////////
#endif // __INDIV_LINE_H__
///////////////////////////////
// eof: indiv_line.h
