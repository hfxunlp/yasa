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

#ifndef JAPA_JAPA_SYNONYM_PARSER_H
#define JAPA_JAPA_SYNONYM_PARSER_H

#include <string>

#include "synonymparser.h"

namespace japa
{

/**
 * \french
 * Permet d'ajouter des synonymes qui sont stock�es au format
 * <code>japa</code>.
 *
 * Deux synonymes, dans le format <code>japa</code>, sont sur la m�me ligne 
 * et sont s�par� par un espace ou une tabulation.  Le premier  mot doit �tre 
 * un mot dans la langue source et le deuxi�me un mot dans la  langue cible.
 *
 * Exemple :
 * 
 * <PRE>pomme apple</PRE>
 * \endfrench
 * 
 * \english
 * <code>japa</code> lexicon parser.
 * 
 * The <code>japa</code> lexicon file format is composed of two words
 * separated by a space character per line.  The first word must be in the
 * source language and the second in the target language.
 *
 * Record example :
 * 
 * <PRE>pomme apple</PRE>
 * \endenglish
 *
 *
 * @version 1.1
 */
class JapaSynonymParser : public SynonymParser< wstring >
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
    JapaSynonymParser();

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~JapaSynonymParser();

    void operator()( std::wistream& in, SynonymContainer< wstring >& sc );
};

}// namespace japa

#endif
