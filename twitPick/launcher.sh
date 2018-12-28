#!/bin/bash
#

if [ -z "$1" ]; then 
#   param="helloWorld"
    param="economy"
else
   param="$1"
fi

./Debug/twitPick \
         --credentials-file "credentials.txt" \
         --cookies-file "cookies2.txt" \
         --output-format tabular \
         --query "$param"

#./Debug/twitPick --credentials-file "credentials.txt" \
#         --cookies-file "cookies2.txt" \
#         --query "hola mundo"






