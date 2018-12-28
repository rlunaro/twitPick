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
 * HttpHeaderParser.h
 *
 * rluna
 * Jul 21, 2018
 *
 */

#ifndef HTTPHEADERPARSER_H_
#define HTTPHEADERPARSER_H_

#include <string>

/**
 * Parses a raw header and convert the values
 * into field-name and field-value.
 *
 * <p>
 * The HTTP header format
 * is defined here:
 *
 * https://tools.ietf.org/html/rfc7230#page-22
 * </p>
 * <pre>
 * Each header field consists of a case-insensitive field name followed
 * by a colon (":"), optional leading whitespace, the field value, and
 * optional trailing whitespace.
 *
 *      header-field   = field-name ":" OWS field-value OWS
 *
 *      field-name     = token
 *      field-value    = *( field-content / obs-fold )
 *      field-content  = field-vchar [ 1*( SP / HTAB ) field-vchar ]
 *      field-vchar    = VCHAR / obs-text
 *
 *      obs-fold       = CRLF 1*( SP / HTAB )
 *                     ; obsolete line folding
 *                     ; see Section 3.2.4
 *
 *      OWS            = *( SP / HTAB )
 *                     ; optional whitespace
 *
 *      token          = 1*tchar
 *
 *      tchar          = "!" / "#" / "$" / "%" / "&" / "'" / "*"
 *                     / "+" / "-" / "." / "^" / "_" / "`" / "|" / "~"
 *                     / DIGIT / ALPHA
 *                     ; any VCHAR, except delimiters
 *
 * A string of text is parsed as a single value if it is quoted using
 * double-quote marks.
 *
 *      quoted-string  = DQUOTE *( qdtext / quoted-pair ) DQUOTE
 *      qdtext         = HTAB / SP /%x21 / %x23-5B / %x5D-7E / obs-text
 *      obs-text       = %x80-FF
 *
 * Comments can be included in some HTTP header fields by surrounding
 * the comment text with parentheses.  Comments are only allowed in
 * fields containing "comment" as part of their field value definition.
 *
 *      comment        = "(" *( ctext / quoted-pair / comment ) ")"
 *      ctext          = HTAB / SP / %x21-27 / %x2A-5B / %x5D-7E / obs-text
 *
 * The backslash octet ("\") can be used as a single-octet quoting
 * mechanism within quoted-string and comment constructs.  Recipients
 * that process the value of a quoted-string MUST handle a quoted-pair
 * as if it were replaced by the octet following the backslash.
 *
 *      quoted-pair    = "\" ( HTAB / SP / VCHAR / obs-text )
 *      VCHAR	= %x21-7E	Visible (printing) characters
 *
 * </pre>
 */
class HttpHeaderParser
{
	const std::string tchar = "!#$%&'*+-.^_`|~0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string whitespace = " \t";
	std::string rawHeader;
	std::string parsedValue;
	std::string fieldName;
	std::string fieldValue;
	bool success;
	size_t position;

	bool parseRawHeader( );
	bool parseFieldName();
	bool parseSemicolon();
	bool parseOptionalWhiteSpace();
	bool parseFieldValue();
	bool parseEndOfString();
	bool parseToken();
	bool parseFieldContent();
	bool parseFolding();

	bool isVcharOrSpace( char c );

public:
	HttpHeaderParser();
	HttpHeaderParser( std::string rawHeader );
	void setRawHeader( std::string rawHeader );
	const bool isSuccess();
	const std::string getFieldName();
	const std::string getFieldValue();
};

#endif /* HTTPHEADERPARSER_H_ */
