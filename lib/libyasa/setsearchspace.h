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

#ifndef JAPA_SET_SEARCH_SPACE_H
#define JAPA_SET_SEARCH_SPACE_H

#include <functional>
#include <set>

#include "point2d.h"
#include "searchspace.h"

namespace japa
{

/**
 * \french
 * Un espace de recherche impl�mant� par un ensemble (<code>std::set</code>).
 * \endfrench
 *
 * \english
 * A search space implemented by a set (<code>std::set</code>).
 * \endenglish
 *
 *
 * @version 1.1
 */
class SetSearchSpace : public SearchSpace
{
private :

    /** 
     * \french
     * Le type d'une solution dans l'espace de recherche. 
     * \endfrench
     *
     * \english
     * The solution's data type. 
     * \endenglish
     */
    typedef Point2D< int > Solution; 
 
    /**
     * \french
     * Compare deux solution pour savoir laquelle est la plus petite en terme de
     * position dans une matrice.
     * \endfrench
     *
     * \english
     * Compare two solutions in order the define the lower one if the points
     * are positions in a matrix.
     * \endenglish
     *
     *
     * @version 1.1
     */
    class SolutionComparator : 
            public std::binary_function< Solution, Solution, bool >

    {
    public :
        /**
         * \french
         * Permet de comparer deux solutions.
         *
         * @param sol1 La premi�re solution.
         * @param sol2 La deuxi�me solution.
         *
         * @return <code>true</code> si <code>sol1 < sol2</code>.
         * \endfrench
         *
         * \english
         * Compare two solutions.
         *
         * @param sol1 The first solution.
         * @param sol2 The second solution.
         *
         * @return <code>true</code> if <code>sol1 < sol2</code>.
         * \endenglish
         */
        bool operator()( const Solution& sol1, const Solution& sol2 ) const;
    };
    
    /** 
     * \french
     * Le type de la structure de donn�e qui contient les solutions.
     * \endfrench
     *
     * \english
     * The solutions holder's data type. 
     * \endenglish
     */
    typedef std::set< Solution, SetSearchSpace::SolutionComparator > SSSet;

public : 
    /**
     * \french
     * Un it�rateur sur l'espace de recherche.
     * \endfrench
     *
     * \english
     * An iterator on the search space.  
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
         * @param begin It�rateur pointant sur la premi�re solution.
         * @param end   It�rateur pointant sur la solution apr�s la derni�re.
         * \endfrench
         *
         * \english
         * Constructor.
         *
         * @param begin Iterator on the first solution.
         * @param end   Iterator on the solution after the last one.
         * \endenglish
         */
        Iterator( const SetSearchSpace::SSSet::const_iterator begin,
                  const SetSearchSpace::SSSet::const_iterator end );
        
        virtual bool hasNext() const;
        
        virtual void next();

        virtual int x() const;

        virtual int y() const;

    protected :
        virtual SearchSpaceIterator* clone() const;

    private :
        /** 
         * \french
         * It�rateur pointant sur la solution courante. 
         * \endfrench
         *
         * \english
         * Iterator on the current solution. 
         * \endenglish
         */
        SetSearchSpace::SSSet::const_iterator m_iterator;

        /** 
         * \french
         * It�rateur pointant sur la solution apr�s la derni�re.
         * \endfrench
         *
         * \english
         * Iterator on the solution after the last one.
         * \endenglish
         */
        SetSearchSpace::SSSet::const_iterator m_end;

        /** 
         * \french
         * Est � <code>true</code> si l'it�rateur n'a pas encore avanc� 
         * \endfrench
         *
         * \english
         * Set to <code>true</code> if next has not been called yet. 
         * \endenglish
         */
        bool m_first;
    };    

    
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
     * @param x0 The search space lower bound's x coordinate.
     * @param y0 The search space lower bound's y coordinate.
     * @param x1 The search space upper bound's x coordinate.
     * @param y1 The search space upper bound's y coordinate.
     * \endenglish
     */
    SetSearchSpace( const int x0, const int y0, const int x1, const int y1 );

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~SetSearchSpace();

    /**
     * \french
     * Retourne le nombre de possibilit�s dans l'espace de recherche.
     * 
     * @return Le nombre de possibilit�s.
     * \endfrench
     *
     * \english
     * Gets the number of possibilities in the search space.
     *
     * @return The number of possibilities.
     * \endenglish
     */
    size_t size() const;
    
    bool addPossibility( const int x, const int y );

    bool isPossibility( const int x, const int y ) const;
    
    SearchSpace::Iterator getIterator() const; 

    SearchSpace::Iterator getIterator( const int y ) const;
     
    int getLowerBoundX() const;

    int getLowerBoundY() const;

    int getUpperBoundX() const;

    int getUpperBoundY() const;

private :
 
    /** 
     * \french
     * La matrice creuse contenant l'espace de recherche. 
     * \endfrench
     *
     * \english
     * The sparse matrix containing the search space. 
     * \endenglish
     */
    SSSet m_set;
    
    /** 
     * \french
     * Borne inf�rieure en x de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * Search space lower bound's x coordinate. 
     * \endenglish
     */
    int m_x0;

    /** 
     * \french
     * Borne inf�rieure en y de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * Search space lower bound's y coordinate. 
     * \endenglish
     */
    int m_y0;

    /** 
     * \french
     * Borne sup�rieure en x de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * Search space upper bound's x coordinate. 
     * \endenglish
     */
    int m_x1;

    /** 
     * \french
     * Borne sup�rieure en y de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * Search space upper bound's y coordinate. 
     * \endenglish
     */
    int m_y1;
};

}// namespace japa

#endif
