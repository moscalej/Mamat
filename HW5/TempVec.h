#ifndef _TEMPVEC_H
#define _TEMPVEC_H

#include <iostream>


enum Result { FAILURE, SUCCESS };

using namespace std;


template <class T, int size>
class TempVec {

public:
	//Default Constructor
	TempVec();
	
	TempVec& operator=(const T& rhs)
	{
		this->SetCoordinate(rhs);

		return *this;
	}
	// Constructor for 3D coordinates
	TempVec(int x, int y, int z);

	// Default Destructor
	virtual ~TempVec() { }


	// Operator Overloaders '+', '*' , '-' , '=', '<<', '[]'
	TempVec operator+(const TempVec& rhs);
	TempVec operator*(const TempVec& rhs);
	TempVec operator-(const TempVec& rhs);
	friend std::ostream& operator<<(std::ostream& lhs, const TempVec<T,size>& rhs)
	{
		rhs.print();
		return lhs;
	}

	TempVec operator*(T rhs);
	TempVec operator[](T rhs);
	
	friend TempVec operator* (const T lhs, const TempVec& rhs) // Allows left side multiplication (LSM).
	{								// The LSM is accomplished with the help of our right-sided
		TempVec<T, size> temp;		// multiplication (RSM) overload.
		int i = 0;
		while (i < size)
		{
			temp.coordinates_[i] = rhs.coordinates_[i] * lhs; // right
			i++;
		}
		return temp;
	}


	//Setting values.
	Result SetVector(char* Nth);
	Result SetCoordinate(int num);
	T GetCoordinate(int num);

	//Vector Math
	friend T InnerProduct(TempVec u, TempVec v);
	friend T SqNorm(TempVec u);
	friend T SqDistance(TempVec u);

	// Member methods
	void print() const
	{
		int i = 0;
		cout << "v is " << "(";
		while (i < size)
		{
			if (i == size - 1)
			{
				cout << coordinates_[i];
				i++;
			}
			else
			{
				cout << coordinates_[i] << ",";
				i++;
			}
		}
		cout << ")" ;
	}
protected:
	int count_;// To count how many vectors we have created.
	int index_;
	T coordinates_[size];
	T* p_coordinates_ = coordinates_;
};

// Default Constructor with exception handling
template <class T, int size>
TempVec<T, size>::TempVec()
{
	count_ = 0;
	index_ = 0;
	try
	{
		for (int i = 0; i < 3; i++)
		{
			if (i > 3 || i < 0) throw "Error TempVec. Illegal index";
			coordinates_[i] = 0;
		}
	}
	catch (const char* errMessage)
	{
		cerr << "Error TempVec. " << errMessage << endl;
	}
}

// Constructor...
template <class T, int size>
TempVec<T, size>::TempVec(int x, int y, int z)
{
	this->count_ = 0;
	this->index_ = 0;
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
		temp.p_coordinates_[i] = coordinates_[i] + rhs.coordinates_[i];
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
		temp.p_coordinates_[i] = coordinates_[i] - rhs.coordinates_[i];
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
		temp.p_coordinates_[i] = coordinates_[i] * rhs.coordinates_[i];
		
		i++;
	}
	return temp;
}

/*
//***********************************************************************
//* Operator overload for printing ("<<")
//***********************************************************************
template <class T, int size>
void TempVec<T, size>::operator<<(const TempVec<T, size>& rhs)
{
	rhs.print();
}*/

//***********************************************************************
//* Operator overload for multiplication ("*") rhs = T, lhs = TempVec
//***********************************************************************
template <class T, int size>
TempVec<T, size> TempVec<T, size>::operator*(T rhs)
{
	TempVec<T, size> temp;
	int i = 0;
	while (i < size)
	{
		temp.p_coordinates_[i] = coordinates_[i] * rhs;
		i++;
	}
	return temp;
}

//***********************************************************************
//* Operator overload for access ("[]") rhs = T
//***********************************************************************
template <class T, int size>
TempVec<T, size> TempVec<T, size>::operator[](T rhs)
{
	
	this->index_ = rhs;
	return *this;
}


//***********************************************************************
//* SetVector()
//* Method for initializing a vector
//* Parameters: string Nth
//* Returns VOID
//***********************************************************************
template <class T, int size>
Result TempVec<T, size>::SetVector(char* Nth)
{
	int i = Nth[0] - '0';

	if (i < 0) return FAILURE;

	this->count_ = i - 1;
	return SUCCESS;
}

//***********************************************************************
//* SetCoordinate() PROBABLY DON'T NEED
//* Method for initializing a vectors coordinates
//* Parameters: string Nth
//* Returns VOID
//***********************************************************************
template <class T, int size>
Result TempVec<T, size>::SetCoordinate(int num)
{
	try
	{
		if (index_ > 2) throw "Error TempVec. Illegal index";
		
		if (index_ == 0)
		{
			this->p_coordinates_[0] = num;
			
			return SUCCESS;
		}
		if (index_ == 1)
		{
			this->p_coordinates_[1] = num;
		
			return SUCCESS;
		}
		if (index_ == 2)
		{
			this->p_coordinates_[2] = num;
			
			return SUCCESS;
		}
	}
	catch (const char* errMessage) {
		cerr << errMessage << endl;
	}
	return FAILURE;
}

//***********************************************************************
//* GetCoordinate()
//* Method for getting a vectors coordinates
//* Parameters: int num
//* Returns T
//***********************************************************************
template <class T, int size>
T TempVec<T, size>::GetCoordinate(int num)
{
	try
	{
		if (num>2) throw "Error TempVec. Illegal index";

	}
	catch (const char* errMessage) {
		cerr << errMessage << endl;
	}
	return coordinates_[num];
}

/*
//***********************************************************************
//* print()
//* Method for printing 
//* Parameters: None
//* Returns VOID
//***********************************************************************
template <class T, int size>
void TempVec<T, size>::print() const
{
	int i = 0;
	cout << "v is " << "(";
	while (i < size)
	{
		if (i == size - 1)
		{
			cout << coordinates_[i];
			i++;
		}
		else
		{
			cout << coordinates_[i] << ",";
			i++;
		}
	}
	cout << ")" << endl;
}*/


//***********************************************************************
//* InnerProduct()
//* Exterior function for getting the Inner Product of two vectors
//* Parameters: TempVec vec1, TempVec vec2
//* Returns int
//***********************************************************************
int InnerProduct(TempVec<int, 3> vec1, TempVec<int, 3> vec2)
{
	TempVec<int, 3> temp = vec1*vec2;
	
	int theSum = 0;
	for (int i = 0; i < 3; i++) {

		theSum += temp.GetCoordinate(i);
	}
	return theSum;
}

//***********************************************************************
//* SqNorm()
//* Exterior function for getting the norma squared (||u||^2) of a vector
//* Parameters: TempVec vec1
//* Returns int
//***********************************************************************
int SqNorm(TempVec<int, 3> vec1)
{
	TempVec<int, 3> temp = vec1*vec1;
	int theSum = 0;
	for (int i = 0; i < 3; i++) {

		theSum += temp.GetCoordinate(i);
	}
	return theSum;
}

//***********************************************************************
//* SqDistance()
//* Exterior function for getting the distance between two vectors
//* Parameters: TempVec vec1 TempVec vec2
//* Returns int
//***********************************************************************
int SqDistance(TempVec<int, 3> vec1, TempVec<int, 3> vec2)
{
	//TempVec<int, 3> temp = vec1 - vec2;

	//int j = SqNorm(temp);

	return SqNorm(vec1 - vec2);
}


#endif
