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

#ifndef JAPA_ONE_SENT_PER_LINE_H
#define JAPA_ONE_SENT_PER_LINE_H

#include "textparser.h"

namespace japa
{

/**
 * \french
 * Compile un texte donc chaque phrase tient sur une ligne et chaque mot est
 * s�par� par un espace.
 * \endfrench
 *
 * \english
 * Parse a text in where sentences are delimited by new lines and words by 
 * spaces.
 * \english
 *
 *
 * @version 1.1
 */
class OneSentPerLineParser : public TextParser
{
public :
    /**
     * \french
     * Constructeur.
     * \endfrench
     *
     * \english
     * Constructor.
     * \endenglish
     */  
    OneSentPerLineParser();

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~OneSentPerLineParser();

    bool operator() ( std::wistream& in, Text& text );
};

}// namespace japa

#endif
