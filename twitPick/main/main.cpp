/*
 * Copyright 2018 Raul Luna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*
 * main.cpp
 *
 * rluna
 * Jul 18, 2018
 *
 *
 */


#include "main.h"

const char *progName = "TwitPick";
const char *progVersion = "1.0";

int main( int argc, char *argv[] )
{
	Config config;

	std::cout << progName << " v." << progVersion << std::endl;

	std::unique_ptr<TwitPick> twitter( new TwitPick() );

	if( readArguments( argc, argv, config ) )
	{
		TwitPick twitter;
		TwitPickSearchParam params;

		copyValues( params, config );
		twitter.setCookiesFilename( config.cookiesFile );
		twitter.setConsumerKey( config.consumerKey );
		twitter.setConsumerSecret( config.consumerSecret );
		twitter.simpleSearch( params );


		std::unique_ptr<TwitterFormatter> formatter;

		if( config.outputType == "raw" )
		    formatter.reset( new TwitterFormatterRaw );
		else if( config.outputType == "tabular" )
		    formatter.reset( new TwitterFormatterTab );

		formatter->print( twitter.getLastSearchResult() );
	}


} // main

void copyValues( TwitPickSearchParam & searchParam, const Config & config )
{
    searchParam.count = config.count;
    searchParam.geocode = config.geocode;
    searchParam.includeEntities = (config.includeEntities == "true");
    searchParam.lang = config.lang;
    searchParam.locale = config.locale;
    searchParam.maxId = config.maxId;
    searchParam.query = config.queryString;
    if( config.resultType == "mixed" )
        searchParam.resultType = mixed;
    if( config.resultType == "popular" )
        searchParam.resultType = popular;
    if( config.resultType == "recent" )
        searchParam.resultType = recent;
    searchParam.sinceId = config.sinceId;
    searchParam.until = config.until;

} // copyValues

bool readArguments( int argc, char* argv[], Config& config )
{
	int opt;
	int option_index;
	bool helpOption;

	static struct option long_options[] =
	{
		{"help",  			no_argument,  	   nullptr, '?' },
		{"lang",            required_argument, nullptr, 'a' },
		{"cookies-file", 	required_argument, nullptr, 'c' },
		{"credentials-file",required_argument, nullptr, 'd' },
		{"geocode",         required_argument, nullptr, 'g' },
		{"since",           required_argument, nullptr, 'i' },
		{"consumer-key",    required_argument, nullptr, 'k' },
		{"locale",          required_argument, nullptr, 'l' },
		{"max-id",          required_argument, nullptr, 'm' },
		{"include-entities",required_argument, nullptr, 'n' },
		{"query",           required_argument, nullptr, 'q' },
		{"result-type",     required_argument, nullptr, 'r' },
		{"count",           required_argument, nullptr, 'o' },
        {"consumer-secret", required_argument, nullptr, 's' },
        {"output-format",   required_argument, nullptr, 't' },
		{"until",           required_argument, nullptr, 'u' },
		{nullptr,           0,                 nullptr,  0  }
	};

	helpOption = false;
	while( (opt = getopt_long(argc, argv, "?:c:", long_options, &option_index)) != -1 )
	{
		switch( opt )
		{
		case '?' : helpOption = true;
				   break;
		case 'a' : config.lang = optarg;
		           break;
		case 'c' : config.cookiesFile = optarg;
				   break;
		case 'd' : readConsumerKeyAndSecret( config, optarg );
				   break;
		case 'g' : config.geocode = optarg;
				   break;
		case 'i' : config.sinceId = optarg;
		           break;
		case 'k' : config.consumerKey = optarg;
				   break;
		case 'l' : config.locale = optarg;
		           break;
		case 'm' : config.maxId = optarg;
		           break;
		case 'n' : config.includeEntities = optarg;
		           break;
        case 'o' : config.count = std::atoi( optarg );
                   break;
		case 'q' : config.queryString = optarg;
				   break;
		case 'r' : config.resultType = optarg;
		           break;
        case 's' : config.consumerSecret = optarg;
                   break;
        case 't' : config.outputType = optarg;
                   break;
		case 'u' : config.until = optarg;
		           break;
		} // switch
	}

	if( helpOption )
	{
		printHelp();
		return false;
	}
	else
		if( !checkConfiguration( config ) )
			return false;
		else
			return true;

}

bool checkConfiguration( const Config & config )
{
	bool ok;

	ok = true;
	if( config.consumerKey.empty() )
	{
		std::cerr << "Error: no provided consumer key" << std::endl;
		ok = false;
	}
	if( config.consumerSecret.empty() )
	{
		std::cerr << "Error: no provided consumer secret" << std::endl;
		ok = false;
	}
	if( config.queryString.empty() )
	{
		std::cerr << "Error: no provided query string" << std::endl;
		ok = false;
	}

	return ok;
} // checkConfiguration


void readConsumerKeyAndSecret( Config &config, const char * filename )
{
	std::ifstream credentialsFile;

	credentialsFile.open( filename );
	credentialsFile >> config.consumerKey;
	credentialsFile >> config.consumerSecret;

	return;
}


void printHelp()
{
	std::cout <<
R"(Usage:
    twitPick [options]

Options:
    -?                   --help
        Show this help message

    -c[file]             --cookies-file [file]
        Set the file that will be used to store cookies

    -d[file]             --credentials-file [file]
        File to store the credentials (consumer key and 
        consumer secret). Must be stored in a single line. 
        First line must be the consumer key and the second 
        line must be the consumer secret.

     -k[consumerKey]      --consumer-key [consumerKey]
        Set the consumer key (a specific key given by twitter).

     -s[consumerSecret]   --consumer-secret [consumerSecret]
        Set the consumer secrete (a specific key given by twitter).

     -q[querystring]     --query [querystring]
		The search term. Must follow the rules of the 
		twitter search string.

     -o[number]          --count [number]
        Number of results per search.

     -g[geocode]         --geocode [geocode]
        Retrieves twitters by users located in a radius of the 
        given coordinates

     -l[locale]          --locale [locale]
        Language of the query (only ja is effective)

     -l[lang-code]       --lang [lang-code]
        Get tweets only of the given language. The language
        is ISO 639-1. 

     -r[resultType]      --result-type [resultType]
        Can have the values "mixed", "recent" or "popular". 
        recent: retrieves only the most recent tweets
        popular: retrieves the most popular tweets
        mixed: mixed content

      -u[yyyy-mm-dd]     --until [yyyy-mm-dd]
        Return tweets created until the given date

      -i[twitterId]      --since [twitterId]
        Return tweets later than the given tweet id

      -m[twitterId]      --max-id [twitterId]
        Return tweets lower than the given tweet id

      -t[outputFormat]   --output-format [outputFormat]
        Set the desired output format. Can be one of these values:
         raw: the received input from twitter
         tabular: tabulated result, one data per line

)";
} // printHelp






