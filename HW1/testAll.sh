#!/bin/bash

#coments
if [[ $# != 2 ]]; then
    #echo "we dont have the exact number of parameters need it to run the scrip"#statements
    exit 1
fi
#check if there is a sbforder call logs if is there will send a error and stop the scrip
if [[ -d logs ]]; then
    echo "there is a dir call logs"
    exit 2
else
    mkdir logs

fi

lineNumber=1
test_number=0
test_pased=0
while read line
    #test_descriotion=cut -d"@" -f1 $line
    program_name=cut -d"@" -f2 $line
    input_address=cut -d"@" -f3 $line
    output_address=cut -d"@" -f4 $line
    testCompile "logs/$lineNumber.compile.log" $program_name
    ((test_number++))
    if [[ "$?" -eq "0" ]]; then
        ((test_pased++))
    fi
    testInOut "logs/$lineNumber.inout.log" $program_name $input_address $output_address
    ((test_number++))
    if [[ "$?" -eq "0" ]]; then
        ((test_pased++))
    fi
    testMem "logs/$lineNumber.memory.log" $program_name $input_address
    ((test_number++))
    if [[ "$?" -eq "0" ]]; then
        ((test_pased++))
    fi
    ((lineNumber++))
done<$1
exit 0
