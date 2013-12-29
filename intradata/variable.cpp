// variable.cpp
/////////////////////////////
#include "variable.h"
//////////////////////////////////
namespace intra {
////////////////////////////////
	Variable::Variable() :
		m_categ(false), m_etape(0) {
	}

	Variable::Variable(int nId, int nVersion, bool bSelected, int nDatasetId,
		const String &sSigle, const String &sName, const String &sRem,
		bool bCateg, int nEtape, const String &sType, const String &sGenre) :
		DatasetChild(nId, nVersion, bSelected, nDatasetId, sSigle, sName, sRem), m_categ(
		bCateg), m_etape(nEtape), m_type(sType), m_genre(sGenre) {

	}

	Variable::Variable(int nDatasetId, const String &sSigle, int nEtape,
		bool bCateg, const String &sType, const String &sGenre) :
		DatasetChild(nDatasetId, sSigle), m_categ(bCateg), m_etape(nEtape), m_type(
		sType), m_genre(sGenre) {
	}

	Variable::Variable(const Variable &other) :
		DatasetChild(other), m_categ(other.m_categ), m_etape(other.m_etape), m_type(
		other.m_type), m_genre(other.m_genre) {
	}

	Variable & Variable::operator=(const Variable &other) {
		if (this != &other) {
			DatasetChild::operator=(other);
			this->m_categ = other.m_categ;
			this->m_etape = other.m_etape;
			this->m_type = other.m_type;
			this->m_genre = other.m_genre;
		}
		return (*this);
	}

	Variable::~Variable() {
	}

	bool Variable::setField(const FieldValue t, const web::json::value & value) {
		switch (t) {
		case FieldValue::categ:
			this->m_categ =
				((!value.is_null()) && value.is_boolean()) ?
				value.as_bool() : false;
			return true;
		case FieldValue::etape:
			this->m_etape =
				((!value.is_null()) && value.is_number()) ?
				value.as_integer() : 0;
			return true;
		case FieldValue::varype:
			this->m_type =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return true;
		case FieldValue::genre:
			this->m_genre =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return true;
		default:
			break;
		}    // t
		return (DatasetChild::setField(t, value));
	}    // setField

	void Variable::write_json(web::json::value &value,
		const ItemGenerator &gen) const {
		DatasetChild::write_json(value, gen);
		String key;
		if (gen.get_key(FieldValue::categ, key)) {
			value[key] = web::json::value::boolean(this->is_categ());
		}
		if (gen.get_key(FieldValue::etape, key)) {
			value[key] = web::json::value::number(this->etape());
		}
		if (gen.get_key(FieldValue::varype, key)) {
			const String &s = this->var_type();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
		if (gen.get_key(FieldValue::genre, key)) {
			const String &s = this->genre();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
	}    // write_json
///////////////////////////////////
}// namespace intra
/////////////////////////////////
//eof: variable.cpp
