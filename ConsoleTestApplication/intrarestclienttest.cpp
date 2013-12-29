/*
 * File:   intrarestclienttest.cpp
 * Author: boubad
 *
 * Created on 10 déc. 2013, 15:50:47
 */
#include "stdafx.h"
////////////////////////
#include <intra_rest_client.h>
/////////////////////////////////
namespace {
	using namespace intra;
	///////////////////////////

	class IntraRESTClientTest : public ::testing::Test {
	protected:
		static String BASE_URI;
		static String TEST_DATASET_SIGLE;
		static String TEST_VARIABLE_SIGLE;
		static String TEST_VARIABLE_TYPE;
		static int TEST_VARIABLE_ETAPE;
		static String TEST_VARIABLE_GENRE;
		static String TEST_INDIV_SIGLE;
		static String TEST_VALUE_STRING;
		static String TEST_VALUE_STATUS;
	protected:
		std::unique_ptr<IntraRESTClient> m_client;
		DatasetPtr m_set;
		VariablePtr m_var;
		IndivPtr m_ind;
		ValuePtr m_val;
		//

		IntraRESTClientTest() {

		}

		virtual ~IntraRESTClientTest() {

		}

		static void SetUpTestCase() {
			IntraRESTClient oMan(BASE_URI);
			IntraRESTClient *pMan = &oMan;
			ASSERT_TRUE(pMan != nullptr);
			bool bRet = pMan->is_connected_async().get();
			ASSERT_TRUE(bRet);
		} // SetUpTestCase
		static void TearDownTestCase() {
		} // TearDownTestCase
		virtual void SetUp() {
			this->m_client.reset(new IntraRESTClient(BASE_URI));
			IntraRESTClient *pMan = this->m_client.get();
			ASSERT_TRUE(pMan != nullptr);
			int nc = pMan->get_all_datasets_count_async().get();
			ASSERT_TRUE(nc > 0);
			std::vector<DatasetPtr> oVec;
			bool bRet = pMan->get_datasets_async(0, nc, oVec).get();
			ASSERT_TRUE(bRet);
			ASSERT_FALSE(oVec.empty());
			ASSERT_EQ((size_t) nc, oVec.size());
			this->m_set = oVec[0];
			Dataset *pSet = this->m_set.get();
			ASSERT_TRUE(pSet != nullptr);
			ASSERT_TRUE(pSet->id() != 0);
		} // SetUp

		virtual void TearDown() {
			this->m_val.reset();
			this->m_ind.reset();
			this->m_var.reset();
			this->m_set.reset();
			this->m_client.reset();
		} // TearDown
	};
	// class IntraRESTClientTest
	String IntraRESTClientTest::BASE_URI(U("http://caprica"));
	String IntraRESTClientTest::TEST_DATASET_SIGLE(U("TESTSET"));
	String IntraRESTClientTest::TEST_VARIABLE_SIGLE(U("TESTVAR"));
	String IntraRESTClientTest::TEST_VARIABLE_TYPE(U("float"));
	int IntraRESTClientTest::TEST_VARIABLE_ETAPE(1);
	String IntraRESTClientTest::TEST_VARIABLE_GENRE(U("input"));
	String IntraRESTClientTest::TEST_INDIV_SIGLE(U("TESTINDIV"));
	String IntraRESTClientTest::TEST_VALUE_STRING(U("3.14"));
	String IntraRESTClientTest::TEST_VALUE_STATUS(U("OK"));
	//

	TEST_F(IntraRESTClientTest, IsConnected) {
		IntraRESTClient *pMan = this->m_client.get();
		ASSERT_TRUE(pMan != nullptr);
		bool bRet = pMan->is_connected_async().get();
		ASSERT_TRUE(bRet);
	} // IsConnected

