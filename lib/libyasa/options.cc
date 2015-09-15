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

#include <iostream>
#include <stdlib.h>

#include <unistd.h>

#include "options.h"

// ------------------------------------------------------------------------ //
// Variables utilisées par getopt

/** L'argument d'une option */
extern char* optarg;

/** L'indice dans argv du premier élément qui n'est pas une option. */
extern int optind;

/** 
 * Doit être affectée à 0 si aucun message d'erreur ne doit être lancé par 
 * <code>getopt</code>.
 */
extern int opterr;

/** Contient une option non-reconnue après une erreur. */
extern int optopt;

// ------------------------------------------------------------------------ //

namespace japa
{

// ------------------------------------------------------------------------ //
Options::Options( const std::string& optstring, const bool handleError ) 
        : m_optstring( optstring )
{
    if( !handleError )
    {
        ::opterr = 0;
    }
}

// ------------------------------------------------------------------------ //
Options::~Options()
{}

// ------------------------------------------------------------------------ //
void Options::parse( int argc, char** argv )
{
    int c;  // L'option de la ligne de commande
    size_t arg = 0;
    std::string value;
    
    // Pour chaque options
    while( ( c = getopt( argc, argv, m_optstring.c_str() ) ) != -1 ) 
    {
        if( c == ':' )
        {
            std::string description( "" );

            description = "Missing argument for option : ";
            description += ::optopt;
            error( description );            
        }
        else if( c == '?' )
        {
            std::string description( "" );

            description = "Unknown option : ";
            description += ::optopt;
            error( description );
        }
        else
        {
            std::string::size_type i;
            i = m_optstring.find( c );
            
            if( i < m_optstring.size() - 1 && m_optstring[ i + 1 ] == ':' )
            {
                // Option à argument
                value = ::optarg;
            }
            else
            {
                // Option sans argument
                value = "1";
            }
            
            setOption( c, value );
        }
    }

    for( arg = 0; ::optind < argc; ::optind++, arg++ )
    {
        value = argv[ ::optind ];
        setArgument( arg, value );
    }
            
}

// ------------------------------------------------------------------------ //
void Options::error( const std::string& description )
{
    
    std::cerr << "Erreur : " << description << std::endl;
    exit( 1 ); 
}

// ------------------------------------------------------------------------ //
void Options::setOption( const int option, const std::string& value )
{
    m_options[ option ].push_back( value );
}

// ------------------------------------------------------------------------ //
void Options::setOption( const int option, const char value )
{
    std::string s;
    s += value;

    setOption( option, s );
}

// ------------------------------------------------------------------------ //
bool Options::isOption( const int option ) const
{
    OptionMap::const_iterator iter;
    
    iter = m_options.find( option );
    
    return iter != m_options.end();
}

// ------------------------------------------------------------------------ //
std::string Options::getOption( const int option ) const
{
    std::string value( "" );
    OptionList ol = getOptionList( option );

    if( ol.size() > 0 )
    {
        value = ol.back();
    }
    
    return value;
}

// ------------------------------------------------------------------------ //
Options::OptionList Options::getOptionList( const int option ) const
{
    OptionList ol;
    OptionMap::const_iterator iter;

    iter = m_options.find( option );

    if( iter != m_options.end() )
    {
        ol = iter -> second;
    }

    return ol;
}

// ------------------------------------------------------------------------ //
void Options::setArgument( const int indice, const std::string& value )
{
    m_arguments[ indice ] = value;
}

// ------------------------------------------------------------------------ //
std::string Options::getArgument( const int indice )
{
    std::string value( "" );
    ArgumentMap::const_iterator iter;

    iter = m_arguments.find( indice );

    if( iter != m_arguments.end() )
    {
        value = iter -> second;
    }

    return value;
   
}

}// namespace japa
