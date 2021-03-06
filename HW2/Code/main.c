
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"
#define MAX_LINE_SIZE (256)


// A function to check the action type of our input 
Result Command(char* input) {
	if (((strcmp(input, "Insert") == 0) || (strcmp(input, "Remove") == 0) || (strcmp(input, "Add") == 0) ||
		(strcmp(input, "Depart") == 0) || (strcmp(input, "Storm") == 0) ||
		(strcmp(input, "Print") == 0) || (strcmp(input, "Exit") == 0)) == 0) return FAILURE;
	else return SUCCESS;
}
// A function to count the number of input arguments
int Number_of_Inputs(char input[])
{
	//printf("***"); fprintf(stderr, input); printf("***\n");
	int count = 0, i, len;
	char lastC;
	len = strlen(input);
	//printf("len = %d", len);
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
	//printf("count is %d", count);
	return count;
}

// A function to check that our destination is of the correct format
Result allCapsThree(char input[]) {
	if (input[3] != '\0') return FAILURE;
	else if ((input[0] <= 'Z' && input[0] >= 'A') &&
		(input[1] <= 'Z' && input[1] >= 'A') &&
		(input[0] <= 'Z' && input[0] >= 'A')) return SUCCESS;
	else return FAILURE;
}

int main(int argc, char* argv[]) {
	char szLine[MAX_LINE_SIZE];
	const char* delimiters = " \t\n\r\v\f";
	char* commandType;
	char* first;
	char* second;
	char* third;//destination only
	char* fourth;//emergency only
	int inputCount;
	int runwayNumber;
	int flightNumber;
  Result yolo;
	Result result;
	FILE *fp;



	Airporthead0.RunwayList = NULL;
	Airporthead = &Airporthead0;

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	if (argc < 1)
	{
		printf("Usage: %s <stack size> <file name>\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		printf("Error: Can't open %s\n", argv[1]);
		exit(1);
	}
	while (fgets(szLine, sizeof szLine, fp))
	{

		inputCount = Number_of_Inputs(szLine);

		commandType = strtok(szLine, delimiters);

		if (Command(commandType) == FAILURE)
		{
			fprintf(stderr, "Command not found.\n");
			continue;
		}


		// We recieved an "Insert" command
		else if (strcmp(commandType, "Insert") == 0)
		{
			first = strtok(NULL, delimiters);
			//printf("First"); fprintf(stderr, first); printf("$$$\n");
			second = strtok(NULL, delimiters);
			//fprintf(stderr, second);
			//printf("!!!\n");


			if (first == NULL || second == NULL) {
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}
			runwayNumber = atoi(first);
			if (inputCount < 3) {
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				continue;
			}

			if (((runwayNumber > 1000) || (runwayNumber < 1)) || ((*second != (char)'I') && (*second != (char)'D')))
			{
				fprintf(stderr, "Insert execution failed.\n");
				continue;
			}



			else
			{


				result = addRunway(runwayNumber, *second);
				if (result == FAILURE)
				{
					fprintf(stderr, "Insert execution failed.\n");
				}
				else
				{
					continue;
				}
			}
		}

		/*this is REMOVE Comand*/
		else if (strcmp(commandType, "Remove") == 0)
		{ // We recieved a "Remove" command
			first = strtok(NULL, delimiters);
			runwayNumber = atoi(first);
			if (first == NULL) {
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				continue;
			}

			if (inputCount < 2) {
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				continue;
			}
			else if (runwayNumber > MAX_ID || runwayNumber < 1) {
				fprintf(stderr, "Remove execution failed.\n");
				continue;
			}
			else {
				Result j = removeRunway(runwayNumber);
				if (j == FAILURE) fprintf(stderr, "Remove execution failed.\n");
				else continue;
			}
		}

		/*This is Add flight Comand*/
		else if (strcmp(commandType, "Add") == 0) { // We recieved an "Add" command
			first = strtok(NULL, delimiters);
			second = strtok(NULL, delimiters);
			third = strtok(NULL, delimiters);
			fourth = strtok(NULL, delimiters);
			if (first == NULL || second == NULL || third == NULL || fourth == NULL) {
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			flightNumber = atoi(first);
			if (inputCount < 5) {
				fprintf(stderr, "Add failed: not enough parameters.\n");
				continue;
			}
			else if ((flightNumber > MAX_ID || flightNumber < 1) ||
				(*second != 'I' && *second != 'D') ||
				(allCapsThree(third) == FAILURE) ||
				(*fourth != 'E' && *fourth != 'R'))
			{
				fprintf(stderr, "Add execution failed.\n");
				continue;
			}
			else
			{
				Result j = addFlightToAirport(flightNumber, isI_or_D(*second), third, isE_or_R(*fourth));
				if (j == FAILURE)
				{
					fprintf(stderr, "Add execution failed.\n");
				}
				else continue;
			}
		}

		/*this depart comand*/
		else if (strcmp(commandType, "Depart") == 0)
		{ // We recieved a "Depart" command
			first = strtok(NULL, delimiters);
			if (first == NULL) {
				fprintf(stderr, "Depart failed: not enough parameters.\n");
				continue;
			}
			else runwayNumber = atoi(first);
			if (inputCount < 2) {
				fprintf(stderr, "Depart failed: not enough parameters.\n");
				continue;
			}

			else if (runwayNumber > MAX_ID || runwayNumber < 1) {
				fprintf(stderr, "Depart execution failed.\n");
				continue;
			}
			else {
				 yolo = departFromRunway(runwayNumber);
				if (yolo == FAILURE) fprintf(stderr, "Depart execution failed.\n");
				continue;
			}
		}

		/*storm Comand*/
		else if (strcmp(commandType, "Storm") == 0) {
			first = strtok(NULL, delimiters);
			if (inputCount < 2) {
				fprintf(stderr, "Storm failed: not enough parameters.\n");
				continue;
			}
			else if (allCapsThree(first) == FAILURE) {
				fprintf(stderr, "Storm execution failed.\n");
				continue;
			}
			else stormAlert(first);
			continue;
		}

		/*this is the Print comand*/
		else if (strcmp(commandType, "Print") == 0)
		{
			printAirport();
			fprintf(stdout, "\n");
			continue;
		}

		/* The only possible command left is Exit*/
		else {
			destroyAirport();
			break;
		}//
	}

	fclose(fp);
 return 0;
}

