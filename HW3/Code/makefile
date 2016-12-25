#!/bin/bash
# Makefile for creating the 'DocsSearchApp' program
CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = main.o graph.o set.o list.o
RM = rm -f
robommt: $(OBJS)
	$(CCLINK) $(CFLAGS) -o robommt $(OBJS)

 
main.o: main.c graph.h set.h list.h
	$(CCLINK) $(CFLAGS) -c main.c

graph.o: graph.c graph.h set.h list.h
	$(CCLINK) $(CFLAGS) -c graph.c

set.o: set.c set.h list.h
	$(CCLINK) $(CFLAGS) -c set.c

list.o: list.c list.h
	$(CCLINK) $(CFLAGS) -c list.c 

#clean old files before new make
clean:
	$(RM) robommt *.o *.bak *~"#"*core
