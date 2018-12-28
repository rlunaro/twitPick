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
 * TwitterPicker.h
 *
 * rluna
 * Jul 19, 2018
 *
 */

#ifndef CURLWRAPPER_H_
#define CURLWRAPPER_H_

#include <iostream>
#include <memory>
#include <exception>
#include <curl/curl.h>
#include <HttpParameter.h>
#include <stdarg.h>
#include <cstring>
#include <vector>

#include <stdlib.h>

#include "TwitPickException.h"
#include "EncodedUrl.h"
#include "HttpHeader.h"

/**
 * Function to get the contents of the page.
 *
 * <p>
 * In the fourth parameter I will receive a pointer
 * to this object (@see CurlWrapper) to get the
 * contents loaded back into the object. </p>
 */
size_t getContentsCallback(char *ptr,
					  size_t size,
					  size_t nmemb,
					  void *userdata);

/**
 * Function to get the contents of the headers.
 *
 */
size_t getHeaderCallback(char *buffer,
						 size_t size,
						 size_t nitems,
						 void *userdata);



class CurlWrapper
{
	/**
	 * This class will act as witness: a single static reference
	 * will be held, and once destroyed, it will make the cleanup.
	 *
	 */
	class GlobalToken
	{
		CURLcode resultOfGlobalInit;

	public:

		GlobalToken()
		{
			resultOfGlobalInit = curl_global_init( CURL_GLOBAL_ALL );
		}
		~GlobalToken()
		{
			if( resultOfGlobalInit == CURLE_OK )
				curl_global_cleanup();
		}
	};

	static GlobalToken globalToken;
	std::string curlVersion;
	CURL *curlHandle;
	char lastErrorMsg[CURL_ERROR_SIZE];
	std::string cookiesFilename;
	// to hold the list of custom request headers
	// to be injected in the execution of the call
	struct curl_slist* requestHeaderList;
	std::vector<std::string> rawResponseHeaders;
	std::vector<HttpParameter> postParameterList;
	std::string postParameterValues;
	std::vector<HttpParameter> getParameterList;
	std::string getParameterValues;
	std::string contents;

	void loadContents(char *ptr,
						  size_t size,
						  size_t nmemb);
	friend size_t getContentsCallback(char *ptr,
			  size_t size,
			  size_t nmemb,
			  void *userdata);

	void clearResponseHeaderInfo();

	void clearContentInfo();

	/**
	 * Transmit the header information to libcurl.
	 */
	void injectRequestHeaders( );

	/**
	 * Transmit the post parameters to libcurl.
	 */
	void injectPostParameters();

	void injectGetParameters();

	std::string getParameterValuesAsUrl();

	/**
	 * Called every time a line in the header is found.
	 */
	void loadHeaderInfo(char *buffer,
							size_t size,
							size_t nitems );
	friend size_t getHeaderCallback(char *buffer,
							 size_t size,
							 size_t nitems,
							 void *userdata);

	/**
	 * Wrap of the curl_easy_perform with throw to fire runtime errors.
	 */
	void easyPerform();
	/**
	 * Do the most common configurations for the http calls.
	 */
	void commonHttpConfig();

	// copy constructor is forbidden
	CurlWrapper( const CurlWrapper & source ) = delete;
	// copy assignment is forbidden
	CurlWrapper & operator=( const CurlWrapper & source ) = delete;
	// move constructor is forbidden
	CurlWrapper( CurlWrapper && source ) = delete;
	// move assignment is forbidden
	CurlWrapper& operator=( CurlWrapper && source ) = delete;

public:
	CurlWrapper();
	~CurlWrapper();

	void reset();

	/**
	 * Return all the headers in the response
	 */
	std::vector<HttpHeader> getResponseHeaders();
	/**
	 * Return the value of a specific header, or the empty string if not found
	 */
	std::string getHeaderValue( std::string headerName );

	CURL *getCurlHandle();

	EncodedUrl getEncodedUrl( std::string url );
	EncodedUrl getEncodedUrl( char *url, size_t size );

	void setCookiesFilename( const std::string& cookiesFilename );

	/**
	 * make curl to be verbose or not
	 */
	void setVerbose( bool verbose );
	/**
	 * make curl to shut off the progress or not
	 */
	void setProgress( bool progress );

	/**
	 * Adds a request to be sent in the next request.
	 *
	 * There is no removeRequestHeader method because
	 * the implementation of CURLOPT_HTTPHEADER doesn't
	 * allow the removal of a custom header: it allows
	 * the removal of internal headers, but not
	 * custom headers.
	 */
	void addRequestHeader( HttpHeader header );

	void addPostParameter( HttpParameter parameter );

	void addGetParameter( HttpParameter parameter );
	/**
	 * Do a simple http get.
	 *
	 * <p>
	 * The url is composed as follows:
	 * </p>
	 * <pre>
	 * protocol + "://" + host + "/" + path
	 * </pre>
	 */
	void httpGet( std::string protocol,
				  std::string host,
				  std::string path );

	void httpPost( std::string protocol,
				   std::string host,
				   std::string path );

	/**
	 * Return the contents downloaded from the latest method.
	 */
	std::string getContents();

	/**
	 * return last status code, if any
	 */
	long getStatusCode();
};



#endif /* CURLWRAPPER_H_ */




