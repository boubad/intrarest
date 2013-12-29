// intra_value.cpp
/////////////////////////////
#include "intra_value.h"
///////////////////////////////
namespace intra {
	///////////////////////////////////////
	Value::Value() :
		m_variableid(0), m_individ(0) {
	}

	Value::Value(int nId, int nVersion, bool bSelected, int nVarId, int nIndId,
		const String &sStatus) :
		BaseItem(nId, nVersion, bSelected), m_variableid(nVarId), m_individ(
		nIndId) {
		this->m_status = sStatus;
	}

	Value::Value(int nVarId, int nIndId) :
		m_variableid(nVarId), m_individ(nIndId) {
	}

	Value::Value(const Value &other) :
		BaseItem(other), m_variableid(other.m_variableid), m_individ(
		other.m_individ), m_val(other.m_val), m_varsigle(
		other.m_varsigle), m_indsigle(other.m_indsigle) {
	}

	Value & Value::operator=(const Value &other) {
		if (this != &other) {
			BaseItem::operator=(other);
			this->m_variableid = other.m_variableid;
			this->m_individ = other.m_individ;
			this->m_val = other.m_val;
			this->m_varsigle = other.m_varsigle;
			this->m_indsigle = other.m_indsigle;
		}
		return (*this);
	}

	Value::~Value() {
	}

	bool Value::operator==(const Value &other) const {
		if ((this->m_id != 0) || (other.m_id != 0)) {
			if (this->m_id == other.m_id) {
				return (true);
			}
			else {
				return (false);
			}
		}
		return ((this->m_variableid == other.m_variableid)
			&& (this->m_individ == other.m_individ));
	}

	bool Value::operator<(const Value &other) const {
		if (this->m_individ < other.m_individ) {
			return (true);
		}
		else if (this->m_individ > other.m_individ) {
			return (false);
		}
		return (this->m_variableid < other.m_variableid);
	} // operator<

	bool Value::setField(const FieldValue t, const web::json::value & value) {
		switch (t) {
		case FieldValue::variableid:
			this->m_variableid =
				((!value.is_null()) && value.is_number()) ?
				value.as_integer() : 0;
			return (true);
		case FieldValue::individ:
			this->m_individ =
				((!value.is_null()) && value.is_number()) ?
				value.as_integer() : 0;
			return (true);
		case FieldValue::value:
			this->m_val =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return (true);
		case FieldValue::variableSigle:
			this->m_varsigle =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return (true);
		case FieldValue::indivSigle:
			this->m_indsigle =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return (true);
		default:
			break;
		} // t
		return (BaseItem::setField(t, value));
	} // setField

	void Value::write_json(web::json::value &value,
		const ItemGenerator &gen) const {
		BaseItem::write_json(value, gen);
		String key;
		if (gen.get_key(FieldValue::variableid, key)) {
			value[key] = web::json::value::number(this->variable_id());
		}
		if (gen.get_key(FieldValue::individ, key)) {
			value[key] = web::json::value::number(this->indiv_id());
		}
		if (gen.get_key(FieldValue::value, key)) {
			const String &s = this->value();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
		if (gen.get_key(FieldValue::variableSigle, key)) {
			const String &s = this->variable_sigle();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
		if (gen.get_key(FieldValue::indivSigle, key)) {
			const String &s = this->indiv_sigle();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
	} // write_json
	///////////////////////////////////////////
}// namespace intra