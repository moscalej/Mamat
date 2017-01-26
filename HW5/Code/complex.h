#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <iostream>
#include <string>


class complex  {
public:
	complex()
	{
		re_ = 0;
		im_ = 0;
	}
	complex(int real, int imaginary);
	~complex() {};
	//view funtions
	int real() const;
	int imag() const;

	// Operator Overloaders '+', '*' , '-' , '='
	complex operator+(const complex& rhs) const;
	complex operator*(const complex& rhs) const;
	complex operator*(const int& rhs) const;
	complex operator-(const complex& rhs) const;

	complex conj(const complex z);


	friend ostream & operator<<(ostream & os, const complex & rsh);

	//complex operator*(T rhs);
	//complex operator[](T rhs);




 protected:
  int re_;
  int im_;
};


#endif
