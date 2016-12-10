#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "airport.h"







/**/
Result addRunway(RunwayNum runway_number, RunwayType runway_type)
{
	printf("Inserti got here i read &d and &c.\n", runway_number, runway_type); //<---debug
	PRunwayInfo runway_navagator;

	if (Airporthead->RunwayList == NULL)
	{
		Airporthead->RunwayList = createRunway(runway_number, runway_type);
		return SUCCESS;
	}
	runway_navagator = Airporthead->RunwayList;
	while (1)
	{
		if (runway_navagator->Runway_Num == runway_number)
		{
			return FAILURE;
		}
		if (runway_navagator->RunwayList == NULL)
		{
			runway_navagator->RunwayList = createRunway(runway_number, runway_type);
			return SUCCESS;
		}
		runway_navagator = runway_navagator->RunwayList;

	}
};



Result removeRunway(RunwayNum runway_number)
{
	PRunwayInfo runway_navagator;
	PRunwayInfo runway_temp;

	if (Airporthead->RunwayList == NULL)
	{

		return FAILURE;
	}
	runway_navagator = Airporthead->RunwayList;
	if (runway_navagator->Runway_Num == runway_number)
	{
		Airporthead->RunwayList = Airporthead->RunwayList->RunwayList;
		destroyRunway(runway_navagator);
		return SUCCESS;
	}
	while (1)
	{
		if (runway_navagator->RunwayList == NULL)
		{
			return FAILURE;
		}
		if (runway_navagator->RunwayList->Runway_Num == runway_number)
		{
			runway_temp = runway_navagator->RunwayList;
			runway_navagator->RunwayList = runway_navagator->RunwayList->RunwayList;
			destroyRunway(runway_temp);
		}
	}
};



/*This function will find the lane that meets these conditions
1 - If the lane in the proper runway type we are looking for
2 - If the number of flights on the runway list is smaller than the smallest
runway list we've found so far.
3 - If the runway number is smaller than the smallest runway number we found
so far.
After these comparing conditions, if the function finds a suitable spot it
will return a pointer to correct runway. If not it will return NULL*/
PRunwayInfo findTheLane(FlightType flight_type/*, BOOL bool*/) //not shure if we need emergency for this
{
	//RunwayInfo pointer_lane0;
	PRunwayInfo pointer_lane;
	pointer_lane = Airporthead->RunwayList;
	//pointer_lane = &pointer_lane0;

	RunwayInfo pointer_lane_minumun0;
	PRunwayInfo pointer_lane_minumun;
	pointer_lane_minumun = &pointer_lane_minumun0;
	pointer_lane_minumun->Runway_Num = MAX_ID;

	BOOL did_it_change = FALSE;

	int number_of_flights_old, number_of_flights_new;
	number_of_flights_old = MAX_ID;
	
	while (TRUE)
	{
		if (pointer_lane->Runway_Type == flight_type)
		{
			number_of_flights_new = getFLightNum(pointer_lane);
			if (number_of_flights_new <= number_of_flights_old)
			{
				if (pointer_lane->Runway_Num <= pointer_lane_minumun->Runway_Num)
				{
					pointer_lane_minumun = pointer_lane;
					did_it_change = TRUE;
				}
				number_of_flights_old = number_of_flights_new;
			}
		}
		if (pointer_lane->RunwayList == NULL)
		{
			if (did_it_change)
			{
				return pointer_lane_minumun;
			}
			else
			{
				return NULL;
			}
		}
		pointer_lane = pointer_lane->RunwayList;
	}
}


Result addFlightToAirport(int flight_number, FlightType flight_type, FlightDestination flight_destination, BOOL bool)
{
	PFlightInfo new_flight;
	PRunwayInfo runway_pointer;
	runway_pointer = findTheLane(flight_type);
	new_flight = createFlight(flight_number, flight_type, flight_destination, bool);
	return addFlight(runway_pointer, new_flight);
}




/*to be fill*/
void printAirport()
{/*
	PAirportInfo temp = Airporthead;
	Result result;
	printf("Airport status:\n");
	while (1) {
		result = printRunway(temp->RunwayList);
		if (result = FAILURE) break;
		if (temp->RunwayList != NULL) {
			temp->RunwayList = temp->RunwayList->RunwayList;
		}
		else break;
	}*/
};


/* search a lane by number in the airport */
PRunwayInfo findLaneByNumber(runway_number)
{
	PRunwayInfo lane_temp;
	lane_temp = Airporthead->RunwayList;
	while (TRUE)
	{
		if (NULL == lane_temp)
		{
			return NULL;
		}
		if (runway_number == lane_temp->Runway_Num)
		{
			return lane_temp;
		}
		lane_temp = lane_temp->RunwayList;
	}
}




