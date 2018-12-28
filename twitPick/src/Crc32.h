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
 * Crc32.h
 *
 * rluna
 * Dec 24, 2018
 *
 */

#ifndef CRC32_H_
#define CRC32_H_

#include <cinttypes>
#include <string>
#include <sstream>
#include <ios>
#include <iomanip>


/**
 * Yet another implementation of the CRC32 algorithm.
 *
 * It's an own implementation inspired in:
 * https://rosettacode.org/wiki/CRC-32#Implementation_2
 *
 * Warning: not entirely thread-safe: the call to
 * calculateCRCTable must be done in a mutex.
 *
 */
class Crc32
{
public:
    Crc32( std::string value = "" );
    uint32_t computeCrc( std::string value );
    std::string computeCrcAsHex( std::string value );
    std::string asHexString( uint32_t value );
private:
    static bool computedTable;
    static uint32_t table[256];
    static void calculateCRCTable() noexcept;
    std::string value;
};


#endif /* CRC32_H_ */


