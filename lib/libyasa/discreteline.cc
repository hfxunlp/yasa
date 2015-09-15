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

#include <cstdlib>

#include "discreteline.h"

namespace japa
{

// ------------------------------------------------------------------------ //
DiscreteLine::DiscreteLine( const int x0, const int y0, const int x1, const int y1 )
{
    init( x0, y0, x1, y1 );
}

// ------------------------------------------------------------------------ //
DiscreteLine::~DiscreteLine()
{}

// ------------------------------------------------------------------------ //
bool DiscreteLine::hasNext() const
{
    return ( ( m_maxIndependent - (*m_independant) ) * m_incrIndependent ) > 0;
}

// ------------------------------------------------------------------------ //
void DiscreteLine::next()
{
    // Si ce n'est pas le premier point, il faut calculer le prochain
    if( !m_first )
    {
        // Décide du prochain point
        if( m_decision <= 0 )
        {
            m_decision += m_incrE;
        }
        else
        {
            m_decision += m_incrNE;
            *m_dependant += m_incrDependent;
        }

        *m_independant += m_incrIndependent;
    }
    else
    {
        m_first = false;
    }
}

// ------------------------------------------------------------------------ //
int DiscreteLine::x() const
{
    return m_currentX;
}

// ------------------------------------------------------------------------ //
int DiscreteLine::y() const
{
    return m_currentY;
}

// ------------------------------------------------------------------------ //
void DiscreteLine::init( const int x0, const int y0, 
                         const int x1, const int y1 )
{
    int dx; // différence en x
    int dy; // différence en y
    
    m_currentX = x0;
    m_currentY = y0;
    
    dx = abs( x1 - x0 );
    dy = abs( y1 - y0 );
    
    if( dx > dy )
    {
        // X est la variable indépendante
        m_independant = &m_currentX;
        m_dependant = &m_currentY;
        
        m_incrIndependent = ( x1 > x0 )? 1 : -1;
        m_incrDependent = ( y1 > y0 )? 1 : -1;

        m_maxIndependent = x1; 
    
        m_decision = ( 2 * dy ) - dx;
        m_incrE = 2 * dy;
        m_incrNE = 2 * ( dy - dx );

    }
    else
    {
        // Y est la variable indépendante
        m_independant = &m_currentY;
        m_dependant = &m_currentX;
        
        m_incrIndependent = ( y1 > y0 )? 1 : -1;
        m_incrDependent = ( x1 > x0 )? 1 : -1;

        m_maxIndependent = y1; 
        
        m_decision = ( 2 * dx ) - dy;
        m_incrE = 2 * dx;
        m_incrNE = 2 * ( dx - dy );
    }

    m_first = true;

}

}// namespace japa
