#!/bin/bash
CCC = g++
CXXFLAGS = -Wall -g -std=c++0x
CXXLINK = $(CCC)
OBJS = main.o polynom.o complex.o  
RM = rm -f
#Default target (usually "all")
all: Poly

#Creating the executables
Poly: $(OBJS)
	$(CXXLINK) -o Poly $(OBJS)
#Creating object files using default rules

complex.o: complex.C complex.H

polynom.o: polynom.C polynom.H

main.o: main.C polynom.H complex.H

#Cleaning old files before new make
clean:
	$(RM) Poly *.o *.bak *~ "#"* core
