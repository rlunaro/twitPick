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
 * HttpHeaderParser.cpp
 *
 * rluna
 * Jul 21, 2018
 *
 */

#include "HttpHeaderParser.h"

HttpHeaderParser::HttpHeaderParser()
{
	rawHeader = "";
	success = false;
	position = 0;
}

HttpHeaderParser::HttpHeaderParser( std::string rawHeader )
{
	setRawHeader( rawHeader );
}

void HttpHeaderParser::setRawHeader( std::string rawHeader )
{
	HttpHeaderParser::rawHeader = rawHeader;
	success = parseRawHeader();
}

const bool HttpHeaderParser::isSuccess()
{
	return success;
}

const std::string HttpHeaderParser::getFieldName()
{
	return fieldName;
}

const std::string HttpHeaderParser::getFieldValue()
{
	return fieldValue;
}

bool HttpHeaderParser::parseRawHeader()
{
	position = 0;
	return parseFieldName()
		&& parseSemicolon()
		&& parseOptionalWhiteSpace()
		&& parseFieldValue()
		&& parseOptionalWhiteSpace()
		&& parseEndOfString();
}

bool HttpHeaderParser::parseFieldName()
{
	bool ret = parseToken();
	if( ret )
		fieldName = parsedValue;
	return ret;
}

bool HttpHeaderParser::parseSemicolon()
{
	parsedValue.clear();
	if( position < rawHeader.length()
	&& rawHeader[position] == ':' )
	{
		parsedValue.push_back( rawHeader[position] );
		++position;
		return true;
	}
	else
		return false;
}


bool HttpHeaderParser::parseOptionalWhiteSpace()
{
	parsedValue.clear();
	bool ok = true;
	while( position < rawHeader.length()
			&& whitespace.find( rawHeader[position] ) != std::string::npos )
	{
		parsedValue.push_back( rawHeader[position] );
		ok = true;
		++position;
	} // while

	return ok;
}

bool HttpHeaderParser::parseFieldValue()
{
	bool result1 = true;
	bool result2 = true;
	fieldValue.clear();
	while( position < rawHeader.length()
			&& (result1 || result2) )
	{
		result1 = parseFieldContent();
		if( result1 )
		{
			fieldValue += parsedValue;
		}
		result2 = parseFolding();
	}
	// field value and folding can be empty
	return true;
}

bool HttpHeaderParser::parseFieldContent()
{
	parsedValue.clear();
	bool ok = false;
	while( position < rawHeader.length()
			&& isVcharOrSpace( rawHeader[position] )  )
	{
		parsedValue.push_back( rawHeader[position] );
		ok = true;
		++position;
	} // while

	return ok;
} // parseFieldContent

/**
 * ¿is an ascii visible character or whitespace???
 */
bool HttpHeaderParser::isVcharOrSpace( char c )
{
	return (0x21 <= c && c <= 0x7e)
		|| (0x80 <= c && c <= 0xff)
		|| (c == ' ')
		|| (c == '\t');
}

bool HttpHeaderParser::parseFolding()
{
	bool ok = false;
	parsedValue.clear();
	if( position + 1 < rawHeader.length()
	&& rawHeader[position] == '\r'
	&& rawHeader[position+1] == '\n' )
	{
		parsedValue.push_back( rawHeader[position] );
		parsedValue.push_back( rawHeader[position+1] );
		position += 2;
		// parse at least one whitespace
		ok = false;
		while( position < rawHeader.length()
				&& whitespace.find( rawHeader[position] ) != std::string::npos )
		{
			parsedValue.push_back( rawHeader[position] );
			ok = true;
			++position;
		} // while
	}

	return ok;

} // parseFolding


bool HttpHeaderParser::parseEndOfString()
{
	parsedValue.clear();
	if( position == rawHeader.length() )
		return true;
	else
		return false;
}

bool HttpHeaderParser::parseToken()
{
	parsedValue.clear();
	bool ok = false;
	while( position < rawHeader.length()
			&& tchar.find( rawHeader[position] ) != std::string::npos )
	{
		parsedValue.push_back( rawHeader[position] );
		ok = true;
		++position;
	} // while

	return ok;
}

