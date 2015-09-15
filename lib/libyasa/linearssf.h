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

#ifndef JAPA_LINEAR_SSF_H
#define JAPA_LINEAR_SSF_H

#include <set>

#include "point2d.h"
#include "searchspacefiller.h"
#include "solutionmarker.h"
#include "text.h"

namespace japa
{

/**
 * \french
 * <em>( Linear search space filler )</em> Rempli un espace de recherche 
 * par intrapollation lin�aire. 
 *
 * Le remplissage est g�r� par un foncteur, ce qui rend la classe plus flexible
 * et permet de lancer des faisceau dont le rayon n'est pas constant.  Donc
 * cette classe ne fait qu'extrapoller des points.
 * \endfrench
 *
 * \english
 * <em>( Linear search space filler )</em> Fills a search space by linear
 * intrapolation.  
 *
 * A fonctor must be specified to fill each point found.  Thus, flexibility is
 * enhanced and a beam of constant or variable radius can be used.
 * \endenglish
 *  
 *
 * @version 1.1
 */
class LinearSSF : public SearchSpaceFiller
{
public :
    /**
     * \french
     * Constructeur.
     *
     * @param marker Une r�f�rence vers le marqueur de solution � utiliser. 
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param marker A reference to the solution marker.
     * \endenglish
     */
    LinearSSF( SolutionMarker& marker );

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~LinearSSF();

    /**
     * \french
     * Ajoute un point de passage qui sera utilis� lors de l'interpollation.
     *
     * Les points peuvent �tre ajout� dans n'importe quel ordre, mais seront
     * interpoll�s selon l'ordre des x, et ensuite des y. Ex :
     *
     * <p>
     * <code>( 2, 3 ) ( 1, 8 ) ( 2, 1 ) ( 7, 0 )</code>
     * </p>
     * 
     * seront interpoll�s dans l'ordre :
     *
     * <p>
     * <code>( 1, 8 ) ( 2, 1 ) ( 2, 3 ) ( 7, 0 )</code>
     * </p>
     * 
     * @param x La coordonn�e en x du point de passage.
     * @param y La coordonn�e en y du point de passage.
     * \endfrench
     *
     * \english
     * Add a passage point that will be considered during the interpolation.
     *
     * The order of insertion of the points has no importance, because the
     * points will be interpolated from left to right.
     *
     * Example :
     * 
     * <p>
     * <code>( 2, 3 ) ( 1, 8 ) ( 2, 1 ) ( 7, 0 )</code>
     * </p>
     * 
     * will be interpolated in the following order :
     *
     * <p>
     * <code>( 1, 8 ) ( 2, 1 ) ( 2, 3 ) ( 7, 0 )</code>
     * </p>

     *
     * \endenglish
     */
    void addPassagePoint( const int x, const int y );

    SearchSpace& operator()( SearchSpace& s );

private :
    /** 
     * \french
     * Le type d'un point de passage 
     * \endfrench
     *
     * \english
     * Passage point's data type. 
     * \endenglish
     */
    typedef Point2D< int > PassagePoint;
    
    /**
     * \french
     * Compare deux point de passage pour savoir laquelle est le plus petit en 
     * terme de rang de visite.
     * \endfrench
     *
     * \english
     * Compare two passage point in order to compute their precedence.  
     * \endenglish
     *
     *
     * @version 1.1
     */
    class PassagePointComparator : 
            public std::binary_function< PassagePoint, PassagePoint, bool >

    {
    public :
        /**
         * \french
         * Permet de comparer deux point de passage selon leurs rang.
         *
         * @param p1 La premi�re solution.
         * @param p2 La deuxi�me solution.
         *
         * @return <code>true</code> si p1 < p2.
         * \endfrench
         *
         * \english
         * Compare two passage points.
         *
         * @param p1 The first passage point.
         * @param p2 The second passage point.
         *
         * @return <code>true</code> if p1 < p2.
         * \endenglish
         */
        bool operator()( const PassagePoint& p1, const PassagePoint& p2 ) const;
    };

    /** 
     * \french
     * Le type de la structure contenant les points de passage. 
     * \endfrench
     *
     * \english
     * Passage points holder's data type.
     * \endenglish
     */
    typedef std::set< PassagePoint, PassagePointComparator > PointsContainer;
    
    /** 
     * \french
     * Une r�f�rence vers le marqueur de solutions. 
     * \endfrench
     *
     * \english
     * A reference to the solution marker. 
     * \endenglish
     */
    SolutionMarker& m_marker;

    /** 
     * \french
     * Contient les points de passage. 
     * \endfrench
     *
     * \english
     * Passage points holder.
     * \endenglish
     */
    PointsContainer m_passagePoints;
};

}// namespace japa

#endif
