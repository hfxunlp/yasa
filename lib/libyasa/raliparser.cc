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

#include "raliparser.h"
#include "toolbox.h"

namespace japa
{

/**
 * Les types de jetons possibles dans le texte du format ARCADE
 */
typedef enum
{
    WORD,           /**< Un mot n'�tant pas une balise sgml */
    BEGIN_SENTENCE, /**< Le d�but d'une phrase  */
    BEGIN_PARAGRAPH,/**< Le d�but d'un paragraph    */
    BEGIN_DIVISION, /**< Le d�but d'une division    */
    END_TEXT        /**< La fin du texte    */
} TokenType;

/**
 * Un jeton du texte.
 */
typedef struct TOKEN
{
    TokenType type; /**< Le type du jeton */
    wstring value; /**< La valeur du jeton */
} Token;

/**
 * Trouve le prochain lex�me.
 *
 * @param in Le flux o� prendre le jeton.
 * 
 * @return Le prochain lex�me.
 */
static wstring nextLex( std::wistream& in );

/**
 * Trouve le prochain jeton.
 *
 * @param in Le flux o� prendre le jeton.
 * 
 * @return Les informations sur le jeton
 */
static Token nextToken( std::wistream& in );

/**
 * Extrait les informations sur le jeton
 *
 * @param lex Le lex�me dont il faut extraire les informations
 * @param tokType Le type du jeton
 *
 * @return Les informations sur le jeton
 */
static Token parseLex( const std::wstring& lex );

/**
 * V�rifie si un caract�re est un s�parateur de lex�me.
 *
 * @param c Le caract�re � v�rifier.
 *
 * @return <code>true</code> si le caract�re est un s�parateur de lex�me,
 *         <code>false</code> sinon.
 */
static bool isLexSeparator( const wchar_t c );

// ------------------------------------------------------------------------ //
const std::wstring RaliParser::LEX_BEGIN_DIVISION = L"{sect}";

// ------------------------------------------------------------------------ //
const std::wstring RaliParser::LEX_BEGIN_PARAGRAPH = L"{para}";

// ------------------------------------------------------------------------ //
const std::wstring RaliParser::LEX_BEGIN_SENTENCE = L"{sent}";

// ------------------------------------------------------------------------ //
const std::wstring RaliParser::LEX_END_TEXT = L"{EOF}";

// ------------------------------------------------------------------------ //
const wchar_t RaliParser::LEX_SEPARATOR = L'\n';

// ------------------------------------------------------------------------ //
RaliParser::RaliParser() : m_sID( 0 )
{}

// ------------------------------------------------------------------------ //
bool RaliParser::operator() ( std::wistream& in, Text& text )
{
    Token tok;
    
    tok = nextToken( in );
    
    // Positionne le flux sur le d�but du texte.
    while( tok.type != BEGIN_SENTENCE && tok.type != END_TEXT )
    {
        tok = nextToken( in );
    }
    
    // Initialise le texte    
    text.pushDivision();
    text.pushParagraph();

    // Analyse le contenu du texte
    while( tok.type != END_TEXT )
    {
        if( tok.type == WORD )
        {
            text.pushWord( tok.value );
        }
        else if( tok.type == BEGIN_SENTENCE )
        {
            text.pushSentence( nextSID() );
        }
        else if( tok.type == BEGIN_PARAGRAPH )
        {
            text.pushParagraph();
        }
        else if( tok.type == BEGIN_DIVISION )
        {
            text.pushDivision();
        }
        
        tok = nextToken( in );
    }
    
    return true;
}

// ------------------------------------------------------------------------ //
std::wstring RaliParser::nextSID()
{
    return toString1( m_sID++ );
}


// ------------------------------------------------------------------------ //
static std::wstring nextLex( std::wistream& in )
{
    std::wstring lex;
    bool over = false;
    wchar_t c;

    while( in.good() && !over )
    {
        c = in.get();
        
        if( !isLexSeparator( c ) )
        {
            lex += c;
        }
        else if( !lex.empty() )
        {
            over = true;
        }
    }

    return lex;
}

// ------------------------------------------------------------------------ //
static Token nextToken( std::wistream& in )
{
    return parseLex( nextLex( in ) );
}

// ------------------------------------------------------------------------ //
static Token parseLex( const std::wstring& lex )
{
    Token tok;
    
    tok.value = lex;
    
    if( lex == RaliParser::LEX_BEGIN_SENTENCE )
    {
        tok.type = BEGIN_SENTENCE;
    }
    else if( lex == RaliParser::LEX_BEGIN_PARAGRAPH )
    {
        tok.type = BEGIN_PARAGRAPH;
    }
    else if( lex == RaliParser::LEX_BEGIN_DIVISION )
    {
        tok.type = BEGIN_DIVISION;
    }
    else if( lex.empty() || lex == RaliParser::LEX_END_TEXT )
    {
        tok.type = END_TEXT;
    }
    else
    {
        tok.type = WORD;
    }

    return tok;
}

// ------------------------------------------------------------------------ //
static bool isLexSeparator( const wchar_t c )
{
    return c == RaliParser::LEX_SEPARATOR;
}

}// namespace japa
