#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <cstdlib>
#include <cstring>
//#include "polynom.h"
#include "complex.h"
#include "TempVec.h"

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG




using namespace std;

typedef TempVec<int, 3> Integer3;
typedef TempVec<complex, 2> Complex2;

void main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Integer3 vector1(1, 1, 1);
	Integer3 vector2(2, 2, 2);
	Integer3 vector3;
	vector3 = vector1 * vector2;
	vector3.print();
	//Complex2 complex1;
	

	_CrtDumpMemoryLeaks();
	return;
};