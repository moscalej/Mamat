/* main.c */
#include "int_util.h"
#include <stdio.h>
void main( ) {
    int n1 = 5 ,n2 = 4, n3 = -5;
    printf("The maximum between n1,n2 and n3 is %d\n",
        max3_int(n1,n2,n3) );
    printf("The minimum between n2 and n3 is %d\n",
        min2_int(n2,n3) );
    swap_int( &n1 , &n3);
    if ( last_error != NO_ERROR ) {
        printf("Error occurred during swap_int\n");
        exit(1);
    }
    printf("After swaping , max2_int( n1,n3) = %d\n",
        max2_int(n1,n3) );
} /* end of main ( ) */
