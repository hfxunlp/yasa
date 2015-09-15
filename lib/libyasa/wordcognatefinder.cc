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

#include "text.h"
#include "wordcognatefinder.h"

namespace japa
{

// ------------------------------------------------------------------------ //
void WordCognateFinder::operator()( Text& source, Text& target,
                                    Validator< WordInfo >& validator )
{
    TextDictionary& srcDict = source.getDictionary(); 
    TextDictionary& tgtDict = target.getDictionary();
    TextDictionary::iterator srcIter;
    TextDictionary::const_iterator tgtIter;
    
    // Pour chaque mot du dictionnaire source
    for( srcIter = srcDict.begin(); srcIter != srcDict.end(); srcIter++ )
    {
        // On regarde si le mot se trouve dans le dictionnaire cible
        tgtIter = tgtDict.find( srcIter -> first );

        if( tgtIter != tgtDict.end() )
        {
            if( validator( srcIter -> second ) && 
                validator( tgtIter -> second ) )
            {
                ( srcIter -> second ).addSynonym( tgtIter -> second );
            }
        }

    }
}

}// namespace japa
