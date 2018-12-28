#!/bin/bash
#

if [ -z "$1" ]; then 
#   param="helloWorld"
    param="economy"
else
   param="$1"
fi

./Debug/twitPick \
         --consumer-key "hiP7mgIpYZrEUFksnn7iWzzP0" \
         --consumer-secret "nQtaLrrNXCSuZvp9IYhaN7PujLu9gQqUIA5rc7ruzaVGgrOKkn" \
         --cookies-file "cookies2.txt" \
         --output-format tabular \
         --query "$param"

#./Debug/twitPick --credentials-file "credentials.txt" \
#         --cookies-file "cookies2.txt" \
#         --query "hola mundo"






