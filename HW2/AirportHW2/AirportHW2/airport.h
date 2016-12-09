#pragma once
#ifndef _AIRPORT_H_
#define _AIRPORT_H_
#include "ex2.h"
#include "runway.h"

typedef struct Airport_Info {
	/*-------this is the information part of the node---- */
	
	/*------this is the link part of the node------*/
	PRunwayInfo RunwayList;
	

}AirportInfo, *PAirportInfo;

PAirportInfo Airporthead; //global variable

Result addRunway(RunwayNum, RunwayType);

Result removeRunway(RunwayNum);

Result addFlightToAirport(FlightNum, FlightType, BOOL); //Bool = emergency

Result depoartFromRunway(RunwayNum);

Result stormAlert
#endif