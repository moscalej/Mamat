#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "flight.h"
//#define MAX_LINE_SIZE 100

//static PFlightInfo ArrElements[MAX_ID] = { 0 };
//static int IndexNum = 0;

/* TO PUT IN MAIN.............
//Creating the format for our linked list
typedef struct _Linked_List_Element {
	FlightInfo TheFlight;
	int i;
	struct _Linked_List_Element* pNext;
}Linked_List_Element;
// A function to check the action type of our input (MAYBE ONLY NEED IN MAIN?)
Result Command(char input[]) {
	char* command;
	command = strtok(input, " ");
	if ((command == "Insert" || command == "Remove" || command == "Add" || command == "Depart" ||
		command == "Storm" || command == "Print" || command == "Exit") != 1) return FAILURE;
	else return SUCCESS;
}
// A function to count the number of input arguments
int Num_Of_Inputs(char input[]) {

};

//MAYBE MAKE A LEGAL INPUT FUNCTION?
Result ValidInput() {
	char Line[MAX_LINE_SIZE];
	char* delimiters = " \n";// If \n is hit how to stop and move to next line?
	char* FlightNum;
	char* FlightType;
	char* FlightDest;
	char* Emergency;
	int number;

}; */


/*Creating a flight 
this fly inteface will create parts of a data structure, will have the ability to
invoque funtions that will delete or print the information */

//the next funtions returns a pointer to the new object based on 
//the structure of flight and insertes on the node info the 
//requared fields

//"the return type" funtion name ( values )
PFlightInfo  createFlight(int Num, char Type, char Destination, char Emergency) {
	PFlightInfo pElem;  //defines pELem as a pointer to a struc object for the maloc to create a memory
	pElem = (PFlightInfo)malloc(sizeof(FlightInfo)); // Dyanmic memory allocation

	if (NULL == pElem) {
	 exit(-1); // Check to make sure legal memory was allocated
 	}
	/* - Entering the flights information - */
	pElem->Flight_Num = (FlightNum)Num;
	pElem->Flight_Type = (FlightType)Type;
	pElem->Flight_Destination = (FlightDestination)Destination;
	pElem->Emergency = (BOOL)Emergency;
	/* - - - - - - - -the link part - - - - - - - - - - */
	pElem->headNext = NULL;
	return pElem;
};

/* Destroying a flight*/
void destroyFlight(PFlightInfo flight) {
	free(flight);
};

Result printFlight(PFlightInfo flight) {
	if (flight == NULL) return FAILURE;
	else // how to print properly??
		printf("FLIGHT &d &d &d &d", flight->Flight_Num,
									 flight->Flight_Type,
									 flight->Flight_Destination,
		 							 flight->Emergency
		);
	return SUCCESS;
}
/* ALSO ADD TO MAIN....
//A searching function to scan our linked lists (mostly an example. Will fix to use on linked lists)
static int InternalFind(FlightNum Num) {
	int i;

	for (i = 0; i < MAX_ID; i++) {
		if (NULL != ArrElements[i] && Num == ArrElements[i]->Flight_Num) return i;
	}
	return -1;
}*/

// Compiler issue
