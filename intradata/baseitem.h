//baseitem.h
#ifndef __BASEITEM_H__
#define  __BASEITEM_H__
/////////////////////////////////
#include "intra_base.h"
/////////////////////////////////////////
namespace intra {
	////////////////////////////////////////////
	class BaseItem : public IntraBase {
	protected:
		int m_id;
		int m_version; bool m_selected;
		String m_status;
	protected:
		BaseItem();
		BaseItem(int nId, int nVersion = 1, bool bSelected = false);
		BaseItem(const BaseItem &other);
		BaseItem & operator=(const BaseItem &other);
	public:
		virtual ~BaseItem();

		inline bool operator==(const BaseItem &other) const {
			return (this->m_id == other.m_id);
		}

		inline bool operator<(const BaseItem &other) const {
			return (this->m_id < other.m_id);
		}
	public:

		inline int id(void) const {
			return (this->m_id);
		}

		inline void id(int n) {
			this->m_id = n;
		}

		inline int version(void) const {
			return (this->m_version);
		}

		inline void version(int n) {
			this->m_version = n;
		}

		inline bool selected(void) const {
			return (this->m_selected);
		}

		inline void selected(bool b) {
			this->m_selected = b;
		}

		inline const String & status(void) const {
			return (this->m_status);
		}

		inline void status(const String &s) {
			this->m_status = s;
		}
	public:
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const;
		virtual bool setField(const FieldValue t, const web::json::value &value);
	};
	// class BaseItem
	///////////////////////////////////////
}//namespace intra
///////////////////////////////////
#endif // __BASEITEM_H__
