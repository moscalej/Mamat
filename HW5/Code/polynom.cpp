#include "polynom.h"

using namespace std;

//Constructor??
polynom::polynom(int n_, int* coefs_)
{
	this->coefs_  = new int[n_+1];
	this->n_ = n_;
	for (int i = 0; i < n_+1; i++)
	{
		this->coefs_[i] = coefs_[i];
	}
	
}

//***********************************************************************
//* GetOrder( )
//* Method for getting the order of the polynomial
//* Parameters: NONE
//* Returns int
//***********************************************************************
int polynom::GetOrder()
{
	return this->n_;
}

//***********************************************************************
//* GetOrder( )
//* Method for getting the order of the polynomial
//* Parameters: NONE
//* Returns int
//***********************************************************************
int* polynom::GetCoefs()
{
	int* temp = new int[this->n_ + 1];
	for (int i = 0; i < this->n_ + 1; i++)
	{
		temp[i] = this->coefs_[i];
	}
	return temp;
}

//***********************************************************************
//* SetNum( )
//* Method for setting a value in the polynomial
//* Parameters: int num
//* Returns VOID
//***********************************************************************
void polynom::SetNum(int num)
{
	this->coefs_[this->n_] = num ;
	this->n_++;
}

//***********************************************************************
//* MultiplyPolynoms( )
//* Exterior function for multiplying polynomials
//* Parameters: int A[], int B[], int m, int n
//* Returns int[]
//***********************************************************************
int* MultiplyPolynoms(int* A, int* B, int m, int n)
{
	int *prod = new int[m + n + 1];

	// Initialize the polynomial
	for (int i = 0; i < m + n +1; i++)
	{
		prod[i] = 0;
	}

	// Multiply two polynomials term by term

	for (int i = 0; i<=m; i++)
	{
		// Multiply the current term of first polynomial
		// with every term of second polynomial.
		for (int j = 0; j<=n; j++)
			prod[i + j] += A[i] * B[j];
	}

	return prod;
}

//***********************************************************************
//* IntegratePolynom( )
//* Exterior function for integrating polynomials with indefinite bounds
//* we will sum the terms (for bounded integral) later.
//* Parameters: int A[], int B[], int m, int n
//* Returns int[]
//***********************************************************************
int* IntegratePolynom(int* A, int m)
{
	int* integral_temp = new int[m + 2];

	// Initializing the integrated polynomial
	for (int i = 0; i < m + 2; i++)
	{
		integral_temp[i] = 0;
	}
	for (int j = m+1; j > 0; j--)
	{
		/*if (A[j - 1] / (j + 1) < 0 && A[j - 1] / (j + 1) > -1)
		{
			integral_temp[j] = 0;
			//continue;
		}
		else if (A[j - 1] / (j + 1) > 0 && A[j - 1] / (j + 1) < 1)
		{
			integral_temp[j] = 1;
			//continue;
		}*/
		 integral_temp[j] = (double)A[j-1] / (double)(j+1);
	}
	integral_temp[0] = 1;

	return integral_temp;
}

polynom::polynom()
{
	this->n_ = 0;
	this->coefs_ = NULL;
}

//***********************************************************************
//* Operator overload for addition "+"
//***********************************************************************
polynom polynom::operator+(const polynom & rhs) const
{
	polynom temp;
	int OrderDiff = abs(rhs.n_ - this->n_);
	int j = -1;
	if (this->n_ > rhs.n_)
	{
		temp.n_ = this->n_;
		temp.coefs_ = new int[this->n_+1];
		j = this->n_;
	}
	else if (this->n_ == rhs.n_)
	{
		temp.n_ = this->n_;
		temp.coefs_ = new int[this->n_ + 1];
		j = -2;
	}
	else
	{
		temp.n_ = rhs.n_;
		temp.coefs_ = new int[rhs.n_+1];
	}
	
	if (j == -1) // This means order of rhs is larger than order of lhs.
	{			 // When this happens we must be careful to no try to access
				 // An order of lhs that doesn't exist!
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[rhs.n_-i] = rhs.coefs_[rhs.n_ - i];
		}
		for (i = OrderDiff; i < rhs.n_ + 1; i++)
		{
			temp.coefs_[rhs.n_ - i] = rhs.coefs_[rhs.n_ - i] + this->coefs_[this->n_ - (i - OrderDiff)];
		}
	}
	else if (j == -2)
	{
		for (int i = 0; i < rhs.n_ + 1; i++)
		{
			temp.coefs_[rhs.n_ - i] = rhs.coefs_[rhs.n_ - i] + this->coefs_[this->n_ - i];
		}
	}
	else // The opposite is true here. order lhs > order rhs
	{
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[this->n_ - i] = this->coefs_[this->n_ - i];
		}
		for (i = OrderDiff; i < this->n_ + 1; i++)
		{
			temp.coefs_[this->n_ - i] = this->coefs_[this->n_ - i] + rhs.coefs_[rhs.n_ - (i - OrderDiff)];
		}
	}

	return temp;
}

