/*
    File: ws5.c

    Abstract:

        This small program reads up to maxSize values from the input file,
		pushes them into a stack and then prints them in a reverse order.
        But it doesnt work properly.
        Try to fix it...
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void PrintLine(int elNum, int elVal); 

int main(int argc, char* argv[]) 
{
	FILE *fp;
	int* pStack;
	int maxSize;
	int top = 0;
	int elNum;
	int lineNum;

	// Check number of arguments
	if (argc != 3)
	{
		printf("Usage: %s <stack size> <file name>\n", argv[0]);
		exit(1);
	}

	// Open input file
	fp = fopen(argv[1], "r");
	if (fp = NULL)
	{
		printf("Error: Can't open %s\n", argv[1]);
		exit(1);
	}

	maxSize = atoi(argv[2]);

	// Allocate memory for the stack
	pStack = (int*)malloc(maxSize * sizeof(int));
	if (pStack == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}

	// Push input values to the stack
	for (lineNum = 0; lineNum < maxSize; lineNum++)
	{
		if (!feof(fp))
		{
			fscanf(fp, "%d", &pStack[top]);
			top++;
		}
		else
		{
			break;
		}
	}

	// Print stack contents (input values in reverse order)
	elNum = 0;
	while (--top >= 0)
	{
		PrintLine(elNum, pStack[top-1]);
		elNum++;
	}

	fclose(fp);

	return 0;
}

void PrintLine(int elNum, int elVal)
{
	printf("Element %d is %d\n", elNum, elVal);
}
