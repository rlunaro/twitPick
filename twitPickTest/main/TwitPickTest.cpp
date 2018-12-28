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
 * TwitPickTest.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */

#include "catch.hpp"
#include <tuple>

#include "TestHelper.h"
#include "TwitPick.h"

TEST_CASE("TwitPickTest", "TwitPickTest")
{
	std::tuple<std::string, BearerInfo> case1
		= std::make_tuple( "{\"token_type\":\"bearer\", "
				"\"access_token\":\"AAAAAAAAAAAAAAAAAAAAABD86w"
				"AAAAAAz3vjDhzPXv8YUN7LQvSAW2dmo0g%3DdqJLDfNuX"
				"jaZzwvIj315rFWjagY8kH3u48jOp0nPCeacijb0gU\"}",
					BearerInfo("bearer","AAAAAAAAAAAAAAAAAAAAABD86wAAAAAAz3vj"
										"DhzPXv8YUN7LQvSAW2dmo0g%3DdqJLDfNuXj"
										"aZzwvIj315rFWjagY8kH3u48jOp0nPCeacij"
										"b0gU") );
	BearerInfo incorrectBearer("bearer","AAAAAAA-AAAAAAAAAABD86wAAAAAAz3vj"
											"DhzP-----7LQvSAW2dmo0g%3DdqJLDfNuXj"
											"aZzwvIj315rFWjagY8kH3u48jOp0nPCeacij"
											"b0gU");

	SECTION( "Test of getBearerFromToken")
	{
		TwitPick twitter;

		twitter.parseBearerFromContent( std::get<0>( case1 ) );
		auto result = twitter.getBearer();
		CHECK( !result.accessToken.empty() );
		CHECK( !result.tokenType.empty() );
		CHECK( result.accessToken == std::get<1>(case1).accessToken );
		CHECK( result.tokenType == std::get<1>(case1).tokenType  );
	}

	SECTION( "Simple search test, no bearer" )
	{
		TestHelper testHelper;
		TwitPick twitter;

		twitter.setCookiesFilename("cookies.txt");
		twitter.setConsumerKey( testHelper.readStringValue("consumerKey", "") );
		twitter.setConsumerSecret( testHelper.readStringValue("consumerSecret", "") );
		twitter.simpleSearch( TwitPickSearchParam("hello"));
	}


	SECTION( "Simple search test, bearer" )
	{
		TestHelper testHelper;
		TwitPick twitter;

		twitter.setCookiesFilename("cookies.txt");
		twitter.setConsumerKey( testHelper.readStringValue("consumerKey", "") );
		twitter.setConsumerSecret( testHelper.readStringValue("consumerSecret", "") );
		twitter.setBearer( std::get<1>(case1) );
		twitter.simpleSearch( TwitPickSearchParam("hello"));
	}

	SECTION( "Simple search test, incorrect bearer" )
	{
		TestHelper testHelper;
		TwitPick twitter;

		twitter.setCookiesFilename("cookies.txt");
		twitter.setConsumerKey( testHelper.readStringValue("consumerKey", "") );
		twitter.setConsumerSecret( testHelper.readStringValue("consumerSecret", "") );
		twitter.setBearer( incorrectBearer );
		twitter.simpleSearch( TwitPickSearchParam("hello"));
	}


} // TwitPickTest




