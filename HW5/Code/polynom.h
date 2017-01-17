#ifndef _POLY_F
#define _POLY_F
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;


class polynom  {
 public:
  polynom(int n=0, int* coefs=NULL);
 protected:
  int n_;
  int* coefs_;
};

#endif
 
