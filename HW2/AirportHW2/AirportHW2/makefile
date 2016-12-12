#!/bin/bash

#Creating the executable (airport)
airport: main.o airport.o runway.o flight.o
	gcc  main.o airport.o runway.o flight.o -o airport
#Creating object files

main.o: main.c airport.h
	gcc -c -g -wall main.c

airport.o: airport.c airport.h
	gcc -c -g -wall runway.c

runway.o: runway.c runway.h
	gcc -c -g -wall runway.c

flight.o: flight.c flight.h ex2.h
	gcc -c -g -wall flight.c
