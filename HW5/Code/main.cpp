#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC



#include <iostream>
#include <cstdlib>
#include <cstring>
#include "polynom.h"
#include "complex.h"
#include "TempVec.h"


#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


using namespace std;

const int MAXLINE = 256;

typedef enum {NONE, poly, integer3, complex2} VectorSpaceType;
typedef TempVec<int,3> Integer3;
typedef TempVec<complex,2> Complex2;
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  int size=0;
  VectorSpaceType type = NONE;
  Integer3* int3_list=NULL;
  Complex2* complex2_list=NULL;
  polynom* polynom_list=NULL;
  char param_name[MAXLINE], param_value[MAXLINE];
  char* token;
  int Count=-1;
  int Coordinate=0;
  Complex2 v,u;
 
  while(!cin.eof()) {
    cin>>param_name>>param_value;
    if (!strcmp(param_name, "//")) {
      continue;
    }
    if (!strcmp(param_name, "VectorSpace_TYPE")) {
      if (!strcmp(param_value, "Polynomials")) {
	type = poly;
      }
      else if (!strcmp(param_value, "TripleInteger")) {
	type = integer3;
      }
      else if (!strcmp(param_value, "CoupleComplex")) {
	type = complex2;
      }
     
    }
    
    if (!strcmp(param_name, "Size")) {
      size = atoi(param_value);
     
      switch(type) {
      case poly:
	polynom_list = new polynom[size];
	break;
      case integer3:
	int3_list = new Integer3[size];
	break;
      case complex2:
	complex2_list = new Complex2[size];
	break;
      default:
	break;
      }
      
    }
    if (!strcmp(param_name, "SetPolynom")) {
      int order;
      int* coefs;
      Count++;
      token = strtok(param_value, ",");
      order = atoi(token);
      token = strtok(NULL, ",");
      coefs= new int[order+1];
      for  (int i=0; i<=order && token; i++) {
	coefs[i] = atof(token);
	token = strtok(NULL, ",");
      }
      polynom_list[Count] = polynom(order,coefs);
      //Finished settting a vector which is a polynomial
      delete [] coefs;
    }
    if (!strcmp(param_name, "SetVector")) {
      Coordinate=0;
      Count++;
    }
    if (!strcmp(param_name, "SetCoordinate")) {
      try{
	if(type==integer3){
	  int x;
	  x = atoi(param_value);
	  int3_list[Count][Coordinate] = x;
	  Coordinate++;
	  // Finished setting a vector of 3 integers
	}
	else if(type==complex2){
	  int re;
	  int im;
	  token = strtok(param_value, ",");
	  re = atoi(token);
	  token = strtok(NULL, ",");
	  im = atoi(token);
	  complex2_list[Count][Coordinate] = complex(re,im);
	  Coordinate++;
	  //Finished setting a vector of 2 complex numbers
	}
      }
      catch(string str){
	cout << "Error main: " << str << endl;
      }
      catch(...) {
	cout << "Unknown error:" << endl;
      }
    }
    // Commands that perform operations on the vectors
  
    if (!strcmp(param_name, "Print")) {
      for(int i=0; i<size; i++){
	cout << "V"<<i<<" is ";
	if(type==poly)
	  cout << polynom_list[i] << endl;
	else if(type==integer3)
	  cout <<int3_list[i] << endl ;
	else 
	  cout << complex2_list[i] << endl;
      }
    }
   
    if (!strcmp(param_name, "Add")||!strcmp(param_name, "Substract")) {
      char Op= (!strcmp(param_name, "Add"))? '+':'-';
      int lhs,rhs;
      token = strtok(param_value, ",");
      lhs = atoi(token);
      token = strtok(NULL, ",");
      rhs = atoi(token);
      cout << "V"<<lhs<<Op<<"V"<<rhs<<" is ";
      if(!strcmp(param_name, "Add")){
	if(type==poly)
	  cout << polynom_list[lhs]+polynom_list[rhs] << endl;
	else if(type==integer3)
	  cout << int3_list[lhs]+int3_list[rhs] << endl;
	else 
	  cout << complex2_list[lhs]+complex2_list[rhs] << endl;
      }
      else {
	if(type==poly)
	  cout << polynom_list[lhs]-polynom_list[rhs] << endl;
	else if(type==integer3)
	  cout << int3_list[lhs]-int3_list[rhs] << endl;
	else 
	  cout << complex2_list[lhs]-complex2_list[rhs] << endl;
      }
    }
    if (!strcmp(param_name, "ScalarMult")) {
      if(type==integer3 || type == poly){ //Scalar is integer
	int x;
	x = atoi(param_value);
	for(int i=0; i<size; i++){
	  if(type==integer3) 
	    cout <<"("<<x<<")"<<"*V"<<i<<" is "<<x*int3_list[i]<<endl;
	  else
	    cout <<"("<< x<<")"<<"*V"<<i<<" is "<<x*polynom_list[i]<<endl;
	}
      }
      else if(type==complex2){ //Scalar is complex
	int re;
	int im;
      	token = strtok(param_value, ",");
	re = atoi(token);
	token = strtok(NULL, ",");
	im = atoi(token);
	complex x(re,im);
	for(int i=0; i<size; i++){
	  cout <<"("<< x<<")"<<"*V"<<i<<" is "<<x*complex2_list[i]<<endl;
	  
	}
      }
    }
    if (!strcmp(param_name, "InnerProduct")) {
      int lhs,rhs;
      token = strtok(param_value, ",");
      lhs = atoi(token);
      token = strtok(NULL, ",");
      rhs = atoi(token);
      cout << "<V"<<lhs<<",V"<<rhs<<"> is ";
      if(type==poly)
	cout << InnerProduct(polynom_list[lhs],polynom_list[rhs]) << endl;
      else if(type==integer3)
	cout << InnerProduct(int3_list[lhs],int3_list[rhs]) << endl;
      else 
	cout << InnerProduct(complex2_list[lhs],complex2_list[rhs]) << endl;
      
    }
    if (!strcmp(param_name, "SquaredNorm")) {
      int vec;
      token = strtok(param_value, ",");
      vec = atoi(token);
      cout << "||V"<<vec<<"||^2"<<" is ";
      if(type==poly)
	cout << SqNorm(polynom_list[vec]) << endl;
      else if(type==integer3)
	cout << SqNorm(int3_list[vec]) << endl;
      else 
	cout << SqNorm(complex2_list[vec]) << endl;
    }
    if (!strcmp(param_name, "SquaredDistance")) {
      int lhs,rhs;
      token = strtok(param_value, ",");
      lhs = atoi(token);
      token = strtok(NULL, ",");
      rhs = atoi(token);
      cout << "d^2(V"<<lhs<<",V"<<rhs<<") is ";
      if(type==poly)
	cout << SqDistance(polynom_list[lhs],polynom_list[rhs]) << endl;
      else if(type==integer3)
	cout << SqDistance(int3_list[lhs],int3_list[rhs]) << endl;
      else 
	cout << SqDistance(complex2_list[lhs],complex2_list[rhs]) << endl;
    }
  }
  
  if(polynom_list) delete[] polynom_list ;
  if(int3_list) delete[] int3_list;
  if(complex2_list) delete[] complex2_list;
  _CrtDumpMemoryLeaks();
  return 0;
}
