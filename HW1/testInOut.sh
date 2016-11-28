#!/bin/bash

#first we will check if we have all the parameters

if [[ $# != 4 ]]; then
    echo #"we dont have the exact number of parameters need it to run the scrip"#statements
    exit 1
fi
#we will check if all the files exist and send a warning
if [[ !( -f $2) || !( -f $3) || !( -f $4) ]]; then
    echo #"one or more files dosent exist"
    exit 2
fi

#we want to run the program at $2 seconde parameter  with the imput from $3 and send it to
#the $1 parameter log and all the log files save it on the log $1 parameter

$2<$3>$1

#now we want to check if the log output is equal as the expected one,
#the diff
#program will return a code if it was sucsefull
diff -q $4 $1 > var #we use the -q option to save space
if [[ !(-s var)]]; then #will if the files are diferent there will be something on vaR
    echo "InOut V"
    rm var
    exit 0
else
    echo "InOut X"
    rm var
    exit 3
fi
