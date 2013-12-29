// ConsoleTestApplication.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
///////////////////////////////
#ifdef _MSC_VER
int _tmain(int argc, _TCHAR* argv[])
#else 
int main(int argc, char **argv) 
#endif // _MSC_VER
{
	::testing::InitGoogleTest(&argc, argv);
	int nRet = RUN_ALL_TESTS();
#ifdef _MSC_VER
	int nx;
	std::wcout << std::endl << L"Veuillez entrer un nombre pour quitter S.V.P.: ";
	std::wcin >> nx;
#endif // _MSC_VER
	return (nRet);
}// main

