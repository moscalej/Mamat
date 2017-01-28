#ifndef _POLY_F
#define _POLY_F
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;


class polynom  {
 public:
	 polynom(int n = 0, int* coefs = NULL);
  //polynom(int n_, int* coefs_);
  // Copy Constructor
  polynom(const polynom &poly)
  {
	  coefs_ = new int(*poly.coefs_);
	  n_ = poly.n_;
  }

  // Destructor
  ~polynom()
  {
	  delete[] coefs_;
  }

  // Operator Overloaders '+', '*' , '-' , '='
  polynom& operator=(const polynom& rhs)
  {
	  if (this != &rhs)
	  {
		  n_ = rhs.n_;
		  if (coefs_) delete[] coefs_;
		  coefs_ = new int(*rhs.coefs_);
	  }
	  return *this;
  }
  polynom operator+(const polynom& rhs) const;
  polynom operator*(const polynom& rhs) const;
  polynom operator*(const int& rhs) const;
  polynom operator-(const polynom& rhs) const;
  polynom operator[](const int rhs);
  friend std::ostream& operator<<(std::ostream & os, const polynom & rhs);
  friend polynom operator*(const int lhs_constant, const polynom rhs_vector);

  // Methods
  int GetOrder();
  int* GetCoefs();
  void SetNum(int num);
  //int* MultiplyPolynoms(int* A, int* B, int m, int n);
  void print() const
  {
	  int i = 0;
	  cout << "v is " << "(";
	  while (i < n_)
	  {
		  if (i == n_ - 1)
		  {
			  cout << coefs_[i];
			  i++;
		  }
		  else
		  {
			  cout << coefs_[i] << "+";
			  i++;
		  }
	  }
	  cout << endl;
  }

  // Calculations
  friend int InnerProduct(polynom poly1, polynom poly2);
  friend int SqNorm(polynom poly1);
  int SqDistance(polynom poly1, polynom poly2);

 protected:
  int n_;
  int* coefs_;
};

#endif
 
