#!/bin/bash

#this scrip will compile a C program and will write the
#compile log in to the log finel given by the user
#it will also cheek if the arguments given are valid ones


#the first 3 if are cheeking if the arguments are valid
if (($# != 2)); then
    #echo "There are not enought parameters"
    exit 1 # for debuging
fi
if [[(!(-f"${2}".c))]]; then
    #echo "the program is not an executable program"
    exit 2
fi
if [[!(-s"${2}".c)]]; then
    #echo "the program is empty"
    exit 3
fi

#once we are sure the program exist we will compile it
gcc "${2}".c -Wall -g -o "$2" > "$1" 2>&1

#After the compilation is call it will cheeck if it run it as
#want it
if [[ $? -eq 0 ]]; then #last call resoult
  if [[ !(-s "$1") ]]; then #then we check that is not empty
      echo "Compile V"
      exit 0
  else
      echo "Compile X"
      exit 4
  fi
 else
    echo "Compile X"
    exit 5
fi
