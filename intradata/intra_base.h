#ifndef __INTRA_BASE_H__
#define  __INTRA_BASE_H__
/////////////////////////////////////
#include <memory>
#include <vector>
/////////////////////////////////
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
//////////////////////////////////////////
#include "item_generator.h"
////////////////////////////////////
namespace intra {
	//////////////////////////////////////////////
	class IntraBase {
	protected:
		IntraBase();
		IntraBase(const IntraBase &other);
		IntraBase & operator=(const IntraBase &other);
	public:
		virtual ~IntraBase();
	public:
		void fill_from_json(const web::json::value &value,
			const ItemGenerator &gen);
		void fill_from_json(const web::json::value &value);
		void write_json(web::json::value &value) const;
		void write_to(String &s) const;
		utility::ostream_t & write(utility::ostream_t &os) const;
		bool setField(const String &key, const web::json::value &value, const ItemGenerator &gen);
	public:
		virtual void write_json(web::json::value &value,
			const ItemGenerator &gen) const;
		virtual bool setField(const FieldValue t, const web::json::value &value);
	};
	// class IntraBase
	//////////////////////////////////////////////
}// namespace intra
//////////////////////////////////////////////
inline utility::ostream_t & operator<<(utility::ostream_t &os, const intra::IntraBase &d){
	return d.write(os);
}// operator<<
////////////////////////////////////////
#endif // __INTRA_BASE_H__
