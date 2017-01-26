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
	Integer3* int3_list = new Integer3[3];
	Integer3 vector1(1, 1, 1);
	Integer3 vector2(2, 2, 2);
	
	Integer3 vector3 = vector1 * vector2 + vector2 - vector1;
	Integer3 vector4 = 5*vector1*5;
	Integer3 vector6(3, 3, 3);
	int k = InnerProduct(vector1, vector2);
	cout << "k is " << k << endl;
	int p = SqNorm(vector1);
	cout << "p is " << p << endl;
	int q = SqDistance(vector6, vector1);
	cout << "q is " << q << endl;
	
	int x = 10;
	int3_list[0][0] = x;
	x = 9;
	int3_list[0][1] = x;
	x = 8;
	int3_list[0][2] = x;
	int3_list[0].print();

	int y = 20;
	int3_list[1][0] = y;
	y = 19;
	int3_list[1][1] = y;
	y = 18;
	int3_list[1][2] = y;

	int3_list[1].print();

	int3_list[2] = int3_list[1] + int3_list[0];

	int3_list[2].print();

	int t = InnerProduct(5*int3_list[0], int3_list[1]);
	cout << "innerProduct of t is " << t << endl;

	vector1.print();
	vector2.print();
	vector3.print();
	vector4.print();
	
	
	delete[] int3_list;

	_CrtDumpMemoryLeaks();
	return;
};