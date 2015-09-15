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

#include "prefixcognatefinder.h"
#include "toolbox.h"


namespace japa
{

// ------------------------------------------------------------------------ //
PrefixCognateFinder::PrefixCognateFinder( const size_t length  ) 
        : m_prefixLength( length )
{
}

// ------------------------------------------------------------------------ //
void PrefixCognateFinder::operator()( Text& source, Text& target, 
                                      Validator< WordInfo >& validator )
{
    TextDictionary& srcDict = source.getDictionary();
    TextDictionary& tgtDict = target.getDictionary();
    TextDictionary::DictionaryMap::iterator word;

    // Pour chaque mot du dictionnaire source
    for( word = srcDict.begin(); word != srcDict.end(); word++ )
    {
        // Si le mot est un cognate potentiel
        if( validator( word -> second ) )
        {
        	//wcout <<  word -> first << endl;
            if( isAlphabetic( word -> first ) )
            {
                addPrefixCognate( word -> first, word -> second, 
                                  validator, tgtDict );             
            }                
            else
            {
                addWordCognate( word -> first, word -> second, 
                                validator, tgtDict );
            }
        }
    }
       
}

// ------------------------------------------------------------------------ //
void PrefixCognateFinder::setPrefixLength( const size_t length )
{
    m_prefixLength = length;
}

// ------------------------------------------------------------------------ //
size_t PrefixCognateFinder::getPrefixLength() const
{
    return m_prefixLength;
}

// ------------------------------------------------------------------------ //
void PrefixCognateFinder::addWordCognate( const wstring& word,
                                          WordInfo& wi,
                                          Validator< WordInfo >& validator,
                                          TextDictionary& tgtDict ) const
{
    TextDictionary::DictionaryMap::const_iterator tgtWord;
    
    tgtWord = tgtDict.find( word );

    if( tgtWord != tgtDict.end() )
    {
    	//wcout << "mot source " << word << " Le mot est trouve " << tgtWord -> first << endl;
        // Si le mot est dans le dictionnaire cible
        if( validator( tgtWord -> second ) )
        {
            wi.addSynonym( tgtWord -> second );
        }
    }

}

// ------------------------------------------------------------------------ //
void PrefixCognateFinder::addPrefixCognate( const wstring& word,
                                            WordInfo& wi,
                                            Validator< WordInfo >& validator,
                                            TextDictionary& tgtDict ) const
{
    if( word.size() >= getPrefixLength() )
    {
        wstring beginPrefix( word, 0, getPrefixLength() );
        wstring endPrefix( beginPrefix );

        TextDictionary::DictionaryMap::const_iterator iter; 
        TextDictionary::DictionaryMap::const_iterator end;
        
        // Peut �tre mauvais si le caract�re chang� est le dernier dans la table 

        endPrefix[ endPrefix.size() - 1 ] += 1;

        iter = tgtDict.lower_bound( beginPrefix );
        end = tgtDict.lower_bound( endPrefix );

        // Pour chaque mot dont le pr�fixe est identique dans le texte cible
        for( ; iter != end; iter++ )
        {
            if( validator( iter -> second ) )
            {
                // Le mot est accept� comme cognate
                wi.addSynonym( iter -> second );
            }
        } 
    }
}

}// namespace japa
