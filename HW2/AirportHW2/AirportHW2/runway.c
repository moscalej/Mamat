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
	PFlightInfo pointer_location_old;
	PFlightInfo pointer_location_new;
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



/*-- this look will go thrue the linked list os the planes search
if the flight number exist on the list and if it does will return true 
if it dosent will and reachs the end of the list and find a null pointer
wich will return FALSE*/

BOOL isFlightExists(PRunwayInfo runway_pointer, FlightNum flight_number) {
	
	PFlightInfo pointer_location_new;
	pointer_location_new = runway_pointer->head_flaight;
	if (pointer_location_new == NULL)
	{
		return FALSE;
	}
	while (true)
	{
		if (pointer_location_new->Flight_Num == flight_number) 
		{
			return TRUE;
		}
		else if (pointer_location_new -> headNext == NULL)
		{
			return FALSE;
		}
		pointer_location_new = pointer_location_new-> headNext ;
	}
}

/*this funtion will run true the linked list and every time it rachs a new node
will  add one to the counter*/
int getFLightNum(PRunwayInfo runway_pointer)
{
	int counter = 0;
	PFlightInfo pointer_location_new;
	pointer_location_new = runway_pointer->head_flaight;
	if (pointer_location_new == NULL)
	{
		return 0;
	}
	while (true)
	{
		counter++;
		pointer_location_new = pointer_location_new->headNext;
		if (pointer_location_new->headNext == NULL)
		{
			return counter;
		}
	}

}


Result addFlight(PRunwayInfo, PFlightInfo)
{

}