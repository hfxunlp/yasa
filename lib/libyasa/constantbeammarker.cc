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

#include "constantbeammarker.h"
#include "iostream"

using namespace std;

namespace japa
{

// ------------------------------------------------------------------------ //
ConstantBeamMarker::ConstantBeamMarker( const size_t radius )
{
    if( radius < 1 )
    {
        m_radius = 1;
    }
    else
    {
        m_radius = radius;
    }
}

// ------------------------------------------------------------------------ //
void ConstantBeamMarker::operator()( SearchSpace& s,
                                     const int, const int,
                                     const int, const int,
                                     const int x, const int y )
{
    const int min = y - m_radius + 1;
    const int max = y + m_radius - 1;
    
    for( int i = min; i <= max; i++ )
    {
        s.addPossibility( x, i ); 

        /////////////////////////////nous affiche notre beam dans l'espace des phrases
        //cout << x << " " << i << endl;
    }
}

}// namespace japa
