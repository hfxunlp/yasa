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
#include <stdexcept>
#include <japaprogram.h>

/**
 * Fonction principale.  Lance le programme yasa.
 *
 * @param argc Le nombre d'arguments � la ligne de commande
 * @param argv Les valeurs de ces arguments
 *
 * @return 0 si tous s'est bien d�roul�
 */
int main( int argc, char** argv )
{
    int retvalue = 0;
    
    try
    {
        // must set a UTF-8 locale
        std::locale *theLocale = NULL;

        try
        {
            theLocale = new std::locale("en_US.UTF-8");
        }
        catch( std::exception& ex )
        {
            theLocale = new std::locale("");
            std::cerr << "Could not find locale en_US.UTF-8 on your system.\nReverting to the system's "
                      << theLocale->name()
                      << ".\nIf the latter is not UTF-8, the program will not behave correctly.\n"
                      << "See the documentation."
                      << std::endl;
        }

        std::locale::global(std::locale(*theLocale));
        // end locale

        if (argc == 1) {
            throw std::runtime_error("No arguments specified.");
        }

        japa::JapaProgram program;

        program.parse( argc, argv );
        program.run();

    }
    catch( std::exception& ex )
    {
        std::cerr << ex.what() << std::endl;
        std::cerr << "Use yasa -" << japa::JapaOptions::HELP 
                  << " for online help." << std::endl;
        retvalue = -1;
    }
    
    return retvalue;
}



