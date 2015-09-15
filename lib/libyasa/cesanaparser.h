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

#ifndef JAPA_CESANA_PARSER_H
#define JAPA_CESANA_PARSER_H

#include "textparser.h"

namespace japa
{

/**
 * \french
 * Compile un texte suivant la norme CESANA.
 *
 * Cet analyseur est assez mauvais en soi, et ne reconna�t que le sous-ensemble
 * suivant des balises de CESANA :
 *
 * <TABLE>
 * <TR><TD>\<CHUNKLIST\>,\</CHUNKLIST\></TD><TD>D�but et fin du texte</TD></TR>
 * <TR><TD>\<CHUNK\>         </TD><TD>D�but d'une nouvelle division</TD></TR>
 * <TR><TD>\<PAR\>           </TD><TD> D�but d'un nouveau paragraphe</TD></TR>
 * <TR><TD>\<S id="id"\> \</S\></TD><TD> D�but et fin d'une phrase</TD></TR>
 * </TABLE>
 *
 * O� <em>id</em> est une cha�ne de caract�re unique � chaque phrase.
 * \endfrench
 *
 * \english
 * Parse a text that is in CESANA format.
 *
 * This parser is not very good, it only recognizes the following subset of 
 * CESANA tags :
 * 
 * <TABLE>
 * <TR><TD>\<CHUNKLIST\>,\</CHUNKLIST\></TD><TD>Beginning and ending of text</TD></TR>
 * <TR><TD>\<CHUNK\>     </TD><TD> Beginning of a division </TD></TR>
 * <TR> <TD> \<PAR\>           </TD><TD> Beginning of a paragraph </TD></TR>
 * <TR> <TD> \<S id="id"\> \</S\></TD><TD> Beginning and ending of a sentence </TD></TR>
 * </TABLE>
 *
 * Where <em>id</em> is a uniq alphanumeric string for each sentence.
 * \endenglish
 *
 *
 * @version 1.1
 */
class CesanaParser : public TextParser
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
    CesanaParser();

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~CesanaParser();

    bool operator() ( std::wistream& in, Text& text );
};


}// namespace japa

#endif
