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

#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "text.h"
#include "toolbox.h"

namespace japa
{

// ------------------------------------------------------------------------ //
Text::Text()
{}

// ------------------------------------------------------------------------ //
Text::~Text()
{}

// ------------------------------------------------------------------------ //
TextDictionary& Text::getDictionary() 
{
    return m_dictionary;
}

// ------------------------------------------------------------------------ //
WordInfo& Text::getWord( const size_t indice ) const
{
    return *m_words[ indice ];
}

// ------------------------------------------------------------------------ //
size_t Text::getWordCount() const
{
    return m_words.size();
}

// ------------------------------------------------------------------------ //
size_t Text::getSentenceLength( const size_t indice ) const
{
    size_t length = 0;

    if( indice < m_sentences.size() )
    {
        length = m_sentencesLength[ indice ];
    }

    return length;
}

// ------------------------------------------------------------------------ //
size_t Text::getSentenceCount() const
{
    return m_sentences.size();
}

// ------------------------------------------------------------------------ //
size_t Text::getSentenceWordCount( const size_t indice ) const
{
    size_t wc = 0;
    
    if( indice < m_sentences.size() - 1 )
    {
        wc = m_sentences[ indice + 1 ] - m_sentences[ indice ];
    }
    else if( indice == m_sentences.size() - 1 )
    {
        wc = m_words.size() - m_sentences[ indice ];
    }

    return wc;
}

// ------------------------------------------------------------------------ //
void Text::getSentenceBounds( const size_t indice, size_t& begin, 
                              size_t& end ) const
{
    if( indice < m_sentences.size() )
    {
        begin = m_sentences[ indice ];

        if( indice == m_sentences.size() - 1 )
        {
            end = m_words.size();
        }
        else
        {
            end = m_sentences[ indice + 1 ];
        }
    }
}

// ------------------------------------------------------------------------ //
size_t Text::getSentenceIndice( const size_t wordIndice ) const
{
    size_t min = 0;
    size_t max = m_sentences.size();
    size_t mid = 0;
    
    // Recherche dichotomique dans le vecteur
    while( min != max )
    {
        mid = ( max + min ) / 2;

        if( wordIndice > m_sentences[ mid ] )
        {
            min = mid + 1;
        }
        else
        {
            max = mid;
        }
    }

    if( m_sentences[ min ] != wordIndice )
    {
        min--;
    }

    return min;
}

// ------------------------------------------------------------------------ //
wstring Text::getSentenceID( const size_t indice ) const
{
    wstring id;

    if( indice < m_sentencesID.size() )
    {
        id = m_sentencesID[ indice ];
    }

    return id;
}

// ------------------------------------------------------------------------ //
wstring Text::prepareWord( wstring& word )
{
    stripAccents( word );
    toUpperCase( word );
    return word;
}

// ------------------------------------------------------------------------ //
void Text::pushWord( wstring& word )
{
	//wcout<< "Le mot est "<< word << endl;
    wstring w = prepareWord( word );

    //wcout<< "Le mot apres preparation est "<< w << endl;
    m_words.push_back( indexWord( w ) );
    m_sentencesLength.back() += w.size();
}

// ------------------------------------------------------------------------ //
void Text::pushSentence( const wstring& id )
{
    m_sentences.push_back( m_words.size() );
    m_sentencesLength.push_back( 0 );
    m_sentencesID.push_back( id );
}

// ------------------------------------------------------------------------ //
void Text::pushParagraph()
{
    m_paragraphs.push_back( m_sentences.size() );
}

// ------------------------------------------------------------------------ //
void Text::pushDivision()
{
    m_divisions.push_back( m_paragraphs.size() );
}

// ------------------------------------------------------------------------ //
WORD_ID Text::indexWord( const wstring& word )
{    
    // Ajoute le mot dans le dictionnaire
    WordInfo& w = m_dictionary.insert( word, WordInfo( word ) );

    w.addOne();
    
    return &w;
}

// ------------------------------------------------------------------------ //
std::wostream& operator<<( std::wostream& out, const Text& text )
{
    size_t low;
    size_t high;
    
    for( size_t i = 0; i < text.getSentenceCount(); i++ )
    {
        text.getSentenceBounds( i, low, high );
        out << text.getSentenceID( i );
        
        for( size_t j = low; j < high; j++ )
        {
            out << " " << text.getWord( j ).getWord();
        }

        out << std::endl;
    }

    return out;
}

}// namespace japa
