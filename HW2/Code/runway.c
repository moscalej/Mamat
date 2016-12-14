#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runway.h"


/* This funtion creates a runway node with :
in the information field the number and type
and with the node fild pointers to the next
node
$$$$$$$$$$$$$$$$$$$working#################*/

PRunwayInfo createRunway(int Num, char Type) {
	PRunwayInfo pElem;  //defines pElem as a pointer to a struct object for the malloc to create memory
	pElem = (PRunwayInfo)malloc(sizeof(RunwayInfo)); // Dyanmic memory allocation

	if (NULL == pElem) {
		exit(-1); // Check to make sure legal memory was allocated
	}
	/* - Entering the flights information - */
	pElem->Runway_Num = (int)Num;
	pElem->Runway_Type = (char)Type;
	//link field of the node
	pElem->RunwayList = NULL;
	pElem->head_flight = NULL;

	return pElem;
}


/* This function finds the head flight of a runway
and then free's all the flights on THAT runway */
void destroyRunway(PRunwayInfo runwayNumber) {
	PFlightInfo pointer_location_old;
	PFlightInfo pointer_location_new;
	pointer_location_new = runwayNumber->head_flight;
	if (pointer_location_new != NULL) {
		while (1) {
			pointer_location_old = pointer_location_new;
			pointer_location_new = pointer_location_new->headNext;
			destroyFlight(pointer_location_old);
			if (pointer_location_new == NULL) {
				break;
			}
		}
	}
	free(runwayNumber);
}


/* This function is designed to search through our linked lists of flights on a
given runway. If the flight exists then the function will return TRUE. If we get a NULL
from the pointer then the function returns FALSE. */
BOOL isFlightExists(PRunwayInfo runway_pointer, FlightNum flight_number) {

	PFlightInfo pointer_location_new;
	pointer_location_new = runway_pointer->head_flight;
	if (pointer_location_new == NULL) {
		return FALSE;
	}
	while (1) {
		if (pointer_location_new->Flight_Num == flight_number) {
			return TRUE;
		}
		else if (pointer_location_new->headNext == NULL) {
			return FALSE;
		}
		pointer_location_new = pointer_location_new->headNext;
	}
}

/* This funtion runs through the linked list and every time it reachs a node that
doesn't point to NULL it will increase the counter by one (). */
int getFLightNum(PRunwayInfo runway_pointer, int flight_number) {
	int counter = 0;
	PFlightInfo pointer_location_new;
	pointer_location_new = runway_pointer->head_flight;

	if (pointer_location_new == NULL) {
		return 0;
	}
	if (flight_number == pointer_location_new->Flight_Num)
	{
		return (-1);
	}

	while (1) {
		counter++;
		if (flight_number == pointer_location_new->Flight_Num)
		{
			return (-1);
		}
		if (pointer_location_new->headNext == NULL) {
			return counter;
		}
		pointer_location_new = pointer_location_new->headNext;
	}
}


