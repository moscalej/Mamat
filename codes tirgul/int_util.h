/* int_util.h */
/* To prevent more than 1 declaration in a single file */
#ifndef _INT_UTIL_H_
#define _INT_UTIL_H_
/* declaration of a global variable - not recommended*/
extern int last_error;
/* definition of few constants to be used with last_error */
#define NO_ERROR 0
#define NULL_POINTER -1

/* declaration of the functions */
void swap_int( int* , int* );
int max2_int( int , int );
int max3_int( int i1 , int i2 , int i3);
int min2_int( int i1 , int i2);
#endif
