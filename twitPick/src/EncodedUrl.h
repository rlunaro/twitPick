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
 * EncodedUrl.h
 *
 * rluna
 * Jul 20, 2018
 *
 */

#ifndef ENCODEDURL_H_
#define ENCODEDURL_H_


#include <string>
#include <curl/curl.h>

class EncodedUrl
{
	char *escapedUrl;

public:
	EncodedUrl( CURL *curlHandle, std::string url );
	EncodedUrl( CURL *curlHandle, char *url, size_t size );
	~EncodedUrl();
	char *getUrlEncoded();
};

#endif /* ENCODEDURL_H_ */
