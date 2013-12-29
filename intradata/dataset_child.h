// dataset_child.h
#ifndef __DATASET_CHILD_H__
#define __DATASET_CHILD_H__
///////////////////////////////////
#include "sigle_named_element.h"
/////////////////////////////////////////
namespace intra {
	///////////////////////////////////////////
	class DatasetChild : public SigleNamedItem {
	protected:
		int m_datasetid;
	protected:
		DatasetChild();
		DatasetChild(int nDatasetId, const String &sSigle);
		DatasetChild(int nId, int nVersion, bool bSelected, int nDatasetId,
			const String &sSigle, const String &sName, const String &sRem);
		DatasetChild(const DatasetChild &other);
		DatasetChild & operator=(const DatasetChild &other);
	public:
		virtual ~DatasetChild(); bool operator==(const DatasetChild &other) const; bool operator<(
			const DatasetChild &other) const;
	public:

		inline int dataset_id(void) const {
			return (this->m_datasetid);
		}

		inline void dataset_id(int n) {
			this->m_datasetid = n;
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value);
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const;
	};
	// class DatasetChild
	/////////////////////////////////////////////
}// namespace intra
///////////////////////////////////////
#endif // __DATASET_CHILD_H__
///////////////////////////
// eof: dataser_child.h
