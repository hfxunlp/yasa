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

#ifndef JAPA_TEXT_PARSER_H
#define JAPA_TEXT_PARSER_H

#include <iostream>
#include <string>

#include "text.h"

namespace japa
{

/**
 * \french
 * Interface permettant d'analyser un text et de le repr�senter par une 
 * structure de donn�es.
 *
 * Quand un nouveau format de fichier d'entr�e doit �tre support�, impl�manter
 * cet interface est une option.
 * \endfrench
 *
 * \english
 * Interface for the parsers of different text formats.
 * \endenglish
 *
 *
 * @version 1.1
 * @see Text
 */
class TextParser
{
public :

    /**
     * \french
     * Constructeur
     * \endfrench
     *
     * \english
     * Constructor. 
     * \endenglish
     */
    TextParser();

    /**
     * \french
     * Destructeur
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~TextParser();

    /**
     * \french
     * Analyse un texte et le repr�sente dans un objet Text.
     *
     * @param in Un flux sur le texte � analyser.
     * @param text La stucture dans laquelle ajouter le texte.
     *
     * @return <code>true</code> si tous s'est bien pass�.
     * \endfrench
     *
     * \english
     * Parse a text into a <code>Text</code> object.
     *
     * @param in The stream containing the text to parse.
     * @param text The object where to parse the text.
     *
     * @return <code>true</code> if all went well. 
     * \endenglish
     */
    virtual bool operator() ( std::wistream& in, Text& text ) = 0;
};

}// namespace japa

#endif
