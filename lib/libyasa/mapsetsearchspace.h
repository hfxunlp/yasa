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
#ifndef JAPA_MAP_SET_SEARCH_SPACE_H
#define JAPA_MAP_SET_SEARCH_SPACE_H

#include <map>
#include <set>

#include "searchspace.h"

namespace japa
{

/**
 * \french
 * Un espace de recherche implant� par un <code>map</code> de 
 * <code>sets</code>.
 *
 * Cet espace de recherche est utile s'il faut avoir un it�rateur sur les
 * lignes ( y ) contenant des possibilit�es.
 * \endfrench
 *
 * \english
 * A search space made of a <code>map</code> of <code>sets</code>.
 *
 * Useful if an iterator on the lines ( y ) of the search space is needed.
 * \endenglish
 *
 *
 * @version 1.1
 */
class MapSetSearchSpace : 
    public std::map< int, std::set< int >, std::greater< int > >,
    public SearchSpace
{
public :
    /** 
     * \french
     * Le type de la structure contenant les rang�es. 
     * \endfrench
     *
     * \english
     * Rows container's data type. 
     * \endenglish
     */
    typedef std::map< int, std::set< int >, std::greater< int > > Row;

    /** 
     * \french
     * Le type de la structure contenant les colonnes. 
     * \endfrench
     *
     * \english
     * Columns container's data type.
     * \endenglish
     */
    typedef std::set< int > Column;

    /**
     * \french
     * Constructeur.
     * 
     * @param x0 La borne inf�rieure en x de l'espace de recherche.
     * @param y0 La borne inf�rieure en y de l'espace de recherche.
     * @param x1 La borne sup�rieure en x de l'espace de recherche.
     * @param y1 La borne sup�rieure en y de l'espace de recherche.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param x0 x search space's lower bound.
     * @param y0 y search space's lower bound.
     * @param x1 x search space's upper bound.
     * @param y1 y search space's upper bound.
     * \endenglish
     */
    MapSetSearchSpace( const int x0, const int y0, const int x1, const int y1 );

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~MapSetSearchSpace();

    bool addPossibility( const int x, const int y );

    bool isPossibility( const int x, const int y ) const;
    
    SearchSpace::Iterator getIterator() const; 

    SearchSpace::Iterator getIterator( const int y ) const;
     
    int getLowerBoundX() const;

    int getLowerBoundY() const;

    int getUpperBoundX() const;

    int getUpperBoundY() const;
    
    /**
     * \french
     * Un it�rateur sur l'espace de recherche.
     * \endfrench
     *
     * \english
     * Search space's iterator. 
     * \endenglish
     *
     *
     * @version 1.1
     */
    class Iterator : public SearchSpaceIterator
    {
    public :
        /**
         * \french
         * Constructeur.
         *
         * @param rowBegin It�rateur pointant sur la premi�re rang�e � visiter.
         * @param rowEnd   It�rateur pointant sur la rang�e avant la derni�re 
         *                 � visiter.
         * \endfrench
         *
         * \english
         * Constructor.
         *
         * @param rowBegin An iterator on the first row.
         * @param rowEnd   An iterator on the row after the last one to visit.
         * \endenglish
         */
        Iterator( const MapSetSearchSpace::Row::const_reverse_iterator& rowBegin,
                  const MapSetSearchSpace::Row::const_reverse_iterator& rowEnd );
        
        bool hasNext() const;
        
        void next();

        int x() const;

        int y() const;

    protected :
        SearchSpaceIterator* clone() const;

    private :
        /**
         * \french
         * Pointe un it�rateur de ligne et de colonne vers l'�l�ment suivant.
         *
         * Quand la fonction finie, les it�rateurs en param�tre pointent sur
         * le prochain �l�ment.
         *
         * @param rowIter Un it�rateur sur la ligne sur laquelle est l'it�rateur
         *                de colonne.
         * @param colIter L'it�rateur � faire pointer sur le suivant.
         * \endfrench
         *
         * \english
         * Points a row and a column iterator on the next element.
         *
         * When the function exits, the parameters points on the next
         * elements.
         *
         * @param rowIter An iterator on the current row.
         * @param colIter An iterator on the current column.
         * \endenglish
         */
        void next( MapSetSearchSpace::Row::const_reverse_iterator& rowIter,
                   MapSetSearchSpace::Column::const_iterator& colIter ) const; 
        
        /** 
         * \french
         * It�rateur pointant sur la rang�e de la solution courante. 
         * \endfrench
         *
         * \english
         * An iterator on the current row. 
         * \endenglish
         */
        MapSetSearchSpace::Row::const_reverse_iterator m_rowIterator;

        /** 
         * \french
         * It�rateur pointant sur la fin des rang�es des solutions. 
         * \endfrench
         *
         * \english
         * An iterator on the last row. 
         * \endenglish
         */
        MapSetSearchSpace::Row::const_reverse_iterator m_rowEnd;

        /** 
         * \french
         * L'it�rateur pointant sur la colonne courante. 
         * \endfrench
         *
         * \english
         * An iterator on the current column.  
         * \endenglish
         */
        MapSetSearchSpace::Column::const_iterator m_colIterator;

        /** 
         * \french
         * L'it�rateur pointant vers la rang�e du prochain �l�ment. 
         * \endfrench
         *
         * \english
         * Iterator on the row of the following element. 
         * \endenglish
         */
        MapSetSearchSpace::Row::const_reverse_iterator m_nextRowIterator;
        
        /** 
         * \french
         * L'it�rateur pointant vers la colonne du prochain �l�ment. 
         * \endfrench
         *
         * \english
         * Iterator on the column of the following element. 
         * \endenglish
         */
        MapSetSearchSpace::Column::const_iterator m_nextColIterator;
        
        /** 
         * \french
         * Est � <code>true</code> si l'it�rateur n'a pas encore avanc� 
         * \endfrench
         *
         * \english
         * Is set to <code>true</code> if next has not been called yet. 
         * \endenglish
         */
        bool m_first;
    };    

private :    
    /** 
     * \french
     * Borne inf�rieure en x de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * x search space's lower bound. 
     * \endenglish
     */
    int m_lowerBoundX;

    /** 
     * \french
     * Borne inf�rieure en y de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * y search space's lower bound. 
     * \endenglish
     */
    int m_lowerBoundY;

    /** 
     * \french
     * Borne sup�rieure en x de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * x search space's lower bound. 
     * \endenglish
     */
    int m_upperBoundX;

    /** 
     * \french
     * Borne sup�rieure en y de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * y search space's lower bound. 
     * \endenglish
     */
    int m_upperBoundY;

};


}// namespace japa

#endif
