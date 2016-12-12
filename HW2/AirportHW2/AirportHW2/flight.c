#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "flight.h"

/*Creating a flight*/
PFlightInfo  createFlight(int Num, FlightType Type, char *Destination, BOOL Emergency) //pointer to a char what i want is to copy what is in that place to my char field
{
	PFlightInfo pElem;
 int i;
	pElem = (PFlightInfo)malloc(sizeof(FlightInfo)); // Dyanmic memory allocation

	if (NULL == pElem) exit(-1); // Check to make sure legal memory was allocated

								 /* - Entering the flights information - */


	pElem->Flight_Num = (FlightNum)Num;
	pElem->Flight_Type = (FlightType)Type;
	for ( i = 0; i < 4; i++)
	{
		pElem->flight_destination_0[i] = *(Destination+i);
	}
	pElem->Flight_Destination = pElem->flight_destination_0;
	pElem->Emergency = (BOOL)Emergency;
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
	char temp, temp1;
	if (flight->Flight_Type == 0) temp = 'D';
	else if (flight->Flight_Type == 1) temp = 'I';
	if (flight->Emergency == TRUE) temp1 = 'E';
	else if (flight->Emergency == FALSE) temp1 = 'R';

	fprintf(stdout, "Flight %d %c %s %c\n", flight->Flight_Num, temp, flight->Flight_Destination, temp1);
	return SUCCESS;
}

FlightType isI_or_D(char input) {
	if (input == 'I') return INTERNATIONAL;
	else return DOMESTIC;
}
BOOL isE_or_R(char input) {
	if (input == 'E') return TRUE;
	else return FALSE;
}
