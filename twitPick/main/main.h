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
 * main.h
 *
 * rluna
 * Dec 18, 2018
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <curl/curl.h>
#include <getopt.h>
#include <json.hpp>
#include <memory>

#include "EncodedUrl.h"
#include "HttpHeaderParser.h"
#include "CurlWrapper.h"
#include "Request.h"
#include "TwitPick.h"
#include "TwitPickSearchParam.h"
#include "TwitterFormatterRaw.h"
#include "TwitterFormatterTab.h"

struct Config
{
	std::string cookiesFile;
	std::string consumerKey;
	std::string consumerSecret;
	std::string queryString;
	std::string geocode;
	std::string locale;
	std::string lang;
	std::string sinceId;
	std::string maxId;
	std::string until;
	std::string resultType;
	std::string includeEntities;
	long count;
	std::string outputType;

	Config()
	{
		cookiesFile = "cookies.txt";
		consumerKey = "";
		consumerSecret = "";
		queryString = "example";
		geocode = "";
		locale = "";
		lang = "";
		count = 100;
		sinceId = "";
		maxId = "";
		until = "";
		resultType = "mixed";
		outputType = "raw";
	}
};

void copyValues( TwitPickSearchParam & searchParam, const Config & config );

bool readArguments( int argc, char* argv[], Config& config );

void printHelp();

bool checkConfiguration( const Config & config );

void readConsumerKeyAndSecret( Config &config, const char * filename );



#endif /* MAIN_H_ */
