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

#ifndef JAPA_ARCADE_PARSER_H
#define JAPA_ARCADE_PARSER_H

#include "textparser.h"

namespace japa
{

/**
 * \french
 * Compile un texte suivant la norme ARCADE.
 *
 * Cet analyseur reconna�t les balises suivantes :
 *
 * <TABLE>
 * <TR><TD> \<text\> et \</text\>  </TD><TD> D�but et fin du texte </TD></TR>
 * <TR><TD> \<divid="id"\></TD><TD> D�but d'une nouvelle division</TD></TR>
 * <TR><TD> \<pid="id"\></TD><TD> D�but d'un nouveau paragraphe</TD></TR>
 * <TR><TD> \<s id="id"\> \</s\></TD><TD> D�but et fin d'une phrase</TD></TR>
 * </TABLE>
 *
 * O�, dans tous les cas, <EM> id </EM> est une cha�ne de caract�re unique �
 * chaque section.
 * \endfrench
 *
 * \english
 * Parse a text that is in ARCADE format.
 * 
 * This parser parses the following tags :
 * 
 * <TABLE>
 * <TR><TD>\<text\> and \</text\></TD><TD>Beginning and ending of text</TD></TR>
 * <TR><TD> \<divid="id"\>       </TD><TD>Beginning of a division </TD></TR>
 * <TR><TD> \<pid="id"\>         </TD><TD>Beginning of a paragraph</TD></TR>
 * <TR><TD> \<s id="id"\> \</s\> </TD><TD>Beginning of a sentence </TD></TR>
 * </TABLE>
 *
 * \endenglish
 *
 *
 * @version 1.1
 */
class ArcadeParser : public TextParser
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
    ArcadeParser();

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~ArcadeParser();

    bool operator() ( std::wistream& in, Text& text );
    
};

}// namespace japa
#endif
