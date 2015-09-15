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

#include "wordinfo.h"

namespace japa
{

// ------------------------------------------------------------------------ //
WordInfo::WordInfo( const wstring& word,
                    const size_t frequency ) : m_word( word ), 
                                               m_frequency( frequency )
{}

// ------------------------------------------------------------------------ //
WordInfo::WordInfo() : m_frequency( 0 )
{}

// ------------------------------------------------------------------------ //
WordInfo::~WordInfo()
{}

// ------------------------------------------------------------------------ //
wstring WordInfo::getWord() const
{
    return m_word;
}

// ------------------------------------------------------------------------ //
size_t WordInfo::getFrequency() const
{
    return m_frequency;
}

// ------------------------------------------------------------------------ //
void WordInfo::setFrequency( const size_t frequency )
{
    m_frequency = frequency;
}

// ------------------------------------------------------------------------ //
void WordInfo::addOne()
{
    m_frequency ++;
}

// ------------------------------------------------------------------------ //
void WordInfo::addSynonym( const WordInfo& syn )
{
    m_synonyms.insert( &syn );
}

// ------------------------------------------------------------------------ //
bool WordInfo::isSynonym( const WordInfo& w ) const
{
    return m_synonyms.find( &w ) != m_synonyms.end();
}

// ------------------------------------------------------------------------ //
bool WordInfo::hasSynonym() const
{
    return m_synonyms.size() > 0;
}

// ------------------------------------------------------------------------ //
const WordInfo::Synonyms& WordInfo::getSynonyms() const
{
    return m_synonyms;
}

// ------------------------------------------------------------------------ //
std::wostream& operator<<( std::wostream& out, const WordInfo& w )
{
    WordInfo::Synonyms::const_iterator iter;
    out << w.getWord() << "(" << w.getFrequency() << ") [ ";

    //Affiche les synonymes du mots
    for( iter = w.m_synonyms.begin(); iter != w.m_synonyms.end(); iter++ )
    {
        out << "`" << ( *iter ) -> getWord() << "` ";
    }

    return out << " ]";
}

}// namespace japa
