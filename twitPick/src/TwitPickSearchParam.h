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
 * TwitPickSearchParam.h
 *
 * rluna
 * Dec 13, 2018
 *
 */

#ifndef TWITPICKSEARCHPARAM_H_
#define TWITPICKSEARCHPARAM_H_

#include <string>


enum ResultType
{
	mixed,
	recent,
	popular
};

/**
 * Twitter search parameters.
 *
 * The description of this parameters can be found at:
 *
 * https://developer.twitter.com/en/docs/tweets/search/api-reference/get-search-tweets.html
 *
 */
struct TwitPickSearchParam
{
	std::string query;
	std::string geocode;
	std::string lang;
	std::string locale;
	ResultType resultType;
	long count;
	std::string until;
	std::string sinceId;
	std::string maxId;
	bool includeEntities;

	TwitPickSearchParam();
	TwitPickSearchParam( const std::string& query );

	std::string getResultType();
};

#endif /* TWITPICKSEARCHPARAM_H_ */
