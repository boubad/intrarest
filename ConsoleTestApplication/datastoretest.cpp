#include "stdafx.h"
////////////////////////
#include <data_store.h>
/////////////////////////////////
namespace {
	using namespace intra;
	///////////////////////////

	class DataStoreTest : public ::testing::Test {
	public:
		typedef DataStore<> DataStoreType;
		typedef IndivLine<> IndivLineType;
		typedef std::shared_ptr<IndivLineType> IndivLinePtrType;
	protected:
		static String BASE_URI;
		static DatasetPtr m_st_set;
	protected:
		std::unique_ptr<DataStoreType> m_store;
		//

		DataStoreTest() {

		}

		virtual ~DataStoreTest() {

		}

		static void SetUpTestCase() {
			IntraRESTClient oMan(BASE_URI);
			IntraRESTClient *pMan = &oMan;
			ASSERT_TRUE(pMan != nullptr);
			bool bRet = pMan->is_connected_async().get();
			ASSERT_TRUE(bRet);
			int nc = pMan->get_all_datasets_count_async().get();
			ASSERT_TRUE(nc > 0);
			std::vector<DatasetPtr> oVec;
			bRet = pMan->get_datasets_async(0, nc, oVec).get();
			ASSERT_TRUE(bRet);
			ASSERT_FALSE(oVec.empty());
			ASSERT_EQ((size_t) nc, oVec.size());
			m_st_set = oVec[0];
			Dataset *pSet =m_st_set.get();
			ASSERT_TRUE(pSet != nullptr);
			ASSERT_TRUE(pSet->id() != 0);
		} // SetUpTestCase
		static void TearDownTestCase() {
			m_st_set.reset();
		} // TearDownTestCase
		virtual void SetUp() {
			this->m_store.reset(new DataStoreType(BASE_URI));
			DataStoreType *pStore = this->m_store.get();
			ASSERT_TRUE(pStore != nullptr);
			bool bRet = pStore->is_connected_async().get();
			ASSERT_TRUE(bRet);
			pStore->set_dataset(m_st_set);
		} // SetUp

		virtual void TearDown() {
			this->m_store.reset();
		} // TearDown
	};
	// class DataStoreTest
	String DataStoreTest::BASE_URI(U("http://caprica"));
	DatasetPtr DataStoreTest::m_st_set;
	//

	TEST_F(DataStoreTest, Variables) {
		DataStoreType *pStore = this->m_store.get();
		size_t n = pStore->variables_count();
		ASSERT_TRUE(n > 0);
		for (size_t i = 0; i < n; ++i){
			const Variable *pVar = pStore->variable(i);
			ASSERT_TRUE(pVar != nullptr);
			VariableType eType = pStore->variable_type(i);
			ASSERT_TRUE(eType != VariableType::unknownType);
			pStore->is_categ_variable(i);
		}// i
	} // Variables
	TEST_F(DataStoreTest, GetAllDatasets) {
		DataStoreType *pStore = this->m_store.get();
		std::vector<DatasetPtr> oVec;
	//	ucout << std::endl << U("DATASTORE DATASETS: ") << std::endl;
		bool bRet = pStore->get_all_datasets_async(oVec).get();
		ASSERT_TRUE(bRet);
		ASSERT_TRUE(bRet);
		ASSERT_FALSE(oVec.empty());
		for (auto it = oVec.begin(); it != oVec.end(); ++it){
			DatasetPtr o = *it;
			Dataset *p = o.get();
			ASSERT_TRUE(o != nullptr);
		//	ucout << *p << std::endl;
		}// it
	//	ucout << std::endl;
	} // Variables
	TEST_F(DataStoreTest, GetHeader) {
		DataStoreType *pStore = this->m_store.get();
		std::vector<String> oVec;
		bool bRet = pStore->get_datalines_header_async(oVec).get();
		ASSERT_TRUE(bRet);
	//	ucout << std::endl << U("DATASTORE HEADER") << std::endl;
		for (auto it = oVec.begin(); it != oVec.end(); ++it){
			const String & s = *it;
	//	ucout << s << U("\t");
		}// it
	//	ucout << std::endl;
	} // GetHeader
	TEST_F(DataStoreTest, GetLines) {
		DataStoreType *pStore = this->m_store.get();
		int nc = pStore->get_datalines_count_async().get();
		ASSERT_TRUE(nc > 0);
		int taken = 20;
		int skip = 0;
	//	ucout << std::endl << U("DATASTORE LINES") << std::endl;
		while (skip < nc){
			std::vector<IndivLinePtrType> oVec;
			bool bRet = pStore->get_datalines_async(skip, taken, oVec).get();
			ASSERT_TRUE(bRet);
			for (auto it = oVec.begin(); it != oVec.end(); ++it){
				IndivLinePtrType o = *it;
				IndivLineType *p = o.get();
				ASSERT_TRUE(p != nullptr);
			//	ucout << *p << std::endl;
			}// it
			skip += taken;
		}// skip
	//	ucout << std::endl;
	} // GetHeader
	//////////////////////////////////////////////////////////
}
// namespace

