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

typedef struct good_and_bad
{
	PFlightInfo good_line;
	PFlightInfo bad_line;
}GoodAndBad, *PGoodAndBad;


PAirportInfo Airporthead; //global variable

/*this are funtions to help in other funtions*/
PRunwayInfo findTheLane(FlightType /*, BOOL bool*/); //status<--- need debug
PRunwayInfo findLaneByNumber(Runway_Num );//status<--- need debug
PGoodAndBad removeBadFlights(PFlightInfo, FlightDestination);

/*funtions asked by the HW2*/
Result addRunway(RunwayNum, RunwayType); //status<--- need debug
Result removeRunway(RunwayNum); //status<--- need debug
Result addFlightToAirport(FlightNum, FlightType, FlightDestination, BOOL);//status<--- need debug  //Bool = emergency
Result depoartFromRunway(RunwayNum); //status<--- need debug
Result stormAlert(FlightDestination[]);//status<--- not started
void destroyAirport();// status<-- need debug
#endif