/* This function adds a flight to a valid runway. If no valid runway is found or
the flight wasn't added to any runway the function returns FAILURE
(only if the types are not the same).*/
Result addFlight(PRunwayInfo runway_pointer, PFlightInfo new_flight_pointer) {
	/*Secury check if the pointers are what we need it*/
	if (NULL == runway_pointer || NULL == new_flight_pointer)
	{
		return FAILURE;
	}
	PFlightInfo pointer_location_new;
	PFlightInfo pointer_location_old;
	pointer_location_new = runway_pointer->head_flight;   // this will save pointer location new as a pointer to the first fly

	if (new_flight_pointer->Flight_Type == isI_or_D(runway_pointer->Runway_Type))
	{


		/*check if the runway is empy*/
		if (pointer_location_new == NULL) {
			runway_pointer->head_flight = new_flight_pointer;
			return SUCCESS;
		}
		/*want to check if the first fly is an emergency*/
		if (pointer_location_new->Emergency == FALSE && new_flight_pointer->Emergency == TRUE) {
			runway_pointer->head_flight = new_flight_pointer;
			new_flight_pointer->headNext = pointer_location_new;
			return SUCCESS;
		}
		//////////////////////////////////////////////////////
		/*<<<<<<------ need to be chked i mith made  a mistake*/
		///////////////////////////////////////////////////////

		/*this soupuse navage the linked list and check if all the emergency flights after until the first not mergency on the
		line and add the flight if is an emergency if not, it will add in the end*/
		while (1) { // i am bit confuse with the pointers we have to check the well if we pass the adress or the think inside the adres

			pointer_location_old = pointer_location_new;

			if (pointer_location_new->headNext == NULL)
			{

				pointer_location_new->headNext = new_flight_pointer;

				return SUCCESS;
			}

			pointer_location_new = pointer_location_new->headNext;

			if (pointer_location_new->Emergency == FALSE && new_flight_pointer->Emergency == TRUE)
			{
				pointer_location_old->headNext = new_flight_pointer;
				new_flight_pointer->headNext = pointer_location_new;
				return SUCCESS;
			}





		}
	}
	else	return FAILURE;
}


/*this funtion will search and delete the flight in 3 comparations
1-search if there is a flight on the runway to delete
2-search if the first flight is the one to dele and delete
3-once we are working with only flight pointers will search
on the linked list until find it and delete it or getting
to the end of the list and return failure */
Result removeFlight(PRunwayInfo runway_pointer, FlightNum flight_id)
 {
 
	PFlightInfo pointer_location_new;
	PFlightInfo pointer_location_temp;
	pointer_location_new = runway_pointer->head_flight;   // This saves pointer_location_new as a pointer to the first flight

														  /**/
	if (pointer_location_new == NULL) {
		return FAILURE;
	}
	/*want to check if the first flight is the one to delete*/
	if (pointer_location_new->Flight_Num == flight_id) {
		runway_pointer->head_flight = pointer_location_new->headNext;
	  destroyFlight( pointer_location_new );
		return SUCCESS;
	}


	while (1) {
		if (pointer_location_new->headNext == NULL) {
			return FAILURE;
		}

		if (pointer_location_new->headNext->Flight_Num == flight_id) {
			pointer_location_temp = pointer_location_new->headNext->headNext;
			destroyFlight(pointer_location_new->headNext);
			pointer_location_new->headNext = pointer_location_temp;
			return SUCCESS;
		}
		pointer_location_new = pointer_location_new->headNext;
	}
}


/* This function will destroy the FLIGHT flight on the runway list pointer and connect the
(now empty) head of the runway list to the next pointer. */
Result depart(PRunwayInfo runway_pointer) {
	PFlightInfo pointer_location_new;
	
	if (runway_pointer->head_flight == NULL) {
		return FAILURE;
	}
	pointer_location_new = runway_pointer->head_flight->headNext;
	destroyFlight(runway_pointer->head_flight);
	runway_pointer->head_flight = pointer_location_new;
	return SUCCESS;
}



/*this will print the header and then will navagate the list and print the flights*/
Result printRunway(PRunwayInfo runway_pointer) {

	PFlightInfo pointer_location_temp;
	if (runway_pointer == NULL) return FAILURE;
	pointer_location_temp = runway_pointer->head_flight;
	int number_of_planes;
	Result result;
	if (runway_pointer->Runway_Type == 'I') {
		printf("Runway %d international\n",
			runway_pointer->Runway_Num
			);
	}
	else if (runway_pointer->Runway_Type == 'D') {
		printf("Runway %d domestic\n",	runway_pointer->Runway_Num);
	}
	number_of_planes = getFLightNum(runway_pointer, MAX_ID);
	printf("%d flights are waiting:\n", number_of_planes);
	while (1) {
		if (pointer_location_temp == NULL) {
			return SUCCESS;
		}
		result = printFlight(pointer_location_temp);
		pointer_location_temp = pointer_location_temp->headNext;
	}
}

