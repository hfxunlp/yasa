/*

Copyright 2013 RALI

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/  

using namespace std;

#include <algorithm>
#include "cognatevalidator.h"
#include "toolbox.h"


namespace japa
{

// ------------------------------------------------------------------------ //
CognateValidator::CognateValidator( size_t minLength )
        : m_minLength( minLength ) 
{}

// ------------------------------------------------------------------------ //
bool CognateValidator::operator()( const WordInfo& data )
{
    bool valid = false; 

    wstring w = data.getWord();
        
    if( w.size() < getMinLength() )
    {
        valid = !isAlphabetic( w );
    }
    else
    {
        valid = true;
    }

    return valid;
}

// ------------------------------------------------------------------------ //
void CognateValidator::setMinLength( const size_t length )
{
    m_minLength = length;
}

// ------------------------------------------------------------------------ //
size_t CognateValidator::getMinLength() const
{
    return m_minLength;
}

}// namespace japa
