/* int_util.c */
#include "int_util.h" /* Why ?? */
int last_error; /* definition of global variable */
				/* implementation of swap_int function */
void swap_int(int* ip1, int* ip2)
{
	int tmp;
	if (ip1 == NULL || ip2 == NULL) {
		last_error = NULL_POINTER;
		return;
	}
	last_error = NO_ERROR;
	tmp = *ip1;
	*ip1 = *ip2;
	*ip2 = tmp;
	return;
}

/* implementation of max2_int function */
int max2_int(int i1, int i2)
{
	int tmp = (i1 > i2) ? i1 : i2;
	last_error = NO_ERROR;
	return tmp;
}
/* implementation of max3_int function */
int max3_int(int i1, int i2, int i3)
{
	return max2_int(i1, max2_int(i2, i3));
}
/* implementation of min2_int function */
int min2_int(int i1, int i2)
{
	return (i1 + i2 - max2_int(i1, i2));
}