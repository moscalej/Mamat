#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <cstdlib>
#include <cstring>
#include"TempVec.h"
//#include "polynom.h"
#include "complex.h"


#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG




using namespace std;

typedef TempVec<int, 3> Integer3;

typedef TempVec<complex, 2> Complex2;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Integer3* int3_list = new Integer3[3];
	Integer3 vector1(1, 1, 1);
	Integer3 vector2(2, 2, 2);
	
	Integer3 vector3 = vector1 * vector2 + vector2 - vector1;
	Integer3 vector4 = 5*vector1*5;
	Integer3 vector6(3, 3, 3);
	int k = InnerProduct(vector1, vector2);
	cout << "InnerProduct k is " << k << endl;
	int p = SqNorm(vector1);
	cout << "SqNorm p is " << p << endl;
	int q = SqDistance(vector6, vector1);
	cout << "SqDistance q is " << q << endl;
	
	int x = 10;
	int3_list[0][0] = x;
	x = 9;
	int3_list[0][1] = x;
	x = -8;
	int3_list[0][2] = x;
	cout << int3_list[0] << "clean 0 " << endl;

	int y = 20;
	int3_list[1][0] = y;
	y = 19;
	int3_list[1][1] = y;
	y = 18;
	int3_list[1][2] = y;
	cout << int3_list[1] << "clean 1 " << endl;

	int3_list[2] = int3_list[1] - int3_list[0];
	cout << int3_list[2] << "clean 2 " << endl;

	int t = InnerProduct(5*int3_list[0], int3_list[1]);
	cout << "InnerProduct of t is " << t << endl;
	int m = SqNorm(int3_list[0]);
	cout << "SqNorm of m is " << m << endl;
	int s = SqDistance(int3_list[0], int3_list[2]);
	cout << "SqDistance of s is " << s << endl;

	cout << vector1 << endl;
	cout << vector2 << endl;
	cout << vector3 << endl;
	cout << vector4 << endl;


	Complex2 newcomplex_vect1, newcomplex_vect2;
	complex com1(2, 4), com2(4,5), com3(6,12), com4(-6,-7);
	newcomplex_vect1[0] = com1;
	newcomplex_vect1[1] = com2;
	newcomplex_vect2[0] = com3;
	newcomplex_vect2[1] = com4;

	Complex2 vectr3 = newcomplex_vect1 * newcomplex_vect2 ;
	Complex2 vectr4 =  newcomplex_vect1 * com2;
	Complex2 vectr5 = com3 * newcomplex_vect1 * com2;
	
	delete[] int3_list;

	_CrtDumpMemoryLeaks();
	return 0;
};