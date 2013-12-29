// item_generator.h
#ifndef __ITEM_GENERATOR_H__
#define __ITEM_GENERATOR_H__
//////////////////////////////////
#include <map>
//////////////////////////////////////
#include <cpprest/json.h>
////////////////////////////////////
namespace intra {
	///////////////////////////////////////////////
	typedef utility::string_t String;
	typedef utility::char_t Char;
	typedef utility::char_t byte;
	///////////////////////////////////////////////
	enum FieldValue {
		unknown,
		id,
		version,
		selected,
		status,
		sigle,
		name,
		remarques,
		datasetid,
		hasimage,
		imagedata,
		categ,
		etape,
		varype,
		genre,
		variableid,
		individ,
		value,
		datasets,
		variables,
		indivs,
		values,
		dataline,
		datalines,
		variableSigle,
		indivSigle
	}; // enum FiledValue
	///////////////////////////////////////
	class ItemGenerator {
		std::map<String, FieldValue> m_map;
		std::map<FieldValue, String> m_invmap;
	public:
		ItemGenerator();
		ItemGenerator(const ItemGenerator &other);
		ItemGenerator & operator=(const ItemGenerator &other);
		virtual ~ItemGenerator();
	public:
		FieldValue get(const String &key) const;
		bool get_key(const FieldValue v, String &sRet) const;
	};// class ItemGenerator
	////////////////////////////
}// namespace intra
////////////////////////////////////
#endif // __ITEM_GENERATOR_H__
