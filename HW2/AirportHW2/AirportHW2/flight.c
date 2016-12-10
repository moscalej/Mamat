#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "flight.h"

/*the return type" funtion name ( values )  */
PFlightInfo  createFlight(int Num, char Type, char Destination[], char Emergency)
{
	PFlightInfo pElem;  //defines pELem as a pointer to a struc object for the maloc to create a memory
	pElem = (PFlightInfo)malloc(sizeof(FlightInfo)); // Dyanmic memory allocation
	if (NULL == pElem) 
	{
	 exit(-1); // Check to make sure legal memory was allocated
 	}


	/* - Entering the flights information - */
	pElem->Flight_Num = (FlightNum)Num;
	pElem->Flight_Type = (FlightType)Type;
	pElem->Flight_Destination[0] = (char) "H";//(FlightDestination)Destination[0];
	pElem->Flight_Destination[1] = (char)"T";//(FlightDestination)Destination[1];
	pElem->Flight_Destination[2] = (char)"L";//(FlightDestination)Destination[2];
	pElem->Emergency = (BOOL)Emergency;
	/* - - - - - - - -the link part - - - - - - - - - - */
	pElem->headNext = NULL;
	return pElem;
};

/* Destroying a flight*/
void destroyFlight(PFlightInfo flight) {
	free(flight);
};

/**/
Result printFlight(PFlightInfo flight) {
	if (flight == NULL) return FAILURE;
	else // how to print properly??
		printf("FLIGHT &d &d &c&c&c &d\n", flight->Flight_Num,
									 flight->Flight_Type,
									 flight->Flight_Destination[0],
									 flight->Flight_Destination[1],
									 flight->Flight_Destination[2],
		 							 flight->Emergency
		);
	return SUCCESS;
};

