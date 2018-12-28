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
 * TestHelper.cpp
 *
 * rluna
 * Dec 8, 2018
 *
 */

#include "TestHelper.h"

std::string TestHelper::readStringValue( const std::string& key,
										 const std::string& defaultValue )
{
	libconfig::Config cfg;
	std::string out = defaultValue;

	try
	{
		cfg.readFile( "config.cfg" );

		try
		{
			cfg.lookupValue( key, out );
		}catch( const libconfig::SettingNotFoundException &settingNotFound )
		{
			std::cerr << "Setting not found: " << settingNotFound.getPath() << std::endl;
		}

	}catch( const libconfig::FileIOException &fileNotFound )
	{
		std::cerr << "Error: file not found " << fileNotFound.what() << std::endl;
	}catch( const libconfig::ParseException &parseException )
	{
		std::cerr << "Error: parsing exception "
				  << parseException.getFile()
				  << " : "
				  << parseException.getLine()
				  << " : "
				  << parseException.getError()
				  << std::endl;
	}

	return out;

}


std::vector<std::string> TestHelper::readExampleData( std::string filename )
{
    std::vector<std::string> result;
    std::string line;

    std::ifstream dataFile("TwitterFormatter.data");

    if( dataFile.is_open() )
    {
        while( getline( dataFile, line ) )
        {
            result.push_back( line );
        } // while
    }

    return result;
}

