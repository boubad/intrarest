// item_generator.cpp
#include "item_generator.h"
//////////////////////////////////
namespace intra {
	///////////////////////////////////////////////
	ItemGenerator::ItemGenerator() {
		std::map<String, FieldValue> &oMap = this->m_map;
		oMap[U("id")] = FieldValue::id;
		oMap[U("version")] = FieldValue::version;
		oMap[U("selected")] = FieldValue::selected;
		oMap[U("status")] = FieldValue::status;
		oMap[U("sigle")] = FieldValue::sigle;
		oMap[U("name")] = FieldValue::name;
		oMap[U("remarques")] = FieldValue::remarques;
		oMap[U("datasetId")] = FieldValue::datasetid;
		oMap[U("hasImage")] = FieldValue::hasimage;
		oMap[U("dataBytes")] = FieldValue::imagedata;
		oMap[U("categ")] = FieldValue::categ;
		oMap[U("etape")] = FieldValue::etape;
		oMap[U("varType")] = FieldValue::varype;
		oMap[U("genre")] = FieldValue::genre;
		oMap[U("variableId")] = FieldValue::variableid;
		oMap[U("indivId")] = FieldValue::individ;
		oMap[U("value")] = FieldValue::value;
		oMap[U("datasets")] = FieldValue::datasets;
		oMap[U("variables")] = FieldValue::variables;
		oMap[U("indivs")] = FieldValue::indivs;
		oMap[U("values")] = FieldValue::values;
		oMap[U("dataline")] = FieldValue::dataline;
		oMap[U("lines")] = FieldValue::datalines;
		oMap[U("variableSigle")] = FieldValue::variableSigle;
		oMap[U("indivSigle")] = FieldValue::indivSigle;
		std::map<FieldValue, String> &pMap = this->m_invmap;
		for (auto it = oMap.begin(); it != oMap.end(); ++it) {
			String val = it->first;
			FieldValue key = it->second;
			pMap[key] = val;
		} // it
	}

	ItemGenerator::ItemGenerator(const ItemGenerator &other) :
		m_map(other.m_map) {

	}

	ItemGenerator & ItemGenerator::operator=(const ItemGenerator &other) {
		if (this != &other) {
			this->m_map = other.m_map;
		}
		return (*this);
	}

	ItemGenerator::~ItemGenerator() {

	}

	FieldValue ItemGenerator::get(const String &key) const {
		const std::map<String, FieldValue> & p = this->m_map;
		FieldValue oRet = FieldValue::unknown;
		auto it = p.find(key);
		if (it != p.end()) {
			oRet = it->second;
		}
		return oRet;
	} // get

	bool ItemGenerator::get_key(const FieldValue v, String &sRet) const {
		sRet.clear();
		if (v != FieldValue::unknown) {
			const std::map<FieldValue, String> & p = this->m_invmap;
			auto it = p.find(v);
			if (it != p.end()) {
				sRet = it->second;
				return (true);
			}
		}
		return (false);
	} // getKey
	///////////////////////////////////////////////////
}// namespace intra