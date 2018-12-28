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
 * CurlWrapperTest.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */


#include "catch.hpp"
#include <list>
#include <libconfig.h++>
#include <sstream>

#include "Crc32.h"
#include "TestHelper.h"
#include "CurlWrapper.h"
#include "TwitPick.h"

TEST_CASE("CurlWrapperTest", "CurlWrapperTest")
{
	SECTION("Simple test", "a very simple test")
	{
		CurlWrapper curlWrapper;

		curlWrapper.httpGet( "http", "example.com", "/" );

		CHECK( curlWrapper.getContents().find("Example Domain") != std::string::npos );
		CHECK( curlWrapper.getContents().find("established to be used for illustrative examples") != std::string::npos );

	}


	SECTION("Headers request", "Perform a request with headers")
	{
		CurlWrapper curlWrapper;

		std::list<HttpHeader> headers;
		headers.push_back( HttpHeader("cabecera1", "valor1") );
		headers.push_back( HttpHeader("cabecera2", "valor2") );
		for( HttpHeader header : headers )
		{
			curlWrapper.addRequestHeader( header );
		}
		curlWrapper.httpGet( "http", "www.xhaus.com", "headers" );
		curlWrapper.httpGet( "http", "www.xhaus.com", "headers" );

		CHECK( curlWrapper.getContents().find("Cabecera1") != std::string::npos );
		CHECK( curlWrapper.getContents().find("Cabecera2") != std::string::npos );

	}

    /**
     * Check that the contents get by two consecutive get or post
     * doesn't accumulate.
     *
     */
    SECTION("Non cumulative contents")
    {
        CurlWrapper curlWrapper;
        Crc32 crc;

        curlWrapper.httpGet( "https", "www.fomento.gob.es", "salidapuestasol/1996/Coruna-1996.txt" );
        curlWrapper.httpGet( "https", "www.fomento.gob.es", "salidapuestasol/1997/Oviedo-1997.txt" );

        CHECK( crc.computeCrcAsHex( curlWrapper.getContents() ) == "8c847899" );

    }

	SECTION("Download big content")
	{
	    CurlWrapper curlWrapper;
	    Crc32 crc;
	    // we have the crc32 of the content to be downloaded
	    // previously calculated
	    std::string contentCrc32 = "91d4de87";

	    // download Philosophiae Naturalis Principia Mathematica
	    curlWrapper.httpGet( "https", "www.gutenberg.org", "cache/epub/28233/pg28233.txt" );

	    CHECK( crc.computeCrcAsHex( curlWrapper.getContents() ) == contentCrc32 );
	}

	SECTION("TwitterTest", "")
	{
		TwitPick twitter;
		CurlWrapper curlWrapper;
		TestHelper testHelper;

		// Instructions in https://developer.twitter.com/en/docs/basics/authentication/overview/application-only
		// get the consumer key and secret
		twitter.setConsumerKey( testHelper.readStringValue("consumerKey", "") );
		twitter.setConsumerSecret( testHelper.readStringValue("consumerSecret", "") );
		// recover the bearer if it exists
		twitter.setBearer( BearerInfo("bearer","AAAAAAAAAAAAAAAAAAAAABD86wAAAAAAz3vj"
										"DhzPXv8YUN7LQvSAW2dmo0g%3DdqJLDfNuXj"
										"aZzwvIj315rFWjagY8kH3u48jOp0nPCeacij"
										"b0gU") );

		bool isThereBearer = false;
		if( twitter.getBearer().accessToken.empty() )
		{
			// encode consumer key and secret into a specially encoded set of credentials
			std::string encodedConsumerKey = twitter.encodeConsumerKeySecret( );
			// use the credentials get in the last point to
			// get a bearer token using this endpoint.
			//	- The request must include an Authorization header with the value of Basic <base64 encoded value from step 1>.
			//  - The request must include a Content-Type header with the value of application/x-www-form-urlencoded;charset=UTF-8.
			//  - The body of the request must be grant_type=client_credentials.
			std::string authorizationHeader = "Basic " + encodedConsumerKey;
			curlWrapper.addRequestHeader( HttpHeader( "Authorization", authorizationHeader.c_str() ) );
			curlWrapper.addRequestHeader( HttpHeader( "Content-Type", "application/x-www-form-urlencoded;charset=UTF-8" ) );
			curlWrapper.addPostParameter( HttpParameter( "grant_type", "client_credentials" ) );
			curlWrapper.httpPost( "https", "api.twitter.com", "oauth2/token" );

			if( curlWrapper.getStatusCode() == 200L )
			{
				// get the content of the file to get the gearer token
				std::string postContent = curlWrapper.getContents();
				twitter.parseBearerFromContent( postContent );
				isThereBearer = true;
			}
			else
				isThereBearer = false;
		} // ! twitter.getBearer()....empty()
		else
			isThereBearer = true;

		// to follow, the status must be 200 (OK)
		if( isThereBearer )
		{
			// use the bearer token to authenticate in this call
			curlWrapper.reset(); // start another request
			curlWrapper.addRequestHeader( HttpHeader("Authorization", std::string("Bearer ") + twitter.getBearer().accessToken ) );
			curlWrapper.addGetParameter( HttpParameter("q", "#example") );
			curlWrapper.addGetParameter( HttpParameter("result_type", "recent") );
			curlWrapper.addGetParameter( HttpParameter("count", "100") );
			curlWrapper.addGetParameter( HttpParameter("include_entities", "true") );
			curlWrapper.httpGet( "https", "api.twitter.com", "1.1/search/tweets.json" );
			// THE RESPONSE CAN BE STATUS 401 , WHICH
			// PROBABLY MEANS THAT THE BEARER IS NO
			// LONGER VALID
			// if( curlWrapper.getStatusCode() == 401 )
				// RENEGOTIATE BEARER
		}

		// save the bearer into a file for later re-use

	}
} // CurlWrapperTest



