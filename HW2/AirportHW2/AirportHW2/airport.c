#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include "airport.h"


/**/
Result addRunway(RunwayNum runway_number, RunwayType runway_type)
{
	PRunwayInfo runway_navagator;

	if (Airporthead->RunwayList == NULL)
	{
		Airporthead->RunwayList = createRunway(runway_number, runway_type);
		return SUCCESS;
	}
	runway_navagator = Airporthead->RunwayList;
	while (true)
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
}



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

		}
}