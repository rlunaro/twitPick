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
 * TestHelper.h
 *
 * rluna
 * Dec 8, 2018
 *
 */

#ifndef TESTHELPER_H_
#define TESTHELPER_H_

#include <string>
#include <vector>
#include <libconfig.h++>
#include <iostream>
#include <fstream>

/**
 * Class for help in making the tests: saving/restoring information
 * to/from filenames.
 *
 */
class TestHelper
{
public:
	std::string readStringValue( const std::string& key,
								 const std::string& defaultValue );
	std::vector<std::string> readExampleData( std::string filename );

};



#endif /* TESTHELPER_H_ */
