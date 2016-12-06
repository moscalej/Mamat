//#pragma once
//#include "ex2.h"
#ifndef _FLIGHT_H_
#define _FLIGHT_H_
#include "ex2.h"

typedef int FlightNum;
typedef char FlightDestination;

typedef struct Flight_Info {
	FlightNum Flight_Num;
	FlightType Flight_Type;
	FlightDestination Flight_Destination;
	BOOL Emergency;

}FlightInfo, *PFlightInfo;

typedef struct _Linked_List* P_Linked_List;

PFlightInfo createFlight(FlightNum, FlightType, FlightDestination);
void destroyFlight(PFlightInfo);
Result printFlight(PFlightInfo);


#endif