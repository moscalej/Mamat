#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "airport.h"
#define MAX_LINE_SIZE (256)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


// A function to check the action type of our input 
Result Command(char input[]) {
	if ((input == "Insert" || input == "Remove" || input == "Add" || input == "Depart" ||
		input == "Storm" || input == "Print" || input == "Exit") != 1) return FAILURE;
	else return SUCCESS;
}
// A function to count the number of input arguments
int Number_of_Inputs(char input[])
{
	int count = 0, i, len;
	char lastC;
	len = strlen(input);
	if (len > 0)
	{
		lastC = input[0];
	}
	for (i = 0; i <= len; i++)
	{
		if ((input[i] == ' ' || input[i] == '\0') && lastC != ' ')
		{
			count++;
		}
		lastC = input[i];
	}
	return count;
}
FlightType isI_or_D(char input) 
{
	if (input == 'I') return INTERNATIONAL;
	else return DOMESTIC;
}
BOOL isE_or_R(char input)
{
	if (input == 'E') return TRUE;
	else return FALSE;
}
// A function to check that our destination is of the correct format
Result allCapsThree(char input[]) 
{
	if (input[3] != '\0') return FAILURE;
	else if ((input[0] <= 'Z' && input[0] >= 'A') &&
		(input[1] <= 'Z' && input[1] >= 'A') &&
		(input[0] <= 'Z' && input[0] >= 'A')) return SUCCESS;
	else return FAILURE;
}

int main(char* argv[])
{
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* commandType;
	char* first;
	char* second;
	char* third;//destination only
	char* fourth;//emergency only
	int runwayNumber;
	int flightNumber;
	FILE *fp;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Error: Can't open %s\n", argv[1]);
		exit(1);
	}
	while (fgets(szLine, MAX_LINE_SIZE, argv[0]))
	{
		commandType = strtok(szLine, delimiters);
		if (Command(commandType) == FAILURE) 
		{
			fprintf(stderr, "Command not found.\n");
			continue;
		}
		else if (strcmp(*commandType, "Insert") == 0)
		{ // We recieved an "Insert" command
			first = strtok(szLine, delimiters);
			second = strtok(szLine, delimiters);
			runwayNumber = atoi(first);
			if (Number_of_Inputs(szLine[MAX_LINE_SIZE]) < 3)
			{
				fprintf(stderr, "Insert failed: not enough parameters.\n");
			}
			else if ((runwayNumber > MAX_ID || runwayNumber < 1) || (second != 'I' || second != 'D')) 
			{
				printf("Insert execution failed.\n");
			}
			else 
			{
				Result j = addRunway(runwayNumber, second);
				if (j == FAILURE) printf("Insert execution failed.\n");
				else continue;
			}
		}
		else if (strcmp(*commandType, "Remove") == 0) 
		{ // We recieved a "Remove" command
			first = strtok(szLine, delimiters);
			runwayNumber = atoi(first);

			if (Number_of_Inputs(szLine[MAX_LINE_SIZE]) < 2) 
			{
				fprintf(stderr, "Remove failed: not enough parameters.\n");
			}
			else if (runwayNumber > MAX_ID || runwayNumber < 1) 
			{
				fprintf(stderr, "Remove execution failed.\n");
			}
			else {
				Result j = removeRunway(runwayNumber);
				if (j == FAILURE) printf("Remove execution failed.\n");
				else continue;
			}
		}
		else if (strcmp(*commandType, "Add") == 0) 
		{ // We recieved an "Add" command
			first = strtok(szLine, delimiters);
			second = strtok(szLine, delimiters);
			third = strtok(szLine, delimiters);
			fourth = strtok(szLine, delimiters);
			flightNumber = atoi(first);
			if (Number_of_Inputs(szLine[MAX_LINE_SIZE]) < 5) 
			{
				fprintf(stderr, "Add failed: not enough parameters.\n");
			}
			else if ((flightNumber > MAX_ID || flightNumber < 1) ||
				(second != 'I' || second != 'D') ||
				allCapsThree(third == FAILURE) ||
				(fourth != 'E' || fourth != 'R'))

				fprintf(stderr, "Add execution failed.\n");
			else 
			{
				Result j = addFlightToAirport(flightNumber, isI_or_D(second), third, isE_or_R(fourth));
				if (j == FAILURE) printf("Add execution failed.\n");
				else continue;
			}
		}


		else if (strcmp(*commandType, "Depart") == 0)
		{ // We recieved a "Depart" command
			first = strtok(szLine, delimiters);
			runwayNumber = atoi(first);
			if (Number_of_Inputs(szLine[MAX_LINE_SIZE]) < 2) 
			{
				fprintf(stderr, "Depart failed: not enough parameters.\n");
			}
			else if (runwayNumber > MAX_ID || runwayNumber < 1) {
				fprintf(stderr, "Depart execution failed.\n");
			}
			else 
			{
				Result j = departFromRunway(runwayNumber);
				if (j == FAILURE) printf("Depart execution failed.\n");
				continue;
			}
		}
		else if (strcmp(*commandType, "Storm") == 0) 
		{ // We recieved a "Storm" command
			first = strtok(szLine, delimiters);
			if (Number_of_Inputs(szLine[MAX_LINE_SIZE]) < 2) 
			{
				fprintf(stderr, "Storm failed: not enough parameters.\n");
			}
			else if (allCapsThree(first) == FAILURE) {
				fprintf(stderr, "Storm execution failed.\n");
			}
			else stormAlert(first);
			continue;
		}
		else if (strcmp(*commandType, "Print") == 0) 
		{ // We recieved a "Print" command
			printAirport();
			continue;
		}
		else	destroyAirport(); // The only possible command left is Exit
	}
	return 0;
}

