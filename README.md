# twitPick

Command line tweet searcher.

**twitPick** is a command line tool to easily search for tweets. It doesn't need 
your username/passwords, instead it uses an application key (called Consumer API
key / Consumer API Secret). 

I've developed this solution to provide an easy and convenient interface to search
for tweets using a command line tool. 

Usage: 

```
$ # remember to install libcurl the first time you use it: 
$ #  sudo apt-get install libcurl4
$ twitPick \
         --credentials-file "credentials.txt" \
         --cookies-file "cookies2.txt" \
         --output-format tabular \
         --query "#peaceWorld"

```

Each invocation must have at least two values: 


  1. A credentials file (see example file credentials.txt.EXAMPLE in the project), 
  that have to be stored the consumer key and consumer secret. 

  2. A cookies file: this file will be used by libcurl to store the cookies. 

  3. A query parameter (#peaceWorld in the example)

  4. Besides it's not necessary, but convenient, an output format. I've created this 
  "tabular" format to ease the parsing and manipulation of the resulting format. I think
  that the json format is very convenient, but it is not the best for batch processing.


  
