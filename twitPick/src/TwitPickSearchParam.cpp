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
 * TwitPickSearchParam.cpp
 *
 * rluna
 * Dec 13, 2018
 *
 */

#include <TwitPickSearchParam.h>

TwitPickSearchParam::TwitPickSearchParam()
: query(""),
  geocode(""),
  lang(""),
  locale(""),
  resultType( mixed ),
  count(100L),
  until(""),
  sinceId(""),
  maxId(""),
  includeEntities(false)
{

}


TwitPickSearchParam::TwitPickSearchParam( const std::string& query )
: query( query ),
  geocode(""),
  lang(""),
  locale(""),
  resultType( mixed ),
  count(100L),
  until(""),
  sinceId(""),
  maxId(""),
  includeEntities(false)
{

}


std::string TwitPickSearchParam::getResultType()
{
	switch( resultType )
	{
	case mixed:   return std::string("mixed");
	case recent:  return std::string("recent");
	case popular: return std::string("popular");
	default:      return std::string("");
	}
}



