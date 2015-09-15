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

#include "cognatessvalidator.h"

namespace japa
{

// ------------------------------------------------------------------------ //
CognateSSValidator::CognateSSValidator( const size_t maxFrequency )
        : m_maxFrequency( maxFrequency )
{}

// ------------------------------------------------------------------------ //
CognateSSValidator::~CognateSSValidator()
{}

// ------------------------------------------------------------------------ //
bool CognateSSValidator::operator()( const WordInfo& data )
{
    bool valid = false;
    size_t freq = 0;
    const WordInfo::Synonyms& syn = data.getSynonyms();
    WordInfo::Synonyms::const_iterator iter; 

    if( data.getFrequency() <= getMaxFrequency() )
    {
        for( iter = syn.begin(); iter != syn.end(); iter++ )
        {
            freq += ( *iter ) -> getFrequency();
        }

        valid = ( freq <= getMaxFrequency() );
    }

    return valid;
}

// ------------------------------------------------------------------------ //
void CognateSSValidator::setMaxFrequency( const size_t frequency )
{
    m_maxFrequency = frequency;
}

// ------------------------------------------------------------------------ //
size_t CognateSSValidator::getMaxFrequency() const
{
    return m_maxFrequency;
}

}// namespace japa
