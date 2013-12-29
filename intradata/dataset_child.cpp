//dataset_child.cpp
///////////////////////
#include "dataset_child.h"
////////////////////////////////
namespace intra {
	//////////////////////////////////////

	DatasetChild::DatasetChild() :
		m_datasetid(0) {
	}

	DatasetChild::DatasetChild(int nDatasetId, const String &sSigle) :
		SigleNamedItem(sSigle), m_datasetid(nDatasetId) {
	}

	DatasetChild::DatasetChild(int nId, int nVersion, bool bSelected,
		int nDatasetId, const String &sSigle, const String &sName,
		const String &sRem) :
		SigleNamedItem(nId, nVersion, bSelected, sSigle, sName, sRem), m_datasetid(
		nDatasetId) {
	}

	DatasetChild::DatasetChild(const DatasetChild &other) :
		SigleNamedItem(other), m_datasetid(other.m_datasetid) {
	}

	DatasetChild & DatasetChild::operator=(const DatasetChild &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
			this->m_datasetid = other.m_datasetid;
		}
		return (*this);
	}

	DatasetChild::~DatasetChild() {
	}

	bool DatasetChild::operator==(const DatasetChild &other) const {
		return ((this->m_datasetid == other.m_datasetid)
			&& (SigleNamedItem::operator==(other)));
	}

	bool DatasetChild::operator<(const DatasetChild &other) const {
		if (this->m_datasetid < other.m_datasetid) {
			return (true);
		}
		else if (this->m_datasetid > other.m_datasetid) {
			return (false);
		}
		return (SigleNamedItem::operator<(other));
	}

	bool DatasetChild::setField(const FieldValue t,
		const web::json::value & value) {
		switch (t) {
		case FieldValue::datasetid:
			this->m_datasetid =
				((!value.is_null()) && value.is_number()) ?
				value.as_integer() : 0;
			return true;
		default:
			break;
		}    // t
		return (SigleNamedItem::setField(t, value));
	}    // setField

	void DatasetChild::write_json(web::json::value &value,
		const ItemGenerator &gen) const {
		SigleNamedItem::write_json(value, gen);
		String key;
		if (gen.get_key(FieldValue::datasetid, key)) {
			value[key] = web::json::value::number(this->dataset_id());
		}
	}    // write_json
	///////////////////////////////
	/////////////////////////////////////
}// namespace intra
/////////////////////////////
//eof: dataset_child.h
