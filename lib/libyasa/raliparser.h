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

#ifndef JAPA_RALI_PARSER_H
#define JAPA_RALI_PARSER_H

#include <string>

#include "textparser.h"

namespace japa
{

/**
 * \french
 * Compile un texte suivant une norme s'inspirant de celle du RALI ( GLM ).
 *
 * Le texte est compos�s des jetons suivants : 
 * <table>
 * <tr><th>Nom</th> <th>Description</th></tr>
 * <tr><td>{sect}</td> <td>D�but d'une section.</td></tr>
 * <tr><td>{para}</td> <td>D�but d'un paragraphe.</td></tr>
 * <tr><td>{sent}</td> <td>D�but d'une phrase.</td></tr>
 * <tr><td>{EOF}</td>  <td>Fin du fichier ( optionnel ).</td></tr>
 * <tr><td>autre</td>  <td>Un mot.</td></tr>
 * 
 * Chaque jeton doit tenir sur sa propre ligne.  Toutes les lignes avant le
 * premier jeton <code>{sent}</code> et apr�s le jeton <code>{EOF}</code> sont
 * ignor�s et peuvent donc servir � commenter le fichier.
 * </table>
 *
 * \endfrench
 *
 * \english
 * Parse a text in a format similar to the RALI ( GLM ) format.
 *
 * The text must be composed of the following tokens :
 *
 * <table>
 * <tr><th>Name</th> <th>Description</th></tr>
 * <tr><td>{sect}</td> <td>Beginning of a section.</td></tr>
 * <tr><td>{para}</td> <td>Beginning of a paragraphe.</td></tr>
 * <tr><td>{sent}</td> <td>Beginning of a sentence.</td></tr>
 * <tr><td>{EOF}</td>  <td>End of the file ( optional ).</td></tr>
 * <tr><td>other</td>  <td>A word.</td></tr>
 * 
 * Each token must stands on its own line.  All the lines before the first
 * <code>{sent}</code> and after <code>{EOF}</code> token are ignored.  So
 * theses lines can comment the file.
 *
 * \endenglish
 *
 *
 * @version 1.1
 */
class RaliParser : public TextParser
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
    RaliParser();
    
    bool operator() ( std::wistream& in, Text& text );

    /**
     * \french
     * Lex�me marquant le d�but d'une division.
     * \endfrench
     *
     * \english
     * Lexeme indicating the beginning of a new division.
     * \endenglish
     */
    static const std::wstring LEX_BEGIN_DIVISION;

    /**
     * \french
     * Lex�me marquant le d�but d'un paragraphe.
     * \endfrench
     *
     * \english
     * Lexeme indicating the beginning of a new paragraph.
     * \endenglish
     */
    static const std::wstring LEX_BEGIN_PARAGRAPH;

    /**
     * \french
     * Lex�me marquant le d�but d'une phrase.
     * \endfrench
     *
     * \english
     * Lexeme indicating the beginning of a new sentence.
     * \endenglish
     */
    static const std::wstring LEX_BEGIN_SENTENCE;
    
    /**
     * \french
     * Lex�me marquant la fin du texte.
     * \endfrench
     *
     * \english
     * Lexeme indicating the end of the text.
     * \endenglish
     */
    static const std::wstring LEX_END_TEXT;

    /**
     * \french
     * Le s�parateur de lex�mes.
     * \endfrench
     *
     * \english
     * Lexems separator.
     * \endenglish
     */
    static const wchar_t LEX_SEPARATOR;

private :
    /**
     * \french
     * @return Un identificateur de phrase unique.
     * \endfrench
     *
     * \english
     * @return A unique sentence identifier.
     * \endenglish
     */
    std::wstring nextSID();
    
    /**  
     * \french
     * L'identificateur de la prochaine phrase.
     * \endfrench
     *
     * \english
     * The next sentence's identifier.
     * \endenglish
     */
    unsigned long m_sID;
};

}// namespace japa

#endif
