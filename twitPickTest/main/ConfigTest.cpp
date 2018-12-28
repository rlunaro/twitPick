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
 * ConfigTest.cpp
 *
 *  Created on: May 6, 2017
 *      Author: rluna
 */


#include "catch.hpp"

#include <iostream>
#include <string>
#include <libconfig.h++>

TEST_CASE("ConfigTest", "ConfigTest")
{
	SECTION("Simple invocation")
	{
		libconfig::Config cfg;

		// trying to read a non-existent file
		try
		{
			cfg.readFile( "filenotfound" );

			CHECK( false );
		}catch( const libconfig::FileIOException &fileNotFound )
		{
			std::cerr << "File not found as expected" << std::endl;
			CHECK( true );
		}

		// trying to read an existent file
		try
		{
			cfg.readFile( "configTest.cfg" );

			CHECK( true );
		}catch( const libconfig::FileIOException &fileNotFound )
		{
			std::cerr << "Error: file not found" << std::endl;
			CHECK( false );
		}

	} // Simple invocation


	SECTION( "Simple read" )
	{
		libconfig::Config cfg;

		try
		{
			cfg.readFile( "configTest.cfg" );
			CHECK( true );

			std::string string1;
			std::string checkString1;

			cfg.lookupValue( "string1", string1 );
			cfg.lookupValue( "checkString1", checkString1 );

			CHECK( string1 == checkString1 );

		}catch( const libconfig::FileIOException &fileNotFound )
		{
			std::cerr << "Error: file not found " << fileNotFound.what() << std::endl;
			CHECK( false );
		}catch( const libconfig::ParseException &parseException )
		{
			std::cerr << "Error: parsing exception "
					  << parseException.getFile()
					  << " : "
					  << parseException.getLine()
					  << " : "
					  << parseException.getError()
					  << std::endl;
			CHECK( false );
		}
	}


	SECTION( "Complex structure" )
	{
		libconfig::Config cfg;

		try
		{
			cfg.readFile( "configTest.cfg" );
			CHECK( true );

			const libconfig::Setting& root = cfg.getRoot();

			libconfig::Setting& complex1 = root["complex1"];

			CHECK( complex1.getLength() > 0 );
			CHECK( complex1.getLength() == 2 );

			libconfig::Setting& data1 = root["complex1"][0]["data1"];

			CHECK( data1.getType() == libconfig::Setting::Type::TypeString );
			CHECK( data1.c_str() == std::string("data1 string") );

		}catch( const libconfig::FileIOException &fileNotFound )
		{
			std::cerr << "Error: file not found " << fileNotFound.what() << std::endl;
			CHECK( false );
		}catch( const libconfig::ParseException &parseException )
		{
			std::cerr << "Error: parsing exception "
					  << parseException.getFile()
					  << " : "
					  << parseException.getLine()
					  << " : "
					  << parseException.getError()
					  << std::endl;
			CHECK( false );
		}
	}


} // TemplateTest
