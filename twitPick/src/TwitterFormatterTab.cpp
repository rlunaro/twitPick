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

std::string TwitterFormatterTab::removeReturn( std::string str )
{
    std::string out = "";

    for( std::string::iterator itPos = str.begin(); itPos != str.end(); ++itPos )
    {
        if( *itPos != '\n'
         && *itPos != '\r' )
            out.push_back( *itPos );
    } // for

    return out;
}


void TwitterFormatterTab::printStatus( TwitterStatus status )
{
    std::cout << "id" << sep << status.id << std::endl;
    std::cout << "created" << sep << status.createdAt << std::endl;
    std::cout << "text" << sep << removeReturn( status.text ) << std::endl;
    std::cout << "source" << sep << status.source << std::endl;
    std::cout << "retweets" << sep << status.retweetCount << std::endl;
    std::cout << "lang" << sep << status.lang << std::endl;
    printUser( status.user );
    return;
}

void TwitterFormatterTab::printUser( TwitterUser user )
{
    std::cout << "user.id" << sep << user.id << std::endl;
    std::cout << "user.name" << sep << user.name << std::endl;
    std::cout << "user.screenName" << sep << user.screenName << std::endl;
    std::cout << "user.followers" << sep << user.followersCount << std::endl;
    std::cout << "user.lang" << sep << user.lang << std::endl;
    return;
}


TwitterFormatterTab::~TwitterFormatterTab()
{

}


