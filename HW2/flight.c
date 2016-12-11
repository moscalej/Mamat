#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "flight.h"

/*Creating a flight*/
PFlightInfo  createFlight(int Num, char Type, FlightDestination Destination, char Emergency) {
	PFlightInfo pElem;
	pElem = (PFlightInfo)malloc(sizeof(FlightInfo)); // Dyanmic memory allocation

	if (NULL == pElem) exit(-1); // Check to make sure legal memory was allocated

								 /* - Entering the flights information - */
	pElem->Flight_Num = (FlightNum)Num;
	pElem->Flight_Type = (FlightType)Type;
	pElem->Flight_Destination = Destination;
	pElem->Emergency = (BOOL)Emergency;
	/* - - - - - - - - - - - - - - - - - - */
	pElem->headNext = NULL;

	return pElem;
}
/* Destroying a flight*/
void destroyFlight(PFlightInfo flight) {
	free(flight);
};

/**/
Result printFlight(PFlightInfo flight) {
	if (flight == NULL) return FAILURE;
	/*else // how to print properly??
		printf(stdout, "Flight %d %d %d %d",
			flight->Flight_Num, flight->Flight_Type, flight->Flight_Destination, flight->Emergency);
	return SUCCESS;
	*/
}



