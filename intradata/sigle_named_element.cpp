// sigle_named_element.h
///////////////////////////////
#include "sigle_named_element.h"
/////////////////////////////////////
namespace intra {
	//////////////////////////////////
	SigleNamedItem::SigleNamedItem() {
	}

	SigleNamedItem::SigleNamedItem(int nId, int nVersion, bool bSelected,
		const String &sSigle, const String &sName, const String &sRem) :
		BaseItem(nId, nVersion, bSelected), m_sigle(sSigle), m_name(sName), m_rem(
		sRem) {
	}

	SigleNamedItem::SigleNamedItem(const String &sSigle) :
		m_sigle(sSigle), m_name(sSigle), m_rem(sSigle) {
	}

	SigleNamedItem::SigleNamedItem(const SigleNamedItem &other) :
		BaseItem(other), m_sigle(other.m_sigle), m_name(other.m_name), m_rem(
		other.m_rem) {
	}

	SigleNamedItem & SigleNamedItem::operator=(const SigleNamedItem &other) {
		if (this != &other) {
			BaseItem::operator=(other);
			this->m_sigle = other.m_sigle;
			this->m_name = other.m_name;
			this->m_rem = other.m_rem;
		}
		return (*this);
	}

	SigleNamedItem::~SigleNamedItem() {
	}

	bool SigleNamedItem::setField(const FieldValue t,
		const web::json::value & value) {
		switch (t) {
		case FieldValue::sigle:
			this->m_sigle =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return (true);
		case FieldValue::name:
			this->m_name =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return (true);
		case FieldValue::remarques:
			this->m_rem =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return (true);
		default:
			break;
		}    // t
		return (BaseItem::setField(t, value));
	}    // setField

	void SigleNamedItem::write_json(web::json::value &value,
		const ItemGenerator &gen) const {
		BaseItem::write_json(value, gen);
		String key;
		if (gen.get_key(FieldValue::sigle, key)) {
			const String &s = this->sigle();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
		if (gen.get_key(FieldValue::name, key)) {
			const String &s = this->name();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
		if (gen.get_key(FieldValue::remarques, key)) {
			const String &s = this->remarques();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
	}    // write_json
	/////////////////////////
}// bamespace intra
//////////////////////////////
//eof: sigle_named_element.h
