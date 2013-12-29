//dataset.cpp
////////////////////////////
#include "dataset.h"
////////////////////////////
namespace intra {
	//////////////////////////////////////////////
	Dataset::Dataset() {
	}

	Dataset::Dataset(int nId, int nVersion, bool bSelected, const String &sSigle,
		const String &sName, const String &sRem) :
		SigleNamedItem(nId, nVersion, bSelected, sSigle, sName, sRem) {
	}

	Dataset::Dataset(const String &sSigle) :
		SigleNamedItem(sSigle) {
	}

	Dataset::Dataset(const Dataset &other) :
		SigleNamedItem(other) {
	}

	Dataset & Dataset::operator=(const Dataset &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return (*this);
	}

	Dataset::~Dataset() {
	}
	////////////////////////////////////////////////
}// namespace intra
//////////////////////////
// eof: dataset.h
