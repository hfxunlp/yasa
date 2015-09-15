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

#include "mapsetsearchspace.h"
#include "iostream"

using namespace std;

namespace japa
{

// ------------------------------------------------------------------------ //
MapSetSearchSpace::MapSetSearchSpace( const int x0, const int y0, 
                                      const int x1, const int y1 )
        : m_lowerBoundX( x0 ), m_lowerBoundY( y0 ),
          m_upperBoundX( x1 ), m_upperBoundY( y1 )
{
}

// ------------------------------------------------------------------------ //
MapSetSearchSpace::~MapSetSearchSpace()
{}

// ------------------------------------------------------------------------ //
bool MapSetSearchSpace::addPossibility( const int x, const int y )
{
    bool ret = false;
    
    if( x >= getLowerBoundX() && x <= getUpperBoundX() &&
        y >= getLowerBoundY() && y <= getUpperBoundY() )
    {
        Row::iterator iter;

        iter = find( y );

        if( iter != end() )
        {
            // La rangée existe déjà
            ( iter -> second ).insert( x );
        }
        else
        {
            Column col;
            col.insert( x );
            
            // Insère la rangée
            insert( value_type( y, col ) );
        }

        ret = true;
    }
    
    return ret;
}

// ------------------------------------------------------------------------ //
bool MapSetSearchSpace::isPossibility( const int x, const int y ) const
{
    bool exists = false;
    Row::const_iterator iter;

    iter = find( y );

    if( iter != end() )
    {
        // La rangée existe
        exists = ( ( iter -> second ).find( x ) != ( iter -> second ).end() );
    }

    return exists;
}

// ------------------------------------------------------------------------ //
SearchSpace::Iterator MapSetSearchSpace::getIterator() const
{
    Iterator* ptr = new Iterator( rbegin(), rend() );

    // L'objet sera libéré par SearchSpace::Iterator
    return SearchSpace::Iterator( ( SearchSpaceIterator* ) ptr );
}

// ------------------------------------------------------------------------ //
SearchSpace::Iterator MapSetSearchSpace::getIterator( const int y ) const
{
    Row::const_iterator iter;
    Row::const_reverse_iterator beginRow( rend() );
    Row::const_reverse_iterator endRow( rend() );
    Iterator* ptr = NULL;
    
    iter = find( y );
    
    if( iter != end() )
    {
        // Quand l'itérateur est convertit, il pointe sur l'élément suivant
        endRow = Row::const_reverse_iterator( iter );
        
        beginRow = endRow;
        beginRow--;
    }
        
    ptr = new Iterator( beginRow, endRow );
    
    
    return SearchSpace::Iterator( ( SearchSpaceIterator* ) ptr ); 
}

// ------------------------------------------------------------------------ //
int MapSetSearchSpace::getLowerBoundX() const
{
    return m_lowerBoundX;
}

// ------------------------------------------------------------------------ //
int MapSetSearchSpace::getLowerBoundY() const
{
    return m_lowerBoundY;
}

// ------------------------------------------------------------------------ //
int MapSetSearchSpace::getUpperBoundX() const
{
    return m_upperBoundX;
}

// ------------------------------------------------------------------------ //
int MapSetSearchSpace::getUpperBoundY() const
{
    return m_upperBoundY;
}


// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //
MapSetSearchSpace::Iterator::Iterator( 
        const MapSetSearchSpace::Row::const_reverse_iterator& rowBegin,
        const MapSetSearchSpace::Row::const_reverse_iterator& rowEnd )

        : m_rowIterator( rowBegin ),
          m_rowEnd( rowEnd ),
          m_nextRowIterator( rowBegin ),
          m_first( true )
{
    if( m_rowIterator != m_rowEnd )
    {
        m_colIterator = ( m_rowIterator -> second ).begin();
        m_nextColIterator = m_colIterator;
        next( m_nextRowIterator, m_nextColIterator ); 
    }
}
// ------------------------------------------------------------------------ //
bool MapSetSearchSpace::Iterator::hasNext() const
{
    return m_nextRowIterator != m_rowEnd;
}

// ------------------------------------------------------------------------ //
void MapSetSearchSpace::Iterator::next()
{
    if( !m_first )
    {
        m_rowIterator = m_nextRowIterator;
        m_colIterator = m_nextColIterator;

        next( m_nextRowIterator, m_nextColIterator );
    }
    else
    {
        m_first = false;

        if( m_colIterator == ( m_rowIterator -> second ).end() )
        {
            // L'itérateur doit pointer vers un élément
            next();
        } 
    }
}

// ------------------------------------------------------------------------ //
void MapSetSearchSpace::Iterator::next( 
        MapSetSearchSpace::Row::const_reverse_iterator& rowIter,
        MapSetSearchSpace::Column::const_iterator& colIter ) const
{
    if( colIter != ( rowIter -> second ).end() )
    {
        colIter++;
    } 

    if( colIter == ( rowIter -> second ).end() )
    {
        do        
        {
            rowIter++;
        }while( rowIter != m_rowEnd && 
                ( rowIter -> second ).begin() == ( rowIter -> second ).end() );


        if( rowIter != m_rowEnd )
        {
            colIter = ( rowIter -> second ).begin();
        }
    }
    
}
// ------------------------------------------------------------------------ //
int MapSetSearchSpace::Iterator::x() const
{
    return *m_colIterator;
}

// ------------------------------------------------------------------------ //
int MapSetSearchSpace::Iterator::y() const
{
    return m_rowIterator -> first;
}

// ------------------------------------------------------------------------ //
SearchSpaceIterator* MapSetSearchSpace::Iterator::clone() const
{
    MapSetSearchSpace::Iterator* s = NULL;

    s = new MapSetSearchSpace::Iterator( m_rowIterator, m_rowEnd );

    s -> m_colIterator = m_colIterator;
    s -> m_nextRowIterator = m_nextRowIterator;
    s -> m_nextColIterator = m_nextColIterator;
    s -> m_first = m_first;

    return s;
}

}// namespace japa
