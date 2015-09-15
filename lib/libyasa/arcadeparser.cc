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

#include <cctype>
#include <string>

#include "arcadeparser.h"
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
    END_SENTENCE,   /**< La fin d'une phrase    */
    BEGIN_PARAGRAPH,/**< Le d�but d'un paragraph    */
    END_PARAGRAPH,  /**< La fin d'un paragraph  */
    BEGIN_DIVISION, /**< Le d�but d'une division    */
    END_DIVISION,   /**< La fin d'une division  */
    BEGIN_TEXT,     /**< Le d�but du texte  */
    END_TEXT        /**< La fin du texte    */
} TokenType;

/**
 * Un jeton du texte.
 */
typedef struct TOKEN
{
    TokenType type; /**< Le type du jeton */
    wstring id; /**< L'identificateur du jeton */
    wstring value; /**< La valeur du jeton */
} Token;

/**
 * Regarde si une cha�ne repr�sente le nom d'une balise.
 *
 * @param s La cha�ne � v�rifier
 *
 * @return Le type de balise o� <code>WORD</code> si le mot n'est pas une 
 *         balise reconnue.
 */
static TokenType parseTagType( const wstring& s );

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
static Token parseLex( const wstring& lex, const TokenType& tokType );

// ------------------------------------------------------------------------ //
ArcadeParser::ArcadeParser()
{}

// ------------------------------------------------------------------------ //
ArcadeParser::~ArcadeParser()
{}

// ------------------------------------------------------------------------ //
bool ArcadeParser::operator()( std::wistream& in, Text& text )
{
    bool over = false;  // Indique si le traitement est termin�
    bool inText = false;// Indique si le texte est commenc�
    Token tok;          // Jeton courant
    wstring ws;
    
    // Lit les jetons
    while( in.good() && over == false )
    {
        tok = nextToken( in );
        
        if( !inText )
        {
            if( tok.type == BEGIN_TEXT )
            {
                inText = true;
            }
        }
        else
        {
            switch( tok.type )
            {
            case WORD :
                text.pushWord( tok.value );
                break;
            case BEGIN_SENTENCE :
            	text.pushSentence( tok.value );
                break;
            case BEGIN_PARAGRAPH :
                text.pushParagraph();
                break;
            case BEGIN_DIVISION :
                text.pushDivision();
                break;
            case END_TEXT :
                over = true;
                break;
            default :
                // on s'en fou
                break;
            }
        }
    }

    return over;
}


// ------------------------------------------------------------------------ //
Token parseLex( const wstring& lex, const TokenType& tokType )
{
    Token tok;
    
    tok.type = tokType;

    if( tokType == BEGIN_SENTENCE )
    {
        //Il faut trouver l'identificateur de la phrase
        wstring::size_type i;
        wstring::size_type j;

        tok.value = L"Oups no sentence id!";
        i = lex.find( L"\"" );

        if( i != wstring::npos )
        {
            j = lex.find( L"\"", i + 1 );

            if( j != wstring::npos )
            {
                tok.value = lex.substr( i + 1, j - i - 1 );
            }
        }

    }
    else
    {
        tok.value = lex;
    }
    
    return tok;
}

// ------------------------------------------------------------------------ //
Token nextToken( std::wistream& in )
{
    bool over = false;  // Indique si le traitement est fini
    wchar_t c;             // Le caract�re lu
    wstring lex;    // Le lex�me courant
    Token tok;          // Le jeton trouv�   
    
    
    while( in.good() && over == false )
    {
        c = in.get();
        
        if( iswspace( c ) )
        {   
            if( !lex.empty() )
            {
                // ajouter le jeton courant
                over = true;
                tok = parseLex( lex, WORD );
            }
        }
        else if( c == L'<' )
        {
            wstring tagName; // Le nom de la balise
            TokenType tag;
            
            lex += c;
            
            // cherche le d�but du nom de la balise
            do
            {
                c = in.get();
            }while( in.good() && isspace( c ) );

            // balise fermante
            if( c == L'/' && in.good() )
            {
                tagName += c;
                lex += c;
                c = in.get();
            } 
            
            // cherche le nom du tag
            do
            {
                tagName += c;
                lex += c;
                c = in.get();
            }while( in.good() && isalpha( c ) );

            tag = parseTagType( tagName );

            if( tag != WORD )
            {
                while( c != L'>' && in.good() )
                {
                    lex += c;
                    c = in.get();
                }
                
                lex += c;
                tok = parseLex( lex, tag );
                over = true;
            }
            else
            {
                lex += c;
            }
        }
        else
        {
            lex += c;
        }
    }

    // fin du flux
    if( !over )
    {
        tok = parseLex( lex, WORD );
    }
    return tok;
}

// ------------------------------------------------------------------------ //
TokenType parseTagType( const wstring& s )
{
    TokenType tag = WORD;
        
    if( s == L"s" || s == L"sid" )
    {
        tag = BEGIN_SENTENCE;
    }    
    else if( s == L"/s" )
    {
        tag = END_SENTENCE;
    }
    else if( s == L"pid" )
    {
        tag = BEGIN_PARAGRAPH;
    }
    else if( s == L"/p" )
    {
        tag = END_PARAGRAPH;
    }
    else if( s == L"divid" )
    {
        tag = BEGIN_DIVISION;
    }
    else if( s == L"/div" )
    {
        tag = END_DIVISION;
    }
    else if( s == L"text" )
    {
        tag = BEGIN_TEXT;
    }
    else if( s == L"/text" )
    {
        tag = END_TEXT;
    }

    return tag;
}

}// namespace japa
