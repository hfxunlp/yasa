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

#ifdef __GNUC__
    #if __GNUC__ < 3
        #include <iostream.h>
    #else
        #include <iostream>
    #endif
#else
    #include <iostream.h>
#endif

#include <clocale>

#include <exception>
#include <japaprogram.h>
#include <fstream>
#include <options.h>
#include <string>
#include <unistd.h>

extern int optind;

namespace
{
    const std::string HELP = 
"Usage : scorecorpora [OPTIONS] inputfile\n\
\n\
Find the last alignments' score of a serie of file paires.\n\
\n\
inputfile :\n\
\n\
The file containing the files to align.  Each record has two  lines, the first is the source text and the second the target text.   Each record is separated by a blank line.  If omitted, the  script reads from stdin.\n\
\n\
output : ( on standard output )\n\
\n\
There is one result per line.  Each result contains three fields  which are separated by spaces characters.  The first field is the  source file, the second the target file and the third, the score  of the last alignment.\n\
\n\
OPTIONS\n\
 \n\
-h Prints this online help.\n\
-o Aligner's options.\n\
-s The directory containing the source files to align.\n\
-t The directory containing the target files to align.\n";
}

/**
 * Fonction principale.  Lance le programme scorecorpora.
 *
 * @param argc Le nombre d'arguments � la ligne de commande
 * @param argv Les valeurs de ces arguments
 *
 * @return 0 si tous s'est bien d�roul�
 */
int main( int argc, char** argv )
{
    int retvalue = 0;
    std::string srcDir = "tok_en/";
    std::string tgtDir = "tok_es/";
    std::ifstream in;
    
    try
    {
        std::ifstream in( "al" );
        std::string src, tgt, blank;
        japa::JapaProgram program;
        program.parse( argc, argv );

        while( std::getline( in, src ) && std::getline( in, tgt ) )
        {
            program.setArgument( 0, srcDir + src );
            program.setArgument( 1, tgtDir + tgt );
            program.run();
            std::getline( in, blank );
        }
        in.close();
    }
    catch( std::exception& ex )
    {
        std::cerr << ex.what() << std::endl;
        std::cerr << "Use japa -" << japa::JapaOptions::HELP 
            << " for online help." << std::endl;
        retvalue = -1;
    }
    catch( ... )
    {
        std::cerr << "An exception has occured." << std::endl;
        retvalue = -1;
    }
    return retvalue;
}


