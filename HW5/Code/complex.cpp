

#include "complex.h"

using namespace std;

complex::complex(int real, int imaginary)
{
	this->im_ = imaginary;
	this->re_ = real;
}

int complex::real() const
{
	return this->re_;
}

int complex::imag() const
{
	return this->im_;
}

complex complex::operator+(const complex & rhs) const
{
	complex temp;
	temp.re_ = this->re_ + rhs.re_;
	temp.im_ = this->im_ + rhs.im_;

	return temp;
}

complex complex::operator*(const complex & rhs) const
{
	complex temp;
	temp.re_ = (this->re_ * rhs.re_ )- (this->im_ * rhs.im_);
	temp.im_ = (this->im_ * rhs.re_ )+ (this->re_ * rhs.im_);
	return temp;
}

complex complex::operator*(const int & rhs) const
{
	complex temp;
	temp.re_ = this->re_ *rhs;
	temp.im_ = this->im_ *rhs;

	return temp;
}

complex complex::operator-(const complex & rhs) const
{
	complex temp;
	temp.re_ = this->re_ - rhs.re_;
	temp.im_ = this->im_ - rhs.im_;

	return temp;
}

complex conj(const complex z)
{
	complex temp;
	temp.im_ = -1 * z.imag();
	temp.re_ = z.real();
	return temp;
}


std::ostream & operator<<(std::ostream & os, const complex & rsh) 
{
	string temp;
	if (rsh.real()==0)
	{

		if (rsh.imag() == 0)
		{
			temp = "0";

		}
		else
		{
			temp = rsh.imag();
		}

	}
	else
	{
		if (rsh.imag() == 0)
		{
			temp = rsh.real();
		}
		else
		{
			temp = rsh.real() + " " + rsh.imag();
		}
	}
	return os << temp << endl;
}

complex operator*(const int lhs,const complex rhs)
{
	complex temp;
	temp.re_ = rhs.re_ * lhs;
	temp.im_ = rhs.im_ * lhs;
	return temp;
}



//***********************************************************************
//* InnerProduct( )
//* Exterior function for getting the Inner Product of two vectors
//* Parameters: TempVec vec1, TempVec vec2
//* Returns int
//***********************************************************************

int InnerProduct(TempVec<int, 3> vect1, TempVec<int, 3> vect2)
{
	TempVec<int, 3> temp;
	temp = vect1 * vect2;
	int sum = temp.coordinates_[0] + temp.coordinates_[1] + temp.coordinates_[2];
	return sum;
}

complex InnerProduct(TempVec<complex, 2> vect1, TempVec<complex, 2> vect2)
{
	TempVec<complex, 2> temp;
	temp[0] = conj(vect2[0]);
	temp[1] = conj(vect2[1]);
	temp = temp * vect1;
	complex sum = temp.coordinates_[0] + temp.coordinates_[1] ;
	return sum;
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

	return SqNorm(vec1 - vec2);
}









/*/
complex InnerProduct(TempVec<complex, 2> vec1, TempVec<complex, 2> vec2)
{
	TempVec<complex, 2> temp;
	complex sum;
	temp[0] = conj(vec2.GetCoordinate(0));
	temp[1] = conj(vec2.GetCoordinate(1));
	temp = temp * vec1;
	sum = temp.GetCoordinate(0) + temp.GetCoordinate(1);
	return sum;
}

/*
complex SqNorm(TempVec<complex, 2> vec1)
{
	return  InnerProduct(vec1, vec1);
}


complex SqDistance(TempVec<complex, 2> vec1, TempVec<complex, 2> vec2) 
{

	return InnerProduct(vec1-vec2, vec1-vec2);
 }
 */