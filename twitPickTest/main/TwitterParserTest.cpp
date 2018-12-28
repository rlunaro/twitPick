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
 * TwitterParserTest.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */


#include "catch.hpp"
#include "json.hpp"
#include <string>

#include "TestHelper.h"
#include "TwitterParser.h"

TEST_CASE("TwitterParserTest", "TwitterParserTest")
{
    std::string statusIds[] = {"1077474113021714432",
                            "1075795591496642562",
                            "1077299356712255489",
                            "1077521480320208896",
                            "1077521471784845315",
                            "1077521289085038592",
                            "1077521257279610880",
                            "1077521215542177792",
                            "1077521167353868288",
                            "1077520952651538437",
                            "1077520923756879872",
                            "1077520882170560512",
                            "1077520728407322625",
                            "1077520460261187584",
                            "1077520450169769984",
                            "1077520443056275456",
                            "1077520300521242625",
                            "1077520160343244800",
                            "1077520070631399424",
                            "1077519817429659648",
                            "1077519667198132226",
                            "1077519643009564672",
                            "1077519638429396992",
                            "1077519634763517952",
                            "1077519582259265537",
                            "1077519533328478208",
                            "1077519480001974272",
                            "1077519321813868545",
                            "1077519312808800256",
                            "1077519177269866496",
                            "1077519154742083586",
                            "1077519046394953728",
                            "1077518896960233473",
                            "1077518815691337728",
                            "1077518794938032128",
                            "1077518596463517696",
                            "1077518211195813888",
                            "1077518135492833281",
                            "1077518092442521600",
                            "1077518072888680448",
                            "1077517971940089856",
                            "1077517912653598720",
                            "1077517795028553728",
                            "1077517718713036800",
                            "1077517702112178177",
                            "1077517647913410562",
                            "1077517532297396224",
                            "1077517521161457670",
                            "1077517512827375617",
                            "1077517418614976512",
                            "1077517345222987776",
                            "1077517311467274241",
                            "1077517295327399936",
                            "1077517279997366272",
                            "1077517249836212224",
                            "1077517241032343553",
                            "1077517213442150402",
                            "1077517188343517184",
                            "1077517024627019777",
                            "1077516975293845504",
                            "1077516746129498112",
                            "1077516633164386304",
                            "1077516627711852544",
                            "1077516586163060738",
                            "1077516455992848386",
                            "1077516155974225921",
                            "1077516076978712576",
                            "1077516047874433026",
                            "1077515992736120832",
                            "1077515910813007873",
                            "1077515894325235712",
                            "1077515888268664832",
                            "1077515771063009281",
                            "1077515762867335168",
                            "1077515674967252992",
                            "1077515653207207936",
                            "1077515577068044289",
                            "1077515547078647809",
                            "1077515454749392896",
                            "1077515424818970625",
                            "1077515362437156864",
                            "1077515281570906113",
                            "1077515272972627971",
                            "1077515077660622848",
                            "1077514851499606017",
                            "1077514745262018561",
                            "1077514637212639232",
                            "1077514378667311104",
                            "1077514322547523586",
                            "1077514319049351168",
                            "1077514224807694337",
                            "1077514101490941957",
                            "1077513888118247431" };
    TestHelper helper;
    std::vector<std::string> data = helper.readExampleData("TwitterFormatter.data");

    SECTION( "SimpleTest" )
    {
        CHECK( data.size() == 5 );
    }

    SECTION( "Elaborated Test" )
    {
        std::string one = data[0];

        auto result = nlohmann::json::parse( one );

        std::cout << result["statuses"] << std::endl;

        std::cout << result["statuses"][0] << std::endl;

        for( auto statusLine : result["statuses"] )
            std::cout << "STATUS LINE DETECTED" << std::endl;

        nlohmann::json status = result["statuses"][0];

        std::cout << "creation: " << status["created_at"] << std::endl;
        std::cout << "status id: " << status["id"] << std::endl;
        std::cout << "text: " << status["text"] << std::endl;
        std::cout << "source: " << status["source"] << std::endl;
        std::cout << "retweet count: " << status["retweet_count"] << std::endl;
        std::cout << "lang: " << status["lang"] << std::endl;

        nlohmann::json user = status["user"];
        std::cout << "user.id: " << user["id"] << std::endl;
        std::cout << "user.name: " << user["name"] << std::endl;
        std::cout << "user.screen_name: " << user["screen_name"] << std::endl;
        std::cout << "user.followers_count: " << user["followers_count"] << std::endl;
        std::cout << "user.lang: " << user["lang"] << std::endl;

        // check whether is a "retweeted_status" with the full text
        if( status["truncated"] == "true" && status["retweeted_status"].is_string() )
        {
            nlohmann::json retweeted_status = status["retweeted_status"];
            std::cout << "full text: " << retweeted_status["text"];
        }

    }

    SECTION( "Simple Test 2" )
    {
        TwitterParser twitterParser( data[0] );

        int nCheck = 0;
        while( twitterParser.isNextStatus() )
        {
            TwitterStatus status = twitterParser.next();
            std::cout << "status: " << status.id << std::endl;
            CHECK( status.id == statusIds[nCheck] );
            ++nCheck;
        }
    }

} // TwitterParserTest





