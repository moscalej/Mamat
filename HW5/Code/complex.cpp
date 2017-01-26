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

complex complex::conj(const complex z)
{
	complex temp;
	temp.im_ = -1 * z.imag();
	temp.re_ = z.real();
	return complex();
}

ostream & operator<<(ostream & os, const complex & rsh)
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
