// baseitem.cpp
///////////////////////////////
#include "baseitem.h"
/////////////////////////////////////
namespace intra {
	//////////////////////////////////////
	BaseItem::BaseItem() :
		m_id(0), m_version(1), m_selected(false) {
	}

	BaseItem::BaseItem(int nId, int nVersion, bool bSelected) :
		m_id(nId), m_version(nVersion), m_selected(bSelected) {
	}

	BaseItem::BaseItem(const BaseItem &other) :
		IntraBase(other), m_id(other.m_id), m_version(other.m_version), m_selected(
		other.m_selected), m_status(other.m_status) {
	}

	BaseItem & BaseItem::operator=(const BaseItem &other) {
		if (this != &other) {
			IntraBase::operator=(other);
			this->m_id = other.m_id;
			this->m_version = other.m_version;
			this->m_selected = other.m_selected;
			this->m_status = other.m_status;
		}
		return (*this);
	}

	BaseItem::~BaseItem() {

	}

	bool BaseItem::setField(const FieldValue t, const web::json::value & value) {
		switch (t) {
		case FieldValue::id:
			this->m_id =
				((!value.is_null()) && value.is_number()) ?
				value.as_integer() : 0;
			return (true);
		case FieldValue::version:
			this->m_version =
				((!value.is_null()) && value.is_number()) ?
				value.as_integer() : 0;
			return (true);
		case FieldValue::status:
			this->m_status =
				((!value.is_null()) && value.is_string()) ?
				value.as_string() : String();
			return (true);
		case FieldValue::selected:
			this->m_selected =
				((!value.is_null()) && value.is_boolean()) ?
				value.as_bool() : false;
			return (true);
		default:
			break;
		}    // t
		return (false);
	}    // setField

	void BaseItem::write_json(web::json::value &value,
		const ItemGenerator &gen) const {
		String key;
		if (gen.get_key(FieldValue::id, key)) {
			value[key] = web::json::value(this->id());
		}
		if (gen.get_key(FieldValue::version, key)) {
			value[key] = web::json::value::number(this->version());
		}
		if (gen.get_key(FieldValue::selected, key)) {
			value[key] = web::json::value::boolean(this->selected());
		}
		if (gen.get_key(FieldValue::status, key)) {
			const String &s = this->status();
			if (s.empty()) {
				value[key] = web::json::value::null();
			}
			else {
				value[key] = web::json::value::string(s);
			}
		}
	}    // write_json
	//////////////////////////////////////////
}// namespace intra
////////////////////////////////
//eof: baseitem.cpp
