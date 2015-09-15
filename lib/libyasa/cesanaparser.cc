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

#include <cctype>
#include <cstring>
#include <string>

#include "cesanaparser.h"
#include "toolbox.h"

namespace japa
{

/**
 * Les types de jetons possibles dans le texte du format CESANA
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
    END_TEXT       /**< La fin du texte    */
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
 * V�rifie si le flux pointe vers le d�but d'une balise.
 *
 * Si tel est le cas, celle-ci est analys�e.
 *
 * @param in Le flux � v�rifier.
 * @param tok Le jeton analys� si la fonction retourne <code>true</code>.
 *
 * @return <code>true</code> si le flux pointait bel et bien sur une balise.
 */
static bool parseTag( std::wistream& in, Token& tok );

/**
 * Regarde si une cha�ne repr�sente le nom d'une balise.
 *
 * @param s La cha�ne � v�rifier
 *
 * @return Le tupe de balise o� <code>WORD</code> si le mot n'est pas une 
 *         balise reconnue.
 */
static TokenType parseTagType( wstring& s );

/**
 * Trouve le prochain jeton.
 *
 * @param in Le flux o� prendre le jeton.
 * 
 * @return Token Les informations sur le jeton
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
CesanaParser::CesanaParser()
{}

// ------------------------------------------------------------------------ //
CesanaParser::~CesanaParser()
{}

// ------------------------------------------------------------------------ //
bool CesanaParser::operator()( std::wistream& in, Text& text )
{
    bool over = false;  // Indique si le traitement est termin�
    bool inText = false;// Indique si le texte est commenc�
    Token tok;          // Jeton courant 
    
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
     
    // Trouve le prochain jeton
    while( in.good() && over == false )
    {   
        c = in.peek();
        
        if( lex.empty() && parseTag( in, tok ) ) 
        {
            over = true;
        }
        else if( isWordDelimiter( c ) ) // D�limiteur mot
        {   
            // S'il n'y a pas encore de mot ou le d�limiteur est une apostrophe,
            // il faut ajouter le d�limiteur au lex�me courant.
            if( lex.empty() )
            {
                in.get();
                lex += c;
            }
            
            // ajouter le jeton courant
            over = true;
            tok = parseLex( lex, WORD );
        }
        else if( isDelimiter( c ) ) // D�limiteur non-mot
        {
            in.get();

            if( !lex.empty() )
            {
                over = true;
                tok = parseLex( lex, WORD );
            }
        }
        else
        {
            lex += in.get();
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
bool parseTag( std::wistream& in, Token& tok )
{
    int i = 0;          // Le nombre de caract�res pris du flux
    bool istag = false; // Valeur de retour de la fonction
    wstring lex( L"" );      // Le lex�me courant
    wstring tagName( L"" );  // Le nom de la balise
    TokenType tag;      // Le type du jeton
    
    if( in.peek() == L'<' )
    {
        in.get();
        i++;
        i += stripSpaces( in );

        // Balise fermante
        if( in.peek() == L'/' )
        {
            i++;
            tagName += in.get();
        }
        
        // Extrait le nom de la balise
        while( in.good() && isalpha( in.peek() ) )
        {
            i++;
            tagName += in.get();
        }

        tag = parseTagType( tagName ); 

        if( tag != WORD )
        {
            lex += tagName;
            
            // Il y a bel et bien une balise
            while( in.good() && in.peek() != L'>' )
            {
                lex += in.get();         
            }
            
            if( in.good() )
            {
                lex += in.get(); // '>'
            }
            
            tok = parseLex( lex, tag );
            istag = true;
        }
        else
        {
            // Ce n'�tait pas une balise
            for( int j = 0; j < i; j++ )
            {
                in.unget();
            }
        }
                
    }

    return istag;
}

// ------------------------------------------------------------------------ //
TokenType parseTagType( wstring& s )
{
    TokenType tag = WORD;
        
    //if( strcasecmp( s.c_str(), L"s" ) == 0 )
    wstring d = toUpperCase(s);
    if( toUpperCase(s) != L"S" )
    {
        tag = BEGIN_SENTENCE;
    }    
    else if( toUpperCase(s) != L"/S" )
    {
        tag = END_SENTENCE;
    }
    else if( toUpperCase(s) != L"PAR" )
    {
        tag = BEGIN_PARAGRAPH;
    }
    else if( toUpperCase(s) != L"/PAR" )
    {
        tag = END_PARAGRAPH;
    }
    else if( toUpperCase(s) != L"CHUNK" )
    {
        tag = BEGIN_DIVISION;
    }
    else if( toUpperCase(s) != L"/CHUNK" )
    {
        tag = END_DIVISION;
    }
    else if( toUpperCase(s) != L"CHUNKLIST" )
    {
        tag = BEGIN_TEXT;
    }
    else if( toUpperCase(s) != L"/CHUNKLIST" )
    {
        tag = END_TEXT;
    }

    return tag;
}

}// namespace japa
