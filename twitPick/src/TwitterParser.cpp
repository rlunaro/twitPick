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
 * TwitterParser.cpp
 *
 * rluna
 * Dec 27, 2018
 *
 */

#include <TwitterParser.h>

TwitterParser::TwitterParser( std::string statusesLine )
{
    parse( statusesLine );
}

void TwitterParser::parse( std::string statusesLine )
{
    // traverse all the status
    auto twitterJson = nlohmann::json::parse( statusesLine );

    statuses.clear();
    for( nlohmann::json statusLine : twitterJson["statuses"] )
    {
        TwitterStatus status;
        status = parseSingleStatus( statusLine );
        statuses.push_back( status );
    }
    statusesIt = statuses.begin();

}

TwitterStatus TwitterParser::parseSingleStatus( nlohmann::json statusLine )
{
    TwitterStatus status;
    status.createdAt = statusLine["created_at"];
    status.id = statusLine["id_str"];
    status.text = statusLine["full_text"];
    status.source = statusLine["source"];
    status.retweetCount = statusLine["retweet_count"];
    status.lang = statusLine["lang"];
    status.user = parseSingleUser( statusLine["user"] );
    return status;
} // parseSingleStatus

TwitterUser TwitterParser::parseSingleUser( nlohmann::json userLine )
{
    TwitterUser user;

    user.id = userLine["id_str"];
    user.name = userLine["name"];
    user.screenName = userLine["screen_name"];
    user.followersCount = userLine["followers_count"];
    user.lang = userLine["lang"];

    return user;
} // parseSingleUser

std::vector<TwitterStatus> TwitterParser::getStatuses()
{
    return statuses;
}

bool TwitterParser::isNextStatus() const
{
    return statusesIt != statuses.end();
}

TwitterStatus TwitterParser::next()
{
    TwitterStatus nextStatus = *statusesIt;
    statusesIt++;
    return nextStatus;
}



