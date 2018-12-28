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
 * FileWritter.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */

#include <string>
#include <fstream>

#include "catch.hpp"

TEST_CASE("FileWritter", "FileWritter")
{
	std::string test1 = R"(a46cd626ce30c40c74f3b7ab5fe35af03bc04cc620bcc3562b8fa55887dd50e)"
			R"(22de17ae1f8fdf12814da96c7603924c9b3fe3469f534737ee2252131d565f2)"
			R"(7694de034e695f93bf89d2da0f8be96f5c3d710d175a3ad586333e2f064db56)"
			R"(de3c7603ed13d01e0765db72b874158a36578ebdf2677665415900302d6046a)"
			R"(9c8ebf8d50738c825063294f220a4cbfed3a9b1df518ae43702f18ea5b89cd7)"
			R"(3d3cde2b93c397041f78d3fe3788e57ed44879a40733828e2e4755f691b3866)"
			R"(983ce81b0cc6f39d302c16340736ba37779533e4838b9fd53082ce8df0371a3)"
			R"(6732408aedba48617120e965f3de040c5a424484ee4df978068c9fab0713bcf)"
			R"(8ec89d3222eaca6d53f6698e6c5089c8ff2c04cb9eb1163e42f6e1150e3800b)"
			R"(2cdb2fc35123fffde4b551b4bbc1ee0a5a13720c1ece2f7ce90d9df7d13a6b5)"
			R"(3f0df87f81bbe4a7c73bb92272ffbdb38935641a763243fa894babcdefdf475)"
			R"(4979c2a2e7fa29857261f6fb9acd127)";

	SECTION("Test of writing content to a file")
	{
	  std::ofstream outFile;

	  outFile.open ("example.txt");
	  outFile << test1;
	  outFile.close();

	  std::ifstream inFile;
	  std::string test2;

	  inFile.open("example.txt");
	  inFile >> test2;
	  inFile.close();

	  CHECK( test1 == test2 );
	}
} // TemplateTest
