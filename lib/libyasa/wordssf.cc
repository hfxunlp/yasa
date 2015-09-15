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

#include <algorithm>
#include <map>
#include <vector>
#include <iostream>

#include "wordssf.h"

using namespace std;

namespace japa
{

// ------------------------------------------------------------------------ //
WordSSF::WordSSF( Text& source, Text& target, Validator< WordInfo >& validator,
                 const size_t radius ) 
        : m_source( source ), m_target( target ), 
          m_validator( validator ), m_radius( radius )
{}

// ------------------------------------------------------------------------ //
SearchSpace& WordSSF::operator()( SearchSpace& s )
{
    // Ce code n'est pas � toute �preuve, il ne g�re pas les cas o� les mots
    // ne sont pas dans le dictionnaire.
    
    TextDictionary& dictSrc = m_source.getDictionary();
    WordInfo::Synonyms synonyms;
    WordInfo::Synonyms::iterator synIter;
    std::map< const wstring, std::vector< size_t > > t1;
    double delta = ( ( double )m_source.getWordCount() ) / 
            m_target.getWordCount();
    size_t min;
    size_t max;
    
    // Indexe les cognates
    for( size_t i = 0; i < m_source.getWordCount(); i++ )
    {
        // Si le mot est valide
        if( m_validator( m_source.getWord( i ) ) )
        {
            // Les synonymes du mot source i
        	//cout << "le mot est " << i << " " << m_source.getWord( i ).getWord().ToConstCharPtr() << endl;
            synonyms = dictSrc[ m_source.getWord( i ).getWord()].getSynonyms();
            
            // Pour chaque synonyme, on indexe l'indice du mot du texte source 
            // qui lui correspond.
            for( synIter = synonyms.begin(); synIter != synonyms.end(); 
                 synIter++ )
            {
                //t1[ ( *synIter ) -> getWord().c_str() ].push_back( i );
            	t1[ ( *synIter ) -> getWord()].push_back( i );
            }
        }
    }

    // Construction de l'espace de recherche
    for( size_t  j = 0; j < m_target.getWordCount(); j++ )
    {
        std::vector< size_t >& words = 
                //t1[ m_target.getWord( j ).getWord().c_str() ];
        		t1[ m_target.getWord( j ).getWord()];
        
        if( getRadius() != INFINITE_RADIUS )
        {
            size_t x = ( size_t )( delta * j );
            size_t sx = m_source.getSentenceIndice( x );
            size_t low, high, temp; 
            
            if( getRadius() < sx )
            {
                low = sx - getRadius();
            }
            else
            {
                low = 0;
            }
    
            if( sx + getRadius() < m_source.getSentenceCount() )
            {
                high = sx + getRadius();
            }
            else
            {
                high = m_source.getSentenceCount() - 1;
            }
            
            m_source.getSentenceBounds( low, min, temp );
            m_source.getSentenceBounds( high, temp, max ); 
        }
        else
        {
            min = 0;
            max = m_source.getWordCount();
        }
        //cout << "jjjjjjjjjj " << j << endl;


        // Pour chaque synonymes du texte source
        for( size_t w = 0; w < words.size(); w++ )
        {
            if( words[ w ] >= min && words[ w ] <= max )
            {
                s.addPossibility( j, words[ w ] );
                //nous affiche tous les cognates
                //cout <<words[w] << " " << j << endl;

            }
        }
    }

    /*
    SearchSpace::Iterator it = s.getIterator();
    while(it.hasNext())
    {
    	cout << "               X: " << it.y() <<
    	"Y: " << it.x() << endl;
    	it.next();
    }*/

    return s;
}
// ------------------------------------------------------------------------ //
void WordSSF::setRadius( const size_t radius )
{
    m_radius = radius;
}

// ------------------------------------------------------------------------ //
size_t WordSSF::getRadius() const
{
    return m_radius;
}

}// namespace japa
