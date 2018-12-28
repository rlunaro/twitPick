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
 * HttpHeaderParserTest.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */

#include "catch.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <regex>

#include "HttpHeader.h"

std::string removeReturn( std::string str );

TEST_CASE("HttpHeaderTest", "HttpHeaderTest")
{
	struct TestAndResult
	{
		std::string header;
		std::string name;
		std::string value;
	};

	// list of test and results
	std::vector<TestAndResult> listOfTests =
	{{"Date: Sat, 21 Jul 2018 14:03:16 GMT","Date","Sat, 21 Jul 2018 14:03:16 GMT"},
	{"Server: Apache/2.4.18 (Ubuntu)","Server","Apache/2.4.18 (Ubuntu)"},
	{"Location: doku.php","Location","doku.php"},
	{"Content-Length: 0","Content-Length","0"},
	{"Content-Type: text/html; charset=UTF-8","Content-Type","text/html; charset=UTF-8"},
	{"Date: Sat, 21 Jul 2018 14:03:16 GMT","Date","Sat, 21 Jul 2018 14:03:16 GMT"},
	{"Server: Apache/2.4.18 (Ubuntu)","Server","Apache/2.4.18 (Ubuntu)"},
	{"Set-Cookie: DokuWiki=2hf1jtleeslbb0gh2e9m9kmnl6; path=/; secure; HttpOnly","Set-Cookie","DokuWiki=2hf1jtleeslbb0gh2e9m9kmnl6; path=/; secure; HttpOnly"},
	{"Expires-with-folding: Thu, 19 Nov 1981\r\n		 08:52:00 GMT","Expires-with-folding","Thu, 19 Nov 1981 08:52:00 GMT"},
	{"Cache-Control: no-store, no-cache, must-revalidate","Cache-Control","no-store, no-cache, must-revalidate"},
	{"Pragma: no-cache","Pragma","no-cache"},
	{"Set-Cookie: DW7fa065a06cb74b536c124cfbe56ac6d3=deleted; \r\nexpires=Thu, 01-Jan-1970 00:00:01 GMT; Max-Age=0; path=/; secure; HttpOnly","Set-Cookie","DW7fa065a06cb74b536c124cfbe56ac6d3=deleted; expires=Thu, 01-Jan-1970 00:00:01 GMT; Max-Age=0; path=/; secure; HttpOnly"},
	{"X-UA-Compatible: IE=edge,chrome=1","X-UA-Compatible","IE=edge,chrome=1"},
	{"Vary: Accept-Encoding","Vary","Accept-Encoding"},
	{"Transfer-Encoding: chunked","Transfer-Encoding","chunked"},
	{"Content-Type: text/html; charset=utf-8", "Content-Type","text/html; charset=utf-8"}};

	SECTION("toStringTest")
	{
		for( TestAndResult testCase : listOfTests )
		{
			HttpHeader header( testCase.name, testCase.value );

			std::cout << removeReturn( testCase.header ) << std::endl;
			REQUIRE( header.toString() == removeReturn( testCase.header ) );
		}
	}

} // HttpHeaderParserTest

std::string removeReturn( std::string str )
{
	std::regex ret("[\r\n\t]+");

	return std::regex_replace( str, ret, "", std::regex_constants::match_any );
}

