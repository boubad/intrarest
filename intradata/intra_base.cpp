// intra_base.cpp
////////////////////////////////
#include "intra_base.h"
///////////////////////////////////
namespace intra {
	/////////////////////////////////////////
	IntraBase::IntraBase() {
	}
	IntraBase::IntraBase(const IntraBase & /*other */) {
	}
	IntraBase & IntraBase::operator=(const IntraBase & /*other */) {
		return (*this);
	}
	IntraBase::~IntraBase() {
	}
	bool IntraBase::setField(const String &key, const web::json::value &value, const ItemGenerator &gen) {
		FieldValue t = gen.get(key);
		return (this->setField(t, value));
	}    // setField
	bool IntraBase::setField(const FieldValue /*t */,
		const web::json::value & /*value */) {
		return (false);
	}    // setField
	void IntraBase::fill_from_json(const web::json::value &value, const ItemGenerator &gen) {
		auto iend = value.cend();
		for (auto it = value.cbegin(); it != iend; ++it) {
			const web::json::value & vname = it->first;
			const web::json::value & vval = it->second;
			String key = vname.as_string();
			FieldValue t = gen.get(key);
			this->setField(t, vval);
		}    // it
	}    // fill_from_json
	void IntraBase::fill_from_json(const web::json::value &value) {
		ItemGenerator gen;
		this->fill_from_json(value, gen);
	}
	void IntraBase::write_json(web::json::value & /*value */,
		const ItemGenerator & /*gen */) const {
	}    // write_json

	void IntraBase::write_json(web::json::value &value) const {
		ItemGenerator gen;
		this->write_json(value, gen);
	}    // write_json
	utility::ostream_t & IntraBase::write(utility::ostream_t &os) const {
		web::json::value value;
		this->write_json(value);
		value.serialize(os);
		return os;
	}    // write
	void IntraBase::write_to(String &s) const {
		web::json::value value;
		this->write_json(value);
		utility::stringstream_t os;
		value.serialize(os);
		s = os.str();
	}    // BaseItem
	//////////////////////////////////////////
}// namespace intra
