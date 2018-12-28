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
 * Crc32.cpp
 *
 * rluna
 * Dec 24, 2018
 *
 */

#include "Crc32.h"

// static initialization

bool Crc32::computedTable = false;

uint32_t Crc32::table[256];

Crc32::Crc32( std::string value )
{
    if( !computedTable )
    {
        calculateCRCTable();
        computedTable = true;
    } // !computedTable
    if( !value.empty() )
    {
        computeCrc( value );
    }
}

void Crc32::calculateCRCTable() noexcept
{
    /* Calculate CRC table. */
    uint32_t rem;
    for (int i = 0; i < 256; i++) {
        rem = i;  /* remainder from polynomial division */
        for (int j = 0; j < 8; j++) {
            if (rem & 1) {
                rem >>= 1;
                rem ^= 0xedb88320;
            } else
                rem >>= 1;
        }
        Crc32::table[i] = rem;
    }

}


uint32_t Crc32::computeCrc( std::string value )
{
    uint32_t crc = 0;
    uint8_t octet;

    crc = ~crc;
    for( auto p = value.begin(); p != value.end(); ++p )
    {
        octet = *p;  /* Cast to unsigned octet */
        crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
    } // for

    return ~crc;
}

std::string Crc32::computeCrcAsHex( std::string value )
{
    return asHexString( computeCrc( value ) );
}

std::string Crc32::asHexString( uint32_t value )
{
    std::stringstream stream;

    stream << std::setfill('0')
           << std::setw( sizeof( value ) * 2 )
           << std::hex
           << value;
    return stream.str();
}







