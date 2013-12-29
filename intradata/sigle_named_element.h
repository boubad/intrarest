// sigle_named_element.h
#ifndef __SIGLE_NAMED_ELEMENT_H__
#define __SIGLE_NAMED_ELEMENT_H__
////////////////////////////////////////
#include "baseitem.h"
/////////////////////////////////////////////
namespace intra {
	////////////////////////////////////////////////
	class SigleNamedItem : public BaseItem {
	protected:
		String m_sigle;
		String m_name;
		String m_rem;
	protected:
		SigleNamedItem();
		SigleNamedItem(int nId, int nVersion, bool bSelected, const String &sSigle,
			const String &sName, const String &sRem);
		SigleNamedItem(const String &sSigle);
		SigleNamedItem(const SigleNamedItem &other);
		SigleNamedItem & operator=(const SigleNamedItem &other);
	public:
		virtual ~SigleNamedItem();

		inline bool operator==(const SigleNamedItem &other) const {
			return (this->m_sigle == other.m_sigle);
		}

		inline bool operator<(const SigleNamedItem &other) const {
			return (this->m_sigle < other.m_sigle);
		}
	public:

		inline const String &sigle(void) const {
			return (this->m_sigle);
		}

		inline void sigle(const String &s) {
			this->m_sigle = s;
		}

		inline const String &name(void) const {
			return (this->m_name);
		}

		inline void name(const String &s) {
			this->m_name = s;
		}

		inline const String &remarques(void) const {
			return (this->m_rem);
		}

		inline void remarques(const String &s) {
			this->m_rem = s;
		}
	public:
		virtual bool setField(const FieldValue t, const web::json::value &value);
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const;
	};
	// class SigleNamedItem
	////////////////////////////////////////////////////
}// namespace intra
////////////////////////////////////////////
#endif // __SIGLE_NAMED_ELEMENT_H__
///////////////////////////
// eof: sigle_named_element.h
