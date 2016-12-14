//#pragma once
//#include "ex2.h"
#ifndef _FLIGHT_H_
#define _FLIGHT_H_
#include "ex2.h"

typedef int FlightNum;
typedef char* FlightDestination;

typedef struct Flight_Info {
	//this will be the informmation part of the node
	FlightNum Flight_Num; //this have to be a unique number
	FlightType Flight_Type; //can be 0 or 1 meaning domestic or inter
	FlightDestination Flight_Destination; // it dosent soupose to be more than one letter?
	char flight_destination_0[4];
	BOOL Emergency;
	//this will be conection part of the node
	struct Flight_Info*  headNext;

}FlightInfo, *PFlightInfo;

typedef struct _Linked_List* P_Linked_List; //pointer to Linked_List_Element

PFlightInfo createFlight(int, FlightType , char* , BOOL);
FlightType isI_or_D(char);
BOOL isE_or_R(char);
void destroyFlight(PFlightInfo);
Result printFlight(PFlightInfo);


#endif
