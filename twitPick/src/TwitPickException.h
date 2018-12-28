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
 * TwitPickException.h
 *
 * rluna
 * Nov 9, 2018
 *
 */

#ifndef TWITPICKEXCEPTION_H_
#define TWITPICKEXCEPTION_H_

#include <exception>
#include <string>

class TwitPickException : public std::exception
{
	std::string what;
	std::string details;

public:
	TwitPickException();
	TwitPickException( const std::string& what );
	TwitPickException( const std::string& what,
					   const std::string& details );

	const char *getWhat() const throw();
	const char *getDetails() const throw();
};

#endif /* TWITPICKEXCEPTION_H_ */
