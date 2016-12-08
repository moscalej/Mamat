#pragma once

#ifndef _RUNWAY_H_
#define _RUNWAY_H_
#include "ex2.h"
#include "flight.h"

typedef int RunwayNum;
typedef char RunwayType;

typedef struct Runway_Info {
	/*-------this is the information part of the node---- */
	RunwayNum Runway_Num;
	RunwayType Runway_Type;
	/*------this is the link part of the node------*/
	P_RunwayList RunwayList;
	PFlightInfo head_flight;

}RunwayInfo, *PRunwayInfo;

typedef struct _Runway_List* P_RunwayList;

PRunwayInfo createRunway(RunwayNum, RunwayType);
void destroyRunway(PRunwayInfo);
BOOL isFlightExists(PRunwayInfo, FlightNum); // Need to check for FlightNum
int getFLightNum(PRunwayInfo);
Result addFlight(PRunwayInfo, PFlightInfo); // Need to add all flight information
Result removeFlight(PRunwayInfo, FlightNum);
Result depart(PRunwayInfo);
Result printRunway(PRunwayInfo);


#endif