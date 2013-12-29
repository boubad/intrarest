// indiv.cpp
////////////////////////////
#include "indiv.h"
///////////////////////////////
namespace intra {
	////////////////////////////////////////////
	Indiv::Indiv() :
		m_hasimage(false), m_size(0) {
	}

	Indiv::Indiv(int nId, int nVersion, bool bSelected, int nDatasetId,
		const String &sSigle, const String &sName, const String &sRem,
		const String &sStatus) :
		DatasetChild(nId, nVersion, bSelected, nDatasetId, sSigle, sName, sRem), m_hasimage(
		false), m_size(0) {
		this->m_status = sStatus;
	}

	Indiv::Indiv(int nDatasetId, const String &sSigle) :
		DatasetChild(nDatasetId, sSigle), m_hasimage(false), m_size(0) {
	}

	Indiv::Indiv(const Indiv &other) :
		DatasetChild(other), m_hasimage(other.m_hasimage), m_size(0) {
		const size_t n = other.m_size;
		if (n > 0) {
			this->m_data.reset(new byte[n]);
			byte *pDest = this->m_data.get();
			const byte *pSrc = other.m_data.get();
			if ((pSrc != nullptr) && (pDest != nullptr)) {
				for (size_t i = 0; i < n; ++i) {
					pDest[i] = pSrc[i];
				} // i
				this->m_size = n;
			}
			else {
				this->m_data.reset();
			}
		} // other.m_size
	}

	Indiv & Indiv::operator=(const Indiv &other) {
		if (this != &other) {
			DatasetChild::operator=(other);
			this->m_hasimage = other.m_hasimage;
			this->m_data.reset();
			this->m_size = 0;
			const size_t n = other.m_size;
			if (n > 0) {
				this->m_data.reset(new byte[n]);
				byte *pDest = this->m_data.get();
				const byte *pSrc = other.m_data.get();
				if ((pSrc != nullptr) && (pDest != nullptr)) {
					for (size_t i = 0; i < n; ++i) {
						pDest[i] = pSrc[i];
					} // i
					this->m_size = n;
				}
				else {
					this->m_data.reset();
				}
			} // other.m_size
		}
		return (*this);
	}

	Indiv::~Indiv() {
	}

	void Indiv::data(const byte *pSrc, const size_t n) {
		if ((pSrc == nullptr) || (n < 1)) {
			this->m_data.reset();
			this->m_size = 0;
			return;
		}
		byte *pOld = this->m_data.get();
		if (pOld != nullptr) {
			byte *px = const_cast<byte *>(pSrc);
			if (px == pOld) {
				return;
			}
			this->m_data.reset();
			this->m_size = 0;
		}
		if (pOld == pSrc) {
			return;
		}
		if (n > 0) {
			this->m_data.reset(new byte[n]);
			byte *pDest = this->m_data.get();
			if (pDest != nullptr) {
				for (size_t i = 0; i < n; ++i) {
					pDest[i] = pSrc[i];
				} // i
				this->m_size = n;
			}
			else {
				this->m_data.reset();
			}
		} // other.m_size
	} // data

	bool Indiv::setField(const FieldValue t, const web::json::value & value) {
		switch (t) {
		case FieldValue::hasimage:
			this->m_hasimage =
				((!value.is_null()) && value.is_boolean()) ?
				value.as_bool() : false;
			return true;
		case FieldValue::imagedata: {
										this->m_size = 0;
										this->m_data.reset();
										if (value.is_array()) {
											const size_t n = value.size();
											if (n > 0) {
												this->m_data.reset(new byte[n]);
												byte *pDest = this->m_data.get();
												if (pDest != nullptr) {
													for (size_t i = 0; i < n; ++i) {
														byte b = (byte) 0;
														auto v = value.get(i);
														if ((!v.is_null()) && v.is_number()) {
															b = (byte) v.as_integer();
														}
														pDest[i] = b;
													} // i
													this->m_size = n;
												} // pDest
											} // n
										} // array
		}
			return true;
		default:
			break;
		} // t
		return (DatasetChild::setField(t, value));
	} // setField

	void Indiv::write_json(web::json::value &value,
		const ItemGenerator &gen) const {
		DatasetChild::write_json(value, gen);
		String key;
		if (gen.get_key(FieldValue::hasimage, key)) {
			value[key] = web::json::value::boolean(this->has_image());
		}
		if (gen.get_key(FieldValue::imagedata, key)) {
			size_t n = 0;
			const byte *pData = this->data(n);
			if ((pData != nullptr) && (n > 0)) {
				if (gen.get_key(FieldValue::imagedata, key)) {
					web::json::value oAr = web::json::value::array(n);
					for (size_t i = 0; i < n; ++i) {
						oAr[i] = web::json::value(pData[i]);
					} // i
					value[key] = oAr;
				} // key
			}
			else {
				value[key] = web::json::value::null();
			}
		}

	} // write_json
	///////////////////////////////////////////////
}// namespace intra
////////////////////////////////
//eof: indiv.cpp
