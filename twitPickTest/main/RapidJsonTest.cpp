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
 * TestMain.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */


#include "catch.hpp"
#include <string>
#include <json.hpp>
#include <iostream>



using json = nlohmann::json;

TEST_CASE("RapidJsonTest", "RapidJsonTest")
{
	std::string test1 = R"({"token_type":"bearer",
					"access_token":"AAAAAAAAAAAAAAAAAAAAABD86wAAAAAAz3vjDhzPXv8YUN7LQvSAW2dmo0g%3DdqJLDfNuXjaZzwvIj315rFWjagY8kH3u48jOp0nPCeacijb0gU"})";

	SECTION( "Test of Reading JSON" )
	{
		// parse the result
		auto result1 = json::parse( test1 );

		// navigate through the elements
		auto resultSet = result1.find("token_type");
		CHECK( resultSet.key() == std::string("token_type") );
		CHECK( resultSet.value() == std::string("bearer") );

		auto resultSet2 = result1.find("access_token");
		CHECK( resultSet2.key() == std::string("access_token") );
		CHECK( resultSet2.value() == std::string("AAAAAAAAAAAAAAAAAAAAABD86wAAAAAAz3vjDhzPXv8YUN7LQvSAW2dmo0g%3DdqJLDfNuXjaZzwvIj315rFWjagY8kH3u48jOp0nPCeacijb0gU") );

	}

} // RapidJsonTest