/*find the lane pointer and use depart from runway.c*/
Result departFromRunway(runway_number)
{
	PRunwayInfo lane_temp;
	lane_temp = findLaneByNumber(runway_number);
	if (lane_temp == NULL)
	{
		return FAILURE;
	}
	return depart(lane_temp);
}


/*i wanted do do it recursive but we need to enter inputs :( */
void destroyAirport()
{
	PRunwayInfo hahah_bye_runway;
	PRunwayInfo hahah_bye_runway_next;
	hahah_bye_runway = Airporthead->RunwayList;
	while (TRUE)
	{
		if (NULL == hahah_bye_runway)
		{
			break;
		}
		hahah_bye_runway_next = hahah_bye_runway->RunwayList;
		destroyRunway(hahah_bye_runway);
		hahah_bye_runway = hahah_bye_runway_next;
	}
}



/*
#####################	THIS FUNTION IS A SUBFUNTION USED IN STORM ALARM##################
this funtion will sort the the line and return two PFLIGHTINFO pointer one with the planes
that maches the direction and the other with the planes that  dont
the good line is the one that maches the adrres*/
PGoodAndBad removeBadFlights(PFlightInfo start_pointer_0, FlightDestination destination[]) 
{
	GoodAndBad awnser_0;
	PGoodAndBad awnser_pointer;
	awnser_pointer = &awnser_0;

	PFlightInfo start_pointer;

	PFlightInfo good_line0;
	FlightInfo good_line;
	good_line0 = &good_line;
	PFlightInfo bad_line0;
	FlightInfo bad_line;
	bad_line0 = &bad_line;

	start_pointer = start_pointer_0;
	
	good_line0->headNext = NULL;
	bad_line0->headNext = NULL;
	
	awnser_0.bad_line = bad_line0;
	awnser_0.good_line= good_line0;
	


	if (start_pointer == NULL)
	{
		awnser_pointer->bad_line = NULL;
		awnser_pointer->good_line = NULL;
		return awnser_pointer;
	}
	while (TRUE)
	{
		if (start_pointer->Flight_Destination == destination)
		{
			good_line0->headNext = start_pointer;
			good_line0 = good_line0->headNext;
			good_line0->headNext = NULL;
		}
		else
		{
			bad_line0->headNext = start_pointer;
			bad_line0 = bad_line0->headNext;
			bad_line0->headNext = NULL;
		}
		start_pointer = start_pointer->headNext;
		if (start_pointer == NULL)
		{
			awnser_pointer->bad_line = awnser_pointer->bad_line->headNext;
			awnser_pointer->good_line = awnser_pointer->good_line->headNext;
			return awnser_pointer;
		}
	}
}



/*we will create a emergency runway were we will move
all the planes with  the definition will go

then we will add all the flights back to the airport*/
Result stormAlert(FlightDestination destination[])
{
	GoodAndBad emergency_flights;  //      <--- this will be the the statarting stone
	PGoodAndBad emergency_flights_pointer;
	emergency_flights_pointer = &emergency_flights;

	RunwayInfo runway;			//      <--- this will be the the statarting stone
	PRunwayInfo runway_pointer;
	runway_pointer = &runway;
	 
	FlightInfo emergency_flights_list_0;		//      <--- this will be the the statarting stone
	PFlightInfo emergency_flights_list_pointer;
	emergency_flights_list_pointer= &emergency_flights_list_0;

	Result temp;

	runway_pointer = Airporthead->RunwayList;


	if (NULL == runway_pointer)
	{
		return FAILURE;
	}
	/*this is the fech part of the funtion*/
	while (TRUE)
	{
		emergency_flights_pointer = removeBadFlights(runway_pointer->head_flight, destination);
		runway_pointer->head_flight = emergency_flights_pointer->bad_line;
		emergency_flights_list_pointer->headNext = emergency_flights_pointer->good_line;

		while (TRUE)
		{
			temp = addFlight(runway_pointer, emergency_flights_pointer->good_line);
			emergency_flights_pointer->good_line = emergency_flights_pointer->good_line->headNext;
			if (NULL == emergency_flights_pointer)
			{
				break;
			}
		}		
		runway_pointer = runway_pointer->RunwayList;
		if (runway_pointer == NULL)
		{
			break;
		}
	}



	return	SUCCESS;
}

