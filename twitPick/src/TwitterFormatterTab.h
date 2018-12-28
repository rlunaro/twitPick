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
 * TwitterFormatterTab.h
 *
 * rluna
 * Dec 26, 2018
 *
 */

#ifndef TWITTERFORMATTERTAB_H_
#define TWITTERFORMATTERTAB_H_

#include <iostream>

#include <TwitterParser.h>
#include <TwitterFormatter.h>

class TwitterFormatterTab: public virtual TwitterFormatter
{
private:
    void printStatus( TwitterStatus status );
    void printUser( TwitterUser user );
public:
    TwitterFormatterTab();
    void print( std::string value );
    ~TwitterFormatterTab();
};

#endif /* TWITTERFORMATTERTAB_H_ */
