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

#include "setsearchspace.h"

namespace japa
{

// ------------------------------------------------------------------------ //
bool SetSearchSpace::SolutionComparator::operator()( const Solution& sol1, 
        const Solution& sol2 ) const
{
    return ( sol1.y() < sol2.y() ) || 
           ( sol1.y() == sol2.y() && sol1.x() < sol2.x() );
}

// ------------------------------------------------------------------------ //
SetSearchSpace::SetSearchSpace( const int x0, const int y0, const int x1, 
        const int y1 )
{
    m_x0 = x0;
    m_y0 = y0;
    m_x1 = x1;
    m_y1 = y1;
}

// ------------------------------------------------------------------------ //
SetSearchSpace::~SetSearchSpace()
{}

// ------------------------------------------------------------------------ //
size_t SetSearchSpace::size() const
{
    return m_set.size();
}

// ------------------------------------------------------------------------ //
bool SetSearchSpace::addPossibility( const int x, const int y )
{
    bool ret = false; 
    
    if( x >= m_x0 && x <= m_x1 && y >= m_y0 && y <= m_y1 )
    {
        // Les coordonnées sont valides dans l'espace
        m_set.insert( Solution( x, y ) );        
        ret = true;
    }

    return ret;
}

// ------------------------------------------------------------------------ //
bool SetSearchSpace::isPossibility( const int x, const int y ) const
{
    return m_set.find( Solution( x, y ) ) == m_set.end();
}

// ------------------------------------------------------------------------ //
int SetSearchSpace::getLowerBoundX() const
{
    return m_x0;
}

// ------------------------------------------------------------------------ //
int SetSearchSpace::getLowerBoundY() const
{
    return m_y0;
}

// ------------------------------------------------------------------------ //
int SetSearchSpace::getUpperBoundX() const
{
    return m_x1;
}

// ------------------------------------------------------------------------ //
int SetSearchSpace::getUpperBoundY() const
{
    return m_y1;
}

// ------------------------------------------------------------------------ //
SearchSpace::Iterator SetSearchSpace::getIterator() const
{
    Iterator* ptr = new Iterator( m_set.begin(), m_set.end() );
    
    // L'itérateur se charge de libérer la mémoire de ptr
    return SearchSpace::Iterator( ( SearchSpaceIterator* ) ptr );
}

// ------------------------------------------------------------------------ //
SearchSpace::Iterator SetSearchSpace::getIterator( const int y ) const
{
    
    SSSet::const_iterator low;
    Solution solLow( getLowerBoundX(), y );
    Iterator* ptr;
    
    low = m_set.lower_bound( solLow );

    if( low != m_set.end() && low -> y() == y )
    {
        // Il y a des solutions avec la coordonnée en y spécifiée
        SSSet::const_iterator high;
        Solution solHigh( getUpperBoundX(), y );

        high = m_set.upper_bound( solHigh );
        ptr = new Iterator( low, high );
    }
    else
    {
        // Aucune solution n'a de coordonnée en y comme spécifiée
        ptr = new Iterator( m_set.end(), m_set.end() );
    }
    
    

    
    // L'itérateur se charge de libérer la mémoire de ptr
    return SearchSpace::Iterator( ( SearchSpaceIterator* ) ptr );
}

// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //

SetSearchSpace::Iterator::Iterator( const SetSearchSpace::SSSet::const_iterator begin,
                                    const SetSearchSpace::SSSet::const_iterator end ) 
                                    
                                    : m_iterator( begin ), 
                                      m_end( end ), 
                                      m_first( true )

{}

// ------------------------------------------------------------------------ //
bool SetSearchSpace::Iterator::hasNext() const 
{
    bool ret = false;
    
    if( m_iterator != m_end )
    {
        SetSearchSpace::SSSet::const_iterator it;

        it = m_iterator;
        it ++;

        ret = ( it != m_end );
    }
    
    return ret;
}

// ------------------------------------------------------------------------ //
void SetSearchSpace::Iterator::next()
{
    if( !m_first )
    {
        m_iterator ++;
    }
    else
    {
        m_first = false;
    }
}

// ------------------------------------------------------------------------ //
int SetSearchSpace::Iterator::x() const
{
    return m_iterator -> x();
}

// ------------------------------------------------------------------------ //
int SetSearchSpace::Iterator::y() const
{
    return m_iterator -> y();
}

// ------------------------------------------------------------------------ //
SearchSpaceIterator* SetSearchSpace::Iterator::clone() const
{
    SetSearchSpace::Iterator* s;

    s = new SetSearchSpace::Iterator( m_iterator, m_end );
    s -> m_first = m_first;

    return s;
}

}// namespace japa
