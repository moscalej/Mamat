#ifndef _TEMPVEC_H
#define _TEMPVEC_H

#include <iostream>


enum Result { FAILURE, SUCCESS };

using namespace std;


template <class T, int size>
class TempVec {

public:
	//Default Constructor
	TempVec() {};
	//TempVec(complex x, complex z);
	
	TempVec& operator=(const T rhs)
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
	friend std::ostream& operator<<(std::ostream& lhs, const TempVec<T,size>& rhs) /// <----need to be review
	{
		rhs.print();
		return lhs;
	}
	TempVec operator*(T rhs);
	//TempVec operator*(int rhs);
	T& operator[](int rhs);
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
	Result SetCoordinate(T num);
	T GetCoordinate(int num);

	
	//***********************************************************************
	//* InnerProduct()
	//* Exterior function for getting the Inner Product of two vectors
	//* Parameters: TempVec vec1, TempVec vec2
	//* Returns int
	//***********************************************************************
	friend T InnerProduct(TempVec<T, size> , TempVec<T, size>) ;
	friend T SqDistance(TempVec<T, size> , TempVec<T, size> );
	friend T SqNorm(TempVec<T, size> );
	
	//***********************************************************************
	//* print()
	//* Method for printing
	//* Parameters: const
	//* Returns VOID
	//***********************************************************************
	void print() const
	{
		int i = 0;
		cout << "(";
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
	
	int count_;
	int index_;
	T coordinates_[size];
	//T* p_coordinates_ = coordinates_;
};

// Default Constructor with exception handling
/*
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

*/

// Constructor... (DOON'T NEED. Was used for early stage testing)
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
//* Operator overload for multiplication ("*") rhs = T, lhs = TempVec
//***********************************************************************
template <class T, int size>
TempVec<T, size> TempVec<T, size>::operator*(T rhs)
{
	TempVec<T, size> temp;
	int i = 0;
	while (i < size)
	{
		temp.coordinates_[i] = coordinates_[i] * rhs;
		i++;
	}
	return temp;
}

//***********************************************************************
//* Operator overload for access ("[]") rhs = T
//***********************************************************************
template <class T, int size>
T& TempVec<T, size>::operator[](int rhs)
{
	try {
		if (rhs > 2 && sizeof(T) == sizeof(int)) throw "Error TempVec. Illegal index";
		if (rhs > 1 && sizeof(T) == sizeof(complex)) throw 2;
		
	}
	catch (const char* errMessage) {
		cout << errMessage << endl;
		
		rhs = rhs - 1; // bringing the index back in bounds.
		//return NULL;//this->coordinates_[rhs];
	}
	catch (const int num) {
		cout << "Error TempVec. Illegal index" << endl;

		rhs = num; // dumping tthe out of bounds values in the extra template array spot;
	}
	//this->index_ = rhs;
	return this->coordinates_[rhs] ;
}

//***********************************************************************
//* SetVector() DON'T NEED
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
//* SetCoordinate() 
//* Method for initializing a vectors coordinates
//* Parameters: string Nth
//* Returns VOID
//***********************************************************************
template <class T, int size>
Result TempVec<T, size>::SetCoordinate(T num)
{
	try
	{
		if (index_ > 2) throw "Error TempVec. Illegal index";
		
		if (index_ == 0)
		{
			this->coordinates_[0] = num;
			index_++;
			return SUCCESS;
		}
		if (index_ == 1)
		{
			this->coordinates_[1] = num;
		
			return SUCCESS;
		}
		if (index_ == 2)
		{
			this->coordinates_[2] = num;
			
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

#endif
