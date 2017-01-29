#ifndef _COMPLEX_H
#define _COMPLEX_H

#include "TempVec.h"
#include <iostream>
#include <string>



class complex  
{

public:
	complex()
	{
		re_ = 0;
		im_ = 0;
	}
	complex(int real, int imaginary);
	complex(int real)
	{ 
		this->re_ = real;
		this->im_ = 0;
	}
	~complex() {};
	//view funtions
	int real() const;
	int imag() const;

	// Operator Overloaders '+', '*' , '-' , '='
	complex operator+(const complex& rhs) const;
	complex operator*(const complex& rhs) const;
	complex operator*(const int& rhs) const;
	complex operator-(const complex& rhs) const;


	//friend funtions that can manipulate the complex
	friend complex conj(const complex z);
	//friend complex InnerProduct( TempVec<complex, 2>,  TempVec<complex, 2>) ;
	friend std::ostream& operator<<(std::ostream & os, const complex & rsh);
	friend complex operator*(const int lhs_constant , const complex rhs_vector);


 protected:
  int re_;
  int im_;
};

//complex SqNorm(TempVec<complex, 2> );
//complex SqDistance(TempVec<complex, 2> , TempVec<complex, 2> );
//complex InnerProduct(TempVec<complex, 2>, TempVec<complex, 2>);
#endif
