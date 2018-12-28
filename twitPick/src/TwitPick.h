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
 * TwitPick.h
 *
 * rluna
 * Nov 8, 2018
 *
 */

#ifndef TWITPICK_H_
#define TWITPICK_H_

#include <string>
#include <json.hpp>
#include <exception>
#include <fstream>

#include "CurlWrapper.h"
#include "base64.h"
#include "BearerInfo.h"
#include "TwitPickSearchParam.h"

class TwitPick
{
	CurlWrapper curlWrapper;
	std::string cookiesFilename;
	std::string consumerKey;
	std::string consumerSecret;
	std::string encodedConsumerKeySecret;
	BearerInfo bearer;
	long lastStatusCode;
	std::string lastSearchResult;

    /**
     * Use the twitter API to request a new bearer.
     *
     * @throw TwitPickException In the case that the
     *     api refuses to autentify because of bad consumerKey/secret
     *     or network problems
     */
    void requestNewBearer();

    /**
     * Performs a search using the bearer the class currently has.
     *
     */
    void performSearch( TwitPickSearchParam params  );

public:

	TwitPick();

	void setCookiesFilename( const std::string& filename );
	// IMPORTANT: you must provide the proper values here
	// for get a new consumerKey/consumerSecret, you must
	// first register yourself as a twitter developer in:
	// https://developer.twitter.com/en/apply-for-access
	// and then register a new application in
	// https://developer.twitter.com/en/apps
	void setConsumerKey( const std::string& consumerKey );
	void setConsumerSecret( const std::string& consumerSecret );

	/**
	 * Make a search, autentifying itself if necessary and
	 * requesting a new Bearer if necessary.
	 *
	 * START HERE IF YOU ARE NOT SURE WHERE TO START.
	 *
	 * The results of the search..... ¿where are they stored?
	 */
	void simpleSearch( TwitPickSearchParam params );

	/**
	 * Return the contents of the last search.
	 */
	std::string getLastSearchResult();

	/**
	 * Create a encode of the consumer key and secret
	 * to authenticate with twitter.
	 *
	 * The description of the steps followed in this
	 * function are detailed in:
	 *
	 * https://developer.twitter.com/en/docs/basics/authentication/overview/application-only
	 *
	 */
	std::string encodeConsumerKeySecret();

	/**
	 * Parse the bearer from the content
	 */
	void parseBearerFromContent( std::string content );

	/**
	 * Return the bearer information if exists, or an empty bearer info.
	 *
	 */
	BearerInfo getBearer();
	/**
	 * Set the bearer information.
	 */
	void setBearer( const BearerInfo& bearer );

private:
	/**
	 * Applies rfc1738 to the input data.
	 *
	 * This step is needed to encode the consumer key
	 * and secret, and it's documented in:
	 *
	 * http://www.ietf.org/rfc/rfc1738.txt
	 *
	 * By now (07/11/2018), the consumer key and
	 * secret are encoded by default in a form
	 * that they don't need a real urlEncoding.
	 */
	std::string urlEncode( std::string urlData );

	std::string base64Encode( std::string str );

	/**
	 * Return true if there is a bearer, and false otherwise.
	 *
	 * Note: it doesn't check if the bearer is valid or not.
	 */
	bool thereIsABearer();

	/**
	 * Add query parameters to the current query that is
	 * performed.
	 */
	void addQueryParameters( TwitPickSearchParam params );

};

#endif /* TWITPICK_H_ */
