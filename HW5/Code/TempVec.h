#ifndef _TEMPVEC_H
#define _TEMPVEC_H

#include <iostream>

enum Result { FAILURE, SUCCESS };

using namespace std;

template <class T,int size>
class TempVec {
	public:
		// Default Constructor
		TempVec()
		{
			try 
			{
				for (int i = 0; i < size; i++)
				{
					if (i > size || i < 0) throw "Error TempVec. Illegal index";
					coordinates_[i] = 0;
				}
			}
			catch (const string errMessage)
			{
				//cerr << errMessage << endl;
			}
		}

		// Constructor for 3D coordinates
		TempVec(int x, int y, int z);

		// Default Destructor
		virtual ~TempVec() {}

		// Operator Overloaders '+', '*' 
		TempVec<T, size> operator+(const TempVec<T, size>& rhs);
		TempVec<T, size> operator*(const TempVec<T, size>& rhs);

		// Vector Math
		void addVectors(T vec1, T vec2);
		void subtractVectors(T vec1, T vec2);
		void multiply_by_scalar(int num, T vec1);
		//int InnerProduct(int u, int v);
		//int SqNorm(int u);
		//int SqDistance(int u);
		
		void print();

	protected:
		
		T coordinates_[size];
};

template <class T, int size>
TempVec<T, size>::TempVec(int x, int y, int z)
{
	this->coordinates_[0] = x;
	this->coordinates_[1] = y;
	this->coordinates_[2] = z;
}
//***********************************************************************
//* Operator overload for addition ("+")
//***********************************************************************
template <class T, int size>
TempVec<T, size> TempVec<T, size>::operator+(const TempVec<T, size>& rhs) 
{
	TempVec<T, size> temp;
	int i = 0;
	while (i < size)
	{
		temp.coordinates_[i] = coordinates_[i] + rhs.coordinates_[i];
		i++;
	}
	return temp;
}

//***********************************************************************
//* Operator overload for subtraction ("-")
//***********************************************************************
template <class T, int size>
TempVec<T, size> TempVec<T, size>::operator-(const TempVec<T, size>& rhs)
{
	TempVec<T, size> temp;
	int i = 0;
	while (i < size)
	{
		temp.coordinates_[i] = coordinates_[i] - rhs.coordinates_[i];
		i++;
	}
	return temp;
}

//***********************************************************************
//* Operator overload for multiplication ("*")
//***********************************************************************
template <class T, int size>
TempVec<T, size> TempVec<T, size>::operator*(const TempVec<T, size>& rhs)
{
	TempVec<T, size> temp;
	int i = 0;
	while (i < size)
	{
		temp.coordinates_[i] = coordinates_[i] * rhs.coordinates_[i];
		i++;
	}
	return temp;
}

//***********************************************************************
//* print()
//* Method for printing 
//* Parameters: None
//* Returns VOID
//***********************************************************************
template <class T, int size>
void TempVec<T, size>::print()
{
	int i = 0;
	while (i < size)
	{
		cout << coordinates_[i] << endl;
		i++;
	}
}

//***********************************************************************
//* print()
//* Method for printing 
//* Parameters: None
//* Returns VOID
//***********************************************************************
template <class T, int size>
void TempVec<T, size>::addVectors(T vec1, T vec2)
{

}




/*
namespace vectorFunctions
{
	int InnerProduct(T* u, T* v)
	{
		for (int i = 0; i < 3 ;i++)
	}
}
*/

#endif
