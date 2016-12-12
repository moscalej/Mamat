#!/bin/bash

# Creating the executable (airport)
airport: main.o airport.o runway.o flight.o
	gcc -o airport main.o airport.o runway.o flight.o

# Creating object files
main.o: main.c airport.h
	gcc -c -g -Wall main.c
airport.o: airport.c airport.h
	gcc -c -g -Wall runway.c
runway.o: runway.c runway.h
	gcc -c -g -Wall runway.c
flight.o: flight.c flight.h  ex2.h
	gcc -c -g -Wall flight.c
