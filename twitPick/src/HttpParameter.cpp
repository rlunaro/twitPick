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
 * PostParameter.cpp
 *
 * rluna
 * Nov 12, 2018
 *
 */

#include <HttpParameter.h>

HttpParameter::HttpParameter( std::string name, std::string value )
{
	HttpParameter::name = name;
	HttpParameter::value = value;
}

std::string HttpParameter::getName()
{
	return name;
}

std::string HttpParameter::getValue()
{
	return value;
}

std::string HttpParameter::getEscapedNameValue( CURL *curlHandle )
{
	char* escapedName = curl_easy_escape( curlHandle, name.c_str(), name.length() );
	char* escapedValue = curl_easy_escape( curlHandle, value.c_str(), value.length() );
	std::string out = std::string(escapedName) + "=" + escapedValue;
	curl_free( escapedValue );
	curl_free( escapedName );

	return out;
}


