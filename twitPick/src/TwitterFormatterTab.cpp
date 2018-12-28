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
 * TwitterFormatterTab.cpp
 *
 * rluna
 * Dec 26, 2018
 *
 */

#include <TwitterFormatterTab.h>

TwitterFormatterTab::TwitterFormatterTab()
{

}

void TwitterFormatterTab::print( std::string value )
{
    TwitterParser parser( value );

    while( parser.isNextStatus() )
    {
        TwitterStatus status = parser.next();
        printStatus( status );
    }
}

void TwitterFormatterTab::printStatus( TwitterStatus status )
{
    std::cout << "id: " << status.id << std::endl;
    std::cout << "created: " << status.createdAt << std::endl;
    std::cout << "text: " << status.text << std::endl;
    std::cout << "source: " << status.source << std::endl;
    std::cout << "retweets: " << status.retweetCount << std::endl;
    std::cout << "lang: " << status.lang << std::endl;
    printUser( status.user );
    return;
}

void TwitterFormatterTab::printUser( TwitterUser user )
{
    std::cout << "user.id: " << user.id << std::endl;
    std::cout << "user.name: " << user.name << std::endl;
    std::cout << "user.screenName: " << user.screenName << std::endl;
    std::cout << "user.followers: " << user.followersCount << std::endl;
    std::cout << "user.lang: " << user.lang << std::endl;
    return;
}


TwitterFormatterTab::~TwitterFormatterTab()
{

}


