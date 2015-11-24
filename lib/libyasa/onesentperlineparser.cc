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

#include <string>
#include <sstream>

#include "onesentperlineparser.h"
#include "toolbox.h"

namespace japa
{

// ------------------------------------------------------------------------ //
OneSentPerLineParser::OneSentPerLineParser()
{}

// ------------------------------------------------------------------------ //
OneSentPerLineParser::~OneSentPerLineParser()
{}

// ------------------------------------------------------------------------ //
bool OneSentPerLineParser::operator() ( std::wistream& in, Text& text )
{
    wstring line;
    wstring word;
    unsigned int id = 1;
    
    text.pushDivision();
    text.pushParagraph();

    in.getloc();

    while( getline( in, line ) )
    {
        // Analyse chaque phrase
        std::wistringstream linestream( line );

         text.pushSentence( toString1( id ) );

        while( linestream >> word )
        {
            // Analyse chaque mot
            text.pushWord( word );
        }
        
        id++;
    }

    return true;
}

}// namespace japa
