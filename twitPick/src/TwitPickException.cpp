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
 * TwitPickException.cpp
 *
 * rluna
 * Nov 9, 2018
 *
 */

#include <TwitPickException.h>

TwitPickException::TwitPickException()
{
	what = "Exception in library TwitPick";
	details = "";
}

TwitPickException::TwitPickException( const std::string& what )
{
	TwitPickException::what = what;
}

TwitPickException::TwitPickException( const std::string& what,
								      const std::string& details )
{
	TwitPickException::what = what;
	TwitPickException::details = details;
}

const char *TwitPickException::getWhat() const throw()
{
	return what.c_str();
}

const char *TwitPickException::getDetails() const throw()
{
	return details.c_str();
}
