#ifndef _COMPLEX_H
#define _COMPLEX_H

#include <iostream>

class complex  {
public:
	complex()
	{
		re_ = 0;
		im_ = 0;
	}
	~complex();
 protected:
  int re_;
  int im_;
};

complex::~complex()
{
	//delete re_;
	//delete im_;
}
#endif
