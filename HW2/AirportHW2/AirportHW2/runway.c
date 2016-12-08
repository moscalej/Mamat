#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "runway.h"



PRunwayInfo  createFlight(int Num, char Type) {
	PRunwayInfo pElem;  //defines pELem as a pointer to a struc object for the maloc to create a memory
	pElem = (PRunwayInfo)malloc(sizeof(PRunwayInfo)); // Dyanmic memory allocation

	if (NULL == pElem) {
		exit(-1); // Check to make sure legal memory was allocated
	}
	/* - Entering the flights information - */
	pElem->Runway_Num = (int) Num;
	pElem->Runway_Type = (char) Type;
	//link field of the node
	pElem->RunwayList = NULL;
	pElem->head_flight = NULL;
	
	return pElem;
};


//this funtion will reach the header from the runway and free all the flaight
//on it in the a while loop
void destroyRunway(PRunwayInfo runwayNumber) {
	PRunwayInfo pointer_location_old;
	PRunwayInfo pointer_location_new;
	pointer_location_new = runwayNumber->head_flaight;
	if (pointer_location_new != NULL ) {
		while (true) {
			pointer_location_old = pointer_location_new;
			pointer_location_new = pointer_location_new->head_flaight;
			destroyFlight(pointer_location_old);
			if (pointer_location_new == NULL) {
				break;
			}
		}
	}
	free(runwayNumber)
}

BOOL isFlightExists(PRunwayInfo, FlightNum)