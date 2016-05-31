#!/bin/bash
# Shawn Stern, CSE 374 HW3, Problem 3

if [ $# -lt 2 ]
then
    echo "${0}: script requires 2 arguments" 1>&2
    exit 1
fi

# For each line in the file, perform measurement on URL, print output to user,
# and write to output file.
count=1

while read line
do
    echo "Performing measurement on $line"
    result=`./perform-measurement.sh "$line"`
    if [ $result -gt 0 ]
    then
		echo "...success"
		echo "$count $line $result" >> "$2"
		# Increment our rank value
		# (( count = $count + 1 ))
    else
		echo "...failed"
    fi
    # Counter moved here after looking at example output for results-small.txt
    (( count = $count + 1 ))
done < "$1"
