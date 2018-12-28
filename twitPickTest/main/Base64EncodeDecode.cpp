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
 * Base64EncodeDecode.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */

#include <vector>
#include <string>

#include "catch.hpp"

#include "base64.h"

std::vector<std::vector<std::string>> data = {
{ "Dantur positione tres rectæ infinitæ AB, AC, BC, & oportet ita locare,",
		"RGFudHVyIHBvc2l0aW9uZSB0cmVzIHJlY3TDpiBpbmZpbml0w6YgQUIsIEFDLCBCQywgJiBvcG9ydGV0IGl0YSBsb2NhcmUs"},
{ "F lineam BC tangat. Super DE, DF & EF describe tria circulorum segmenta",
		"RiBsaW5lYW0gQkMgdGFuZ2F0LiBTdXBlciBERSwgREYgJiBFRiBkZXNjcmliZSB0cmlhIGNpcmN1bG9ydW0gc2VnbWVudGE="},
{ "a",
		"YQ=="},
{ "Agatur enim Fc ipsi (aD occurrens) in n. [Jungantur aG, [97]á´íóúbG,] PD, QD & producatur PQ",
		"QWdhdHVyIGVuaW0gRmMgaXBzaSAoYUQgb2NjdXJyZW5zKSBpbiBuLiBbSnVuZ2FudHVyIGFHLCBbOTddw6HCtMOtw7PDumJHLF0gUEQsIFFEICYgcHJvZHVjYXR1ciBQUQ=="} };


TEST_CASE("base64EncodeAndDecode", "")
{
	SECTION("base64 encode")
	{
		for( std::vector<std::string> reg : data )
			CHECK( base64_encode( reg[0] ) == reg[1] );
		for( std::vector<std::string> reg : data )
			CHECK( base64_decode( reg[1] ) == reg[0] );
	}

} // base64 encode decode
