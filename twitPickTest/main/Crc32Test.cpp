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
 * Crc32Test.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */


#include <iostream>
#include "catch.hpp"
#include <tuple>
#include <vector>

#include "Crc32.h"

TEST_CASE("Crc32Test", "Crc32Test")
{
    std::vector<std::tuple<std::string,std::string>> testValues =
    {{ "The quick brown fox jumps over the lazy dog", "414fa339" },
    { "Muchos años después, frente al pelotón de fusilamiento, el coronel Aureliano Buendía había de recordar aquella tarde remota en que su padre lo llevó a conocer el hielo.", "9ae50acc" },
    { "Macondo era entonces una aldea de veinte casas de barro y cañabrava construidas a la orilla de un río de aguas diáfanas que se precipitaban por un lecho de piedras pulidas, blancas y enormes como huevos prehistóricos.", "4b15b383" },
    { "El mundo era tan reciente, que muchas cosas carecían de nombre, y para mencionarlas había que señalarías con el dedo.", "9dcff922" }
    };

	SECTION("Simple creation")
    {
	    Crc32 crc1;
	    Crc32 crc2;

	    // traverse the test values
	    for( auto it : testValues )
	    {
	        CHECK( crc1.asHexString( crc1.computeCrc( std::get<0>(it) ) )
	                == std::get<1>(it) );
	    }

	    std::cout << crc1.asHexString(
	                crc1.computeCrc( std::string("The quick brown fox jumps over the lazy dog"))) << std::endl;
    }


} // Crc32Test
