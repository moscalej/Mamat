#include "polynom.h"

using namespace std;

//Constructor??
polynom::polynom(int n_, int* coefs_)
{
	
	for (int i = 0; i < n_; i++)
	{
		this->SetNum(coefs_[i]);
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
	int* temp = new int[*this->coefs_];
	for (int i = 0; i < this->n_; i++)
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
	int *prod = new int[m + n - 1];

	// Initialize the polynomial
	for (int i = 0; i < m + n - 1; i++)
	{
		prod[i] = 0;
	}

	// Multiply two polynomials term by term

	for (int i = 0; i<m; i++)
	{
		// Multiply the current term of first polynomial
		// with every term of second polynomial.
		for (int j = 0; j<n; j++)
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
	int* integral_temp = new int[m + 1];

	// Initializing the integrated polynomial
	for (int i = 0; i < m + 1; i++)
	{
		integral_temp[i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		integral_temp[i] = A[i] / (m + 1 - i);
	}
	integral_temp[m] = 1;

	return integral_temp;
}

//***********************************************************************
//* Operator overload for addition "+"
//***********************************************************************
polynom polynom::operator+(const polynom & rhs) const
{
	polynom temp;
	//int Order1 = rhs.GetOrder;
	//int Order2 = this->GetOrder;
	int OrderDiff = abs(rhs.n_ - this->n_);
	int j = -1;
	if (this->n_ > rhs.n_)
	{
		temp.n_ = this->n_;
		j = this->n_;
	}
	else temp.n_ = rhs.n_;
	
	if (j == -1) // This means order of rhs is larger than order of lhs.
	{			 // When this happens we must be careful to no try to access
				 // An order of lhs that doesn't exist!
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[i] = rhs.coefs_[i];
		}
		for (i = OrderDiff; i < rhs.n_; i++)
		{
			temp.coefs_[i] = rhs.coefs_[i] + this->coefs_[i - OrderDiff];
		}
	}
	else // The opposite is true here.
	{
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[i] = this->coefs_[i];
		}
		for (i = OrderDiff; i < this->n_; i++)
		{
			temp.coefs_[i] = this->coefs_[i] + rhs.coefs_[i - OrderDiff];
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
	
	polynom* temp = new polynom(Order1+Order2,0);
	int* productPoly = MultiplyPolynoms(Coefs1, Coefs2, Order1, Order2);

	for (int i = 0; i < Order1 + Order2; i++)
	{
		temp->coefs_[i] = productPoly[i];
	}
	
	return *temp;
}

//***********************************************************************
//* Operator overload for multiplication "*"
//***********************************************************************
polynom polynom::operator*(const int & rhs) const
{
	polynom temp;
	
	for (int i = 0; i < this->n_; i++)
	{
		temp.coefs_[i] = temp.coefs_[i] * rhs;
	}

	return temp;
}

//***********************************************************************
//* Operator overload for subtraction "-"
//***********************************************************************
polynom polynom::operator-(const polynom & rhs) const
{
	polynom temp;
	//int Order1 = rhs.GetOrder;
	//int Order2 = this->GetOrder;
	int OrderDiff = abs(rhs.n_ - this->n_);
	int j = -1;
	if (this->n_ > rhs.n_)
	{
		temp.n_ = this->n_;
		j = this->n_;
	}
	else temp.n_ = rhs.n_;

	if (j == -1) // This means order of rhs is larger than order of lhs.
	{			 // When this happens we must be careful to no try to access
				 // An order of lhs that doesn't exist!
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[i] = -(rhs.coefs_[i]);
		}
		for (i = OrderDiff; i < rhs.n_; i++)
		{
			temp.coefs_[i] = this->coefs_[i - OrderDiff] - rhs.coefs_[i];
		}
	}
	else // The opposite is true here.
	{
		int i;
		for (i = 0; i < OrderDiff; i++)
		{
			temp.coefs_[i] = (this->coefs_[i]);
		}
		for (i = OrderDiff; i < this->n_; i++)
		{
			temp.coefs_[i] = this->coefs_[i] - rhs.coefs_[i - OrderDiff];
		}
	}

	return temp;
}

//***********************************************************************
//* Operator overload for brackets "[]"
//***********************************************************************
polynom polynom::operator[](const int rhs)
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

//***********************************************************************
//* InnerProduct( )
//* Exterior function for getting the Inner Product of two polynomials
//* Parameters: polynom poly1, polynom poly2
//* Returns int
//***********************************************************************
int InnerProduct(polynom poly1, polynom poly2)
{
	int Order = poly1.GetOrder()*poly2.GetOrder();
	int* product = MultiplyPolynoms(poly1.GetCoefs(), poly2.GetCoefs(), poly1.GetOrder(), poly2.GetOrder());
	int* integral = IntegratePolynom(product, Order);
	int innerProduct_is = 0;
	for (int i = 0; i < Order; i++)
	{
		innerProduct_is += integral[i];
	}

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
	return sqrt(SqNorm(poly1 - poly2));
}




