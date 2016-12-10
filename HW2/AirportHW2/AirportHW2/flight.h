//#pragma once
//#include "ex2.h"
#ifndef _FLIGHT_H_
#define _FLIGHT_H_
#include "ex2.h"

typedef int FlightNum;
typedef char FlightDestination;

typedef struct Flight_Info {
	//this will be the informmation part of the node
	FlightNum Flight_Num; //this have to be a unique number
	FlightType Flight_Type; //can be 0 or 1 meaning domestic or inter
	FlightDestination Flight_Destination[3]; // it dosent soupose to be more than one letter?
	BOOL Emergency;
	//this will be conection part of the node
	struct Flight_Info*  headNext;

}FlightInfo, *PFlightInfo;

typedef struct _Linked_List* P_Linked_List; //pointer to Linked_List_Element

PFlightInfo createFlight(FlightNum, FlightType, FlightDestination[], BOOL);
void destroyFlight(PFlightInfo);
Result printFlight(PFlightInfo);


#endif
