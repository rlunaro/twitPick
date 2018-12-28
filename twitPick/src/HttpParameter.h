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
 * PostParameter.h
 *
 * rluna
 * Nov 12, 2018
 *
 */

#ifndef HTTPPARAMETER_H_
#define HTTPPARAMETER_H_

#include <curl/curl.h>
#include <string>

class HttpParameter
{
public:
	HttpParameter( std::string name, std::string value );
	std::string getName();
	std::string getValue();
	std::string getEscapedNameValue( CURL *curlHandle );
private:
	std::string name;
	std::string value;
};

#endif /* HTTPPARAMETER_H_ */