//***********************************************************************
//* Operator overload for subtraction "-"
//***********************************************************************
polynom polynom::operator-(const polynom & rhs) const
{
	polynom temp;
	
	int OrderDiff = abs(rhs.n_ - this->n_);
	int j = -1;
	if (this->n_ > rhs.n_)
	{
		temp.n_ = this->n_;
		temp.coefs_ = new int[this->n_+1];
		j = this->n_;
	}
	else if (this->n_ == rhs.n_)
	{
		temp.n_ = this->n_;
		temp.coefs_ = new int[this->n_ + 1];
		j = -2;
	}
	else
	{
		temp.n_ = rhs.n_;
		temp.coefs_ = new int[rhs.n_+1];
	}

	if (j == -1) // This means order of rhs is larger than order of lhs.
	{			 // When this happens we must be careful to no try to access
				 // An order of lhs that doesn't exist!
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[rhs.n_ - i] = 0 - (rhs.coefs_[rhs.n_ - i]);
		}
		for (i = OrderDiff; i < rhs.n_ + 1; i++)
		{
			temp.coefs_[rhs.n_ - i] = this->coefs_[this->n_ - (i - OrderDiff)] - rhs.coefs_[rhs.n_ - i];
		}
	}
	else if (j == -2)
	{
		for (int i = 0; i < rhs.n_ + 1; i++)
		{
			temp.coefs_[rhs.n_ - i] = this->coefs_[this->n_ - i] - rhs.coefs_[rhs.n_ - i];
		}
	}
	else // The opposite is true here.
	{
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[this->n_ - i] = (this->coefs_[this->n_ - i]);
		}
		for (i = OrderDiff; i < this->n_ + 1; i++)
		{
			temp.coefs_[this->n_ - i] = this->coefs_[this->n_ - i] - rhs.coefs_[rhs.n_ - (i - OrderDiff)];
		}
	}

	return temp;
}

//***********************************************************************
//* Operator overload for multiplication "*"
//***********************************************************************
polynom polynom::operator*(const polynom & rhs) const
{
	int Order1 = this->n_;
	int Order2 = rhs.n_;
	int* Coefs1 = this->coefs_;
	int* Coefs2 = rhs.coefs_;

	int i = this->n_;
	int j = rhs.n_;
	
	
	int* productPoly = MultiplyPolynoms(Coefs1, Coefs2, Order1, Order2); //alocates new memory 1

	polynom temp((this->n_ + rhs.n_), productPoly); //alocates memory2

	delete[] productPoly; // release the memory 1
	
	return temp;//relese memory 2
}

//***********************************************************************
//* Operator overload for multiplication "*"
//***********************************************************************
polynom polynom::operator*(const int & rhs) const
{
	polynom temp;
	
	for (int i = 0; i < this->n_+1; i++)
	{
		temp.coefs_[i] = temp.coefs_[i] * rhs;
	}

	return temp;
}

//***********************************************************************
//* Operator overload for brackets "[]"
//***********************************************************************
int& polynom::operator[](const int rhs)
{
	return this->coefs_[rhs];
}
//***********************************************************************
//* Operator overload for printing "<<"
//***********************************************************************
std::ostream& operator<<(std::ostream & os, const polynom & rhs)
{
	rhs.print();
	return os;
}

polynom operator*(const int lhs_constant, const polynom rhs_vector)
{
	polynom temp;
	temp = rhs_vector * lhs_constant;

	return temp;
}

//***********************************************************************
//* InnerProduct( )
//* Exterior function for getting the Inner Product of two polynomials
//* Parameters: polynom poly1, polynom poly2
//* Returns int
//***********************************************************************
int InnerProduct(polynom poly1, polynom poly2)
{
	int Order = poly1.GetOrder()+poly2.GetOrder();
	int* product = MultiplyPolynoms(poly1.GetCoefs(), poly2.GetCoefs(), poly1.GetOrder(), poly2.GetOrder());
	int* integral = IntegratePolynom(product, Order);
	int innerProduct_is = 0;
	for (int i = 0; i < Order+2; i++)
	{
		innerProduct_is += integral[i];
	}
	delete[] product;
	delete[] integral;

	return innerProduct_is;
}

//***********************************************************************
//* SqNorm()
//* Exterior function for getting the SqNorm of a polynomial
//* Parameters: polynom poly1
//* Returns int
//***********************************************************************
int SqNorm(polynom poly1)
{
	return InnerProduct(poly1, poly1);
}

//***********************************************************************
//* SqDistance()
//* Exterior function for getting the SqDistance of two polynomials
//* Parameters: polynom poly1, polynom poly2
//* Returns int
//***********************************************************************

int SqDistance(polynom poly1, polynom poly2)
{
	return SqNorm(poly1 - poly2);
}




