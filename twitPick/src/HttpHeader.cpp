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
 * HttpHeader.cpp
 *
 * rluna
 * Jul 20, 2018
 *
 */

#include "HttpHeader.h"

HttpHeader::HttpHeader()
{
	name = "";
	value = "";
	success = false;

} // HttpHeader

HttpHeader::HttpHeader( std::string rawHeader )
{
	name = "";
	value = "";
	success = false;
	parse( rawHeader );
} // HttpHeader


HttpHeader::HttpHeader( std::string name, std::string value )
{
	HttpHeader::name = name;
	HttpHeader::value = value;
	success = true;
}

void HttpHeader::parse( std::string rawHeader)
{
	HttpHeaderParser parser( rawHeader );

	if( parser.isSuccess() )
	{
		name = parser.getFieldName();
		value = parser.getFieldValue();
		success = true;
	}
} // parse

const std::string HttpHeader::getName()
{
	return name;
}

const std::string HttpHeader::getValue()
{
	return value;
}

const bool HttpHeader::isSuccess()
{
	return success;
}

bool HttpHeader::operator == (const HttpHeader& elem) const
{
	return name == elem.name
	    && value == elem.value
		&& success == elem.success;
}

bool HttpHeader::operator != (const HttpHeader& elem) const
{
	return name != elem.name
	    || value != elem.value
		|| success != elem.success;

}

const std::string HttpHeader::toString() const
{
	return name + ": " + value;
}






