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

#include "discreteline.h"
#include "linearssf.h"
#include "iostream"

using namespace std;

namespace japa
{

// ------------------------------------------------------------------------ //
LinearSSF::LinearSSF( SolutionMarker& marker ) : m_marker( marker )
{}

// ------------------------------------------------------------------------ //
LinearSSF::~LinearSSF()
{}

// ------------------------------------------------------------------------ //
void LinearSSF::addPassagePoint( const int x, const int y )
{
    PassagePoint pp( x, y );

    m_passagePoints.insert( pp );
}

// ------------------------------------------------------------------------ //
SearchSpace& LinearSSF::operator()( SearchSpace& s )
{
    PassagePoint pp1;
    PassagePoint pp2;
    PointsContainer::const_iterator iter = m_passagePoints.begin();
    
    if( iter != m_passagePoints.end() )
    {
        // S'il y a au moins un point
        pp1 = *iter;
        iter ++;

        if( iter != m_passagePoints.end() )
        {
            // Il y a au moins une ligne
            pp2 = *iter;
            
            // La boucle saute le premier point de chaque ligne, mais il faut
            // considérer celui de la première 

            m_marker( s, pp1.x(), pp1.y(), pp2.x(), pp2.y(), pp1.x(), pp1.y() );

            for( ; iter != m_passagePoints.end(); iter ++ )
            {
                pp2 = *iter;
                
                DiscreteLine line( pp1.x(), pp1.y(), pp2.x(), pp2.y() );
                
                // Évite la redondance, car le dernier point d'une ligne est 
                // le premier de la suivante
                line.next();
                
                while( line.hasNext() )
                {
                    line.next();
                    //cout << "line XY" << line.x() << " " << line.y() << endl;
                    m_marker( s,
                              pp1.x(), pp1.y(), 
                              pp2.x(), pp2.y(), 
                              line.x(), line.y() );
                }

                pp1 = pp2;
            }

        }
        else
        {
            // Il n'y a qu'un point
            m_marker( s, 
                      pp1.x(), pp1.y(), 
                      pp1.x(), pp1.y(), 
                      pp1.x(), pp1.y() );
        }
    }    
   
    return s; 
}

// ------------------------------------------------------------------------ //
bool LinearSSF::PassagePointComparator::operator()
        ( const PassagePoint& p1, const PassagePoint& p2 ) const
{
    return ( p1.x() < p2.x() ) || 
           ( p1.x() == p2.x() && p1.y() < p2.y() );
}

}// namespace japa
