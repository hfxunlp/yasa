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
/**@file
 * \french
 * Impl�mentation de filter.h
 * \endfrench
 *
 * \english
 * filter.h implementation.
 * \endenglish
 *
 * @version 1.1
 */

#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <string>
#include <unistd.h>

#include "japaexception.h"
#include "filter.h"
#include <iostream>

namespace japa
{

/**
 * \french
 * Trouve et remplace toutes les occurences d'une sous-cha�nes dans un cha�ne.
 * Le traitement est fait sur place.
 *
 * @param s       La cha�ne � traiter.
 * @param search  La sous-cha�ne � chercher.
 * @param replace La cha�ne qui remplacera <code>search</code>.
 * 
 * @return Une r�f�rence vers la cha�ne trait�e.
 * 
 * \endfrench
 *
 * \english
 * Finds and replace all the occurences of a substring in a string.  The
 * processing is done on place.
 *
 * @param s       The string to process.
 * @param search  The substring to search.
 * @param replace The string that will replace <code>search</code>.
 *
 * @return A reference to the processed string.
 * \endenglish
 */
std::string& searchReplace( std::string& s, const std::string search, 
        const std::string replace );

/**
 * \french
 * Filtre utilis� par la fonction <code>gunzip</code>.
 * \endfrench
 *
 * \english
 * <code>gunzip</code>'s filter.
 * \endenglish
 *
 * @see gunzip
 */
static const std::string GUNZIP_FILTER( std::string( "zcat -f " ) + 
        INPUT_FILE_MNEMONIC + " > " + OUTPUT_FILE_MNEMONIC );
    

// --------------------------------------------------------------------------
void inputFilter( const std::string filter, const std::string inputFile, 
        std::ifstream& stream )
{
    std::string command( filter );
    std::string tempFile( tmpnam( NULL ) ); 

    // L'usage de la fonction tmpnam lance un avertissement � la compilation, 
    // c'est cependant la seule fa�on que j'ai trouv� de faire pour avoir un 
    // ifstream sur un fichier temporaire.
    
    searchReplace( command, INPUT_FILE_MNEMONIC, inputFile );
    searchReplace( command, OUTPUT_FILE_MNEMONIC, tempFile );

    if( system( command.c_str() ) )
    {
        unlink( tempFile.c_str() );
        throw Exception( command + " failed" );
    }

    stream.open( tempFile.c_str() );
    unlink( tempFile.c_str() );
}

// --------------------------------------------------------------------------
void gunzip( const std::string inputFile, std::ifstream& stream )
{
    inputFilter( GUNZIP_FILTER, inputFile, stream );
}

// ------------------------------------------------------------------------ //
std::string& searchReplace( std::string& s, const std::string search, 
        const std::string replace )
{
    size_t pos = 0;
    size_t inc = replace.size() - search.size() + 1;
    
    for( pos = s.find( search ); pos != std::string::npos; 
            pos = s.find( search, pos + inc ) )
    {
        s.replace( pos, search.size(), replace );
    }
    
    return s;
}


}// namespace japa
