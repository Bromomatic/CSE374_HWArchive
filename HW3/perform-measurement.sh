#!/bin/bash
# Shawn Stern, CSE 374 HW3, Problem 1

if [ $# -lt 1 ]
then
    echo "${0}: script requires an argument" 1>&2
    exit 1
fi

# perform wget on the input, redirect output to null to keep it from displaying to stdout
#wget "$1" -O -T 10 url.txt 2> /dev/null
wget "$1" -O url.txt --timeout=10 -t 1 2>/dev/null

# if the wget failed, print 0 to stdout; otherwise do byte count and echo to stdout
if [ $? -ne 0 ]
then
    echo 0
else
    wc -c < url.txt
fi