	TEST_F(IntraRESTClientTest, GetDatasets) {
		IntraRESTClient *pMan = this->m_client.get();
		ASSERT_TRUE(pMan != nullptr);
		int nc = pMan->get_all_datasets_count_async().get();
		ASSERT_TRUE(nc > 0);
		int taken = 5;
		int skip = 0;
	//	ucout << std::endl << U("NB DATASETS: ") << nc << std::endl;
		while (skip < nc){
			std::vector<DatasetPtr> oVec;
			bool bRet = pMan->get_datasets_async(skip, taken, oVec).get();
			ASSERT_TRUE(bRet);
			ASSERT_FALSE(oVec.empty());
			for (auto it = oVec.begin(); it != oVec.end(); ++it){
				DatasetPtr o = *it;
				Dataset *p = o.get();
				ASSERT_TRUE(o != nullptr);
			//	ucout << *p << std::endl;
			}// it
			skip += taken;
		}// skip
		//ucout << std::endl;
	} // GetDatasets
	TEST_F(IntraRESTClientTest, GetVariables) {
		IntraRESTClient *pMan = this->m_client.get();
		ASSERT_TRUE(pMan != nullptr);
		Dataset *pSet = this->m_set.get();
		ASSERT_TRUE(pSet != nullptr);
		int datasetid = pSet->id();
		ASSERT_TRUE(datasetid != 0);
		std::vector<VariablePtr> oVec;
		bool bRet = pMan->get_datalines_variables_async(datasetid, oVec).get();
	//	ucout << std::endl << U("DATALINES VARIABLES FOR DATASET ") << pSet->sigle() << std::endl;
		for (auto it = oVec.begin(); it != oVec.end(); ++it){
			VariablePtr o = *it;
			Variable *p = o.get();
			ASSERT_TRUE(o != nullptr);
			//ucout << *p << std::endl;
		}// it
	//	ucout << std::endl;
	} // GetVariables
	TEST_F(IntraRESTClientTest, GetHeader) {
		IntraRESTClient *pMan = this->m_client.get();
		ASSERT_TRUE(pMan != nullptr);
		Dataset *pSet = this->m_set.get();
		ASSERT_TRUE(pSet != nullptr);
		int datasetid = pSet->id();
		ASSERT_TRUE(datasetid != 0);
		std::vector<String> oVec;
		bool bRet = pMan->get_datalines_header_async(datasetid, oVec).get();
		//ucout << std::endl << U("DATALINES HEADER FOR DATASET ") << pSet->sigle() << std::endl;
		for (auto it = oVec.begin(); it != oVec.end(); ++it){
			const String & s = *it;
		//	ucout << s << U("\t");
		}// it
	//	ucout << std::endl;
	} // GetHeader
	TEST_F(IntraRESTClientTest, GetValues) {
		typedef DataLine<> DataLineType;
		typedef std::shared_ptr<DataLineType> DataLinePtrType;
		IntraRESTClient *pMan = this->m_client.get();
		ASSERT_TRUE(pMan != nullptr);
		Dataset *pSet = this->m_set.get();
		ASSERT_TRUE(pSet != nullptr);
		int datasetid = pSet->id();
		ASSERT_TRUE(datasetid != 0);
		int nc = pMan->get_datalines_count_async(datasetid).get();
		ASSERT_TRUE(nc > 0);
		int taken = 20;
		int skip = 0;
	//	ucout << std::endl << U("DATALINES VALUES FOR DATASET ") << pSet->sigle() << std::endl;
		while (skip < nc){
			std::vector<DataLinePtrType> oVec;
			bool bRet = pMan->get_datalines_values_async(datasetid, skip, taken, oVec).get();
			ASSERT_TRUE(bRet);
			ASSERT_FALSE(oVec.empty());
			for (auto it = oVec.begin(); it != oVec.end(); ++it){
				DataLinePtrType o = *it;
				DataLineType *p = o.get();
				ASSERT_TRUE(o != nullptr);
			//	ucout << *p << std::endl;
			}// it
			skip += taken;
		}// skip
	//	ucout << std::endl;
	} // GetValues
	//////////////////////////////////////////////////////////
}
// namespace

