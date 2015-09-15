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

#include "bitextsynonymcontainer.h"

namespace japa
{

// ------------------------------------------------------------------------ //
BitextSynonymContainer::BitextSynonymContainer( TextDictionary& sourceDict, 
        TextDictionary& targetDict ) 
        : m_sourceDict( sourceDict ), m_targetDict( targetDict )
{
}

// ------------------------------------------------------------------------ //
BitextSynonymContainer::~BitextSynonymContainer()
{}

// ------------------------------------------------------------------------ //
void BitextSynonymContainer::addSynonyms( wstring& word1, wstring& word2 )
{
    wstring w1( Text::prepareWord( word1 ) );
    wstring w2( Text::prepareWord( word2 ) );
	//UTF8::String w1( Text::prepareWord( word1 ) );
	//UTF8::String w2( Text::prepareWord( word2 ) );
    TextDictionary::iterator iter1;
    TextDictionary::iterator iter2;

    iter1 = m_sourceDict.find( w1 );
    iter2 = m_targetDict.find( w2 );

    if( iter1 != m_sourceDict.end() && iter2 != m_targetDict.end() )
    {
        // Les mots sont pr�sents dans les textes, l'ajout est donc pertinent
        ( iter1 -> second ).addSynonym( iter2 -> second );
    } 
}

}// namespace japa
