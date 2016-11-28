#!/bin/bash

if [[ $# != 4 ]]; then
    #echo "we dont have the exact number of parameters need it to run the scrip"#statements
    exit 1
fi
#we will check if all the files exist and send a warning
if [[ !( -f $2) || !( -f $3) || !( -f $4) ]]; then
    #echo "one or more files dosent exist"
    exit 2
fi
#for easy use we will use names

log_address=$1
program_name=$2
input_address=$3
#we start valgrind with basic options:
#  we start with a memcheck and full leak check as workshok n2
#  we set an error exit code to be 2 for the next if stament (we know that 0 means all went well)
#  the ouput from valgrind we send to a null directory (so we dont get any output)
#  and the results from valgrind we send then to the log address
valgrind --tool=memcheck --leak-check=full --error-exitcode=2 --log-file=$log_address $program_name $input_address  1>/dev/null
if [[ "$?" -eq "0"  ]]; then
    echo "Memory V"
    unset log_address
    unset program_name
    unset input_address
    exit 0
else
    echo "Memory X"
    unset log_address
    unset program_name
    unset input_address
    exit 4
fi
