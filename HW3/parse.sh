#!/bin/bash
# Shawn Stern, CSE 374 HW3, Problem 2

# if given fewer than 2 arguments, print error and exit
if [ $# -lt 2 ]
then
    echo "${0}: script requires 2 arguments" 1>&2
    exit 1
fi

# if given file doesn't exist, print error and exit
if [ ! -e $1 ]
then
    echo "${0}: provided file does not exist" 1>&2
    exit 1
fi

# grep the file for URLs and save to the desired text file
grep http "$1" > "$2"

# convert the text preceeding the URL to blank string by matching .*http and replacing with just http
sed -i 's/.*http/http/g' "$2"

# likewise, convert the text trailing the URL by matching an appropriate URL ender like .com, .edu, or .htm
# and all trailing characters as two matches, and replacing with just the first match (so the url still works)
# old, cheater sedthat relied on tags: sed -i 's/".*$//g' "$2"
# Note that in the case of europa.eu.int, that URL is actually invalid according to their website and they
# say to simply use europa.eu, so I changed my sed to match that case, not .int (which also kills websites) 
sed -i 's/\(\.com\|\.net\|.org\|\.edu\|\.gov\|.uk\|\.eu\|\.html\|.htm\)\(.*\)/\1/g' "$2"
