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
 * TwitPick.cpp
 *
 * rluna
 * Nov 8, 2018
 *
 */

#include <TwitPick.h>

TwitPick::TwitPick() : encodedConsumerKeySecret(""), lastStatusCode(0L)
{
}

void TwitPick::setCookiesFilename( const std::string& filename )
{
	TwitPick::cookiesFilename = filename;
	curlWrapper.setCookiesFilename( filename );
}

void TwitPick::simpleSearch( TwitPickSearchParam params  )
{
	int tries = 0;

	while( tries < 2 )
	{
		bool ok = thereIsABearer();
		if( !ok )
		{
			requestNewBearer();
			if( lastStatusCode == 200L )
				ok = true;
		}
		if( ok )
		{
			performSearch( params );
			if( lastStatusCode == 401 )
			{
				// the current bearer has become invalid
				bearer = BearerInfo();
				// let's try it again
			}
			else
				break;
		}
		tries++;
	} // while

}

std::string TwitPick::getLastSearchResult()
{
    return lastSearchResult;
}

bool TwitPick::thereIsABearer()
{
	return !bearer.accessToken.empty();
}

/**
 * Use the twitter API to request a new bearer.
 */
void TwitPick::requestNewBearer()
{
	curlWrapper.reset();
	// encode consumer key and secret into a specially encoded set of credentials
	std::string encodedConsumerKey = encodeConsumerKeySecret( );

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
	lastStatusCode = curlWrapper.getStatusCode();

	if( lastStatusCode == 200L )
	{
		// get the content of the file to get the gearer token
		std::string postContent = curlWrapper.getContents();
		parseBearerFromContent( postContent );
	}
	else
		throw TwitPickException("Error getting bearer",
								curlWrapper.getContents().c_str());
} // requestNewBearer

/**
 * Performs a search using the bearer the class currently has.
 *
 */
void TwitPick::performSearch( TwitPickSearchParam params )
{
	curlWrapper.reset(); // start another request
	curlWrapper.addRequestHeader( HttpHeader("Authorization", std::string("Bearer ") + bearer.accessToken ) );
	addQueryParameters( params );
	curlWrapper.httpGet( "https", "api.twitter.com", "1.1/search/tweets.json" );
	lastStatusCode = curlWrapper.getStatusCode();
	lastSearchResult = curlWrapper.getContents();
}

void TwitPick::addQueryParameters( TwitPickSearchParam params )
{
	curlWrapper.addGetParameter( HttpParameter("q", params.query.c_str() ) );
	if( !params.geocode.empty() )
		curlWrapper.addGetParameter( HttpParameter("geocode", params.geocode.c_str() ) );
	if( !params.lang.empty() )
		curlWrapper.addGetParameter( HttpParameter("lang", params.lang.c_str() ) );
	if( !params.locale.empty() )
		curlWrapper.addGetParameter( HttpParameter("locale", params.locale.c_str() ) );
	curlWrapper.addGetParameter( HttpParameter("result_type", params.getResultType() ) );
	if( params.count != 0 )
		curlWrapper.addGetParameter( HttpParameter("count", std::to_string( params.count ) ) );
	if( !params.until.empty() )
		curlWrapper.addGetParameter( HttpParameter("until", params.until ) );
	if( !params.sinceId.empty() )
		curlWrapper.addGetParameter( HttpParameter("since_id", params.sinceId ) );
	if( !params.maxId.empty() )
		curlWrapper.addGetParameter( HttpParameter("max_id", params.maxId ) );
	if( params.includeEntities )
		curlWrapper.addGetParameter( HttpParameter("include_entities", "true" ) );
	else
		curlWrapper.addGetParameter( HttpParameter("include_entities", "false" ) );
}

void TwitPick::setConsumerKey( const std::string& consumerKey )
{
	TwitPick::consumerKey = consumerKey;
}

void TwitPick::setConsumerSecret( const std::string& consumerSecret )
{
	TwitPick::consumerSecret = consumerSecret;
}

std::string TwitPick::encodeConsumerKeySecret()
{
	std::string urlEncodedConsumerKey = urlEncode( consumerKey );
	std::string urlEncodedConsumerSecret = urlEncode( consumerSecret );

    std::string concatenatedKeySecret = urlEncodedConsumerKey
    									+ ":"
										+ urlEncodedConsumerSecret;

    std::string base64EncodedString = base64Encode( concatenatedKeySecret );

    encodedConsumerKeySecret = base64EncodedString;

    return encodedConsumerKeySecret;
}

void TwitPick::parseBearerFromContent( std::string content )
{
	try
	{
		auto json = nlohmann::json::parse( content );
		auto tokenType = json.find("token_type");
		bearer.tokenType = tokenType.value();
		auto accessToken = json.find("access_token");
		bearer.accessToken = accessToken.value();

	}catch( const std::exception & ex )
	{
		// do nothing, in that case it will return
		// a bearerInfo empty
	}
}


BearerInfo TwitPick::getBearer()
{
	return bearer;
}

void TwitPick::setBearer( const BearerInfo& bearer )
{
	TwitPick::bearer = bearer;
}


std::string TwitPick::urlEncode( std::string urlData )
{
	return urlData;
}

std::string TwitPick::base64Encode( std::string str )
{
	return base64_encode( str );
}

