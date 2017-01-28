#ifndef _POLY_F
#define _POLY_F
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;


class polynom  {
 public:
  polynom();
  polynom(int n_, int* coefs_);


  // Copy Constructor
  polynom(const polynom &poly)
  {
	  n_ = poly.n_;
	  if (poly.coefs_ == NULL)
	  {
		  this->coefs_ = NULL;
	  }
	  else
	  {
		  this->coefs_ = new int[(poly.n_) + 1];
		  for (int i = 0; i < n_ + 1; i++)
		  {
			  coefs_[i] = poly.coefs_[i];

		  }
	  }
  }

  // Destructor
  ~polynom()
  {
	  if (this->coefs_ != NULL)
	  delete[] this->coefs_;

	  this->coefs_ = NULL;
  }

  // Operator Overloaders '+', '*' , '-' , '='
  polynom& operator=(const polynom& rhs)
  {
	  if (this != &rhs)

	  {
		  if (this->coefs_ != NULL)
		  {
			  delete[] this->coefs_;
			  this->coefs_ = NULL;
		  }
		  this->coefs_ = new int[(rhs.n_) + 1];
		  this->n_ = rhs.n_;
		  for (int i = 0; i < n_+1; i++)
		  {
			  this->coefs_[i] = rhs.coefs_[i];
		  }
	  }
	  return *this;
  }
  polynom operator+(const polynom& rhs) const;
  polynom operator*(const polynom& rhs) const;
  polynom operator*(const int& rhs) const;
  polynom operator-(const polynom& rhs) const;
  int& operator[](const int rhs);
  friend std::ostream& operator<<(std::ostream & os, const polynom & rhs);
  friend polynom operator*(const int lhs, const polynom& rhs)
  {
	  
	  polynom temp;		
	  int i = 0;
	  while (i < rhs.n_)
	  {
		  temp.coefs_[i] = rhs.coefs_[i] * lhs; // right
		  i++;
	  }
	  return temp;
  }

  // Methods
  int GetOrder();
  int* GetCoefs();
  void SetNum(int num);
  friend int* MultiplyPolynoms(int* A, int* B, int m, int n); // this funtion alocates memory !!!!
  void print() const
  {
	  int i = n_;
	
	  while (i >= 0)
	  {
		  if (i == n_)
		  {
			  if (i == 1)
			  {
				  cout << coefs_[i] << "x";
				  i--;
				  continue;
			  }
			  if (i == 0)
			  {
				  cout << coefs_[0];				  
				  i--;
				  break;
			  }
			  else
			  {
				  cout << coefs_[i] << "x^" << i;
				  i--;
				  continue;
			  }
		  }
		  if (coefs_[i] == 0)
		  {
			  i--;
			  continue;
		  }
		  if (i == 0)
		  {
			  if (coefs_[0] < 0) cout << coefs_[0];
			  else cout << "+" << coefs_[0];
			  i--;
			  break;
		  }
		  else
		  {
			  
			  if (i == 1)
			  {
				  if (coefs_[i] < 0)
				  {
					  cout << coefs_[i] << "x";
					  i--;
					  continue;
				  }
				  else
				  {
					  cout << "+" << coefs_[i] << "x";
				  }
			  }
			  else if (coefs_[i] < 0)
			  {
				  cout << coefs_[i];
			  }
			  else cout << "+" << coefs_[i];
				  cout << "x^" << i ;
			  i--;
			  continue;
		  }
	  }
  }

  // Calculations
  friend int InnerProduct(polynom poly1, polynom poly2);
  friend int SqNorm(polynom poly1);
  friend int SqDistance(polynom poly1, polynom poly2);

 protected:
  int n_;
  int* coefs_;
};

#endif
 
