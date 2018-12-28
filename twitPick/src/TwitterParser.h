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
 * TwitterParser.h
 *
 * rluna
 * Dec 27, 2018
 *
 */

#ifndef TWITTERPARSER_H_
#define TWITTERPARSER_H_

#include <string>
#include "json.hpp"
#include <vector>

struct TwitterUser
{
    std::string id;
    std::string name;
    std::string screenName;
    long long followersCount;
    std::string lang;
};

struct TwitterStatus
{
    std::string createdAt;
    std::string id;
    std::string text;
    std::string source;
    long long retweetCount;
    std::string lang;
    TwitterUser user;
};

class TwitterParser
{
private:
    std::vector<TwitterStatus> statuses;
    std::vector<TwitterStatus>::iterator statusesIt;

    TwitterStatus parseSingleStatus( nlohmann::json statusLine );
    TwitterUser parseSingleUser( nlohmann::json userLine );

public:
    TwitterParser( std::string statusesLine );
    void parse( std::string statusesLine );
    std::vector<TwitterStatus> getStatuses();
    bool isNextStatus() const;
    TwitterStatus next();
};

#endif /* TWITTERPARSER_H_ */
