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
 * TwitterFormatterTest.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */


#include "catch.hpp"
#include "json.hpp"
#include <string>

#include "TestHelper.h"

TEST_CASE("TwitterFormatterTest", "TwitterFormatterTest")
{
    TestHelper helper;
    std::vector<std::string> data = helper.readExampleData("TwitterFormatter.data");

    SECTION( "SimpleTest" )
    {
        CHECK( data.size() == 5 );
    }


} // TwitterFormatterTest





