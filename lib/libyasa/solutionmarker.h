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

#ifndef JAPA_SOLUTION_MARKER_H
#define JAPA_SOLUTION_MARKER_H

#include "searchspace.h"
#include "text.h"

namespace japa
{

/**
 * \french
 * Sp�cifie la fa�on dont un point extrapoll� doit affect� un espace de 
 * recherche.
 *
 * Cette classe permet de sp�cifier si le faisceau entre deux point fixe sera
 * de rayon constant, la largeur de ce rayon, etc...
 * \endfrench
 *
 * \english
 * Specify how a point is marked in a search space.
 *
 * This class allow to specify if a beam sent between two points will have a
 * constant radius, a fixed radius, the size of the radius, etc...  
 * \endenglish
 *
 *
 * @version 1.1
 */
class SolutionMarker
{
public :
    /**
     * \french
     * Fonction permettant de marquer une possibilit� dans l'espace de
     * recherche.
     *
     * @param s L'espace de recherche � marquer.
     * @param pfpx La coordonn�e en x du point fix pr�c�dent. 
     *             ( previous fixed point x )
     * @param pfpy La coordonn�e en y du point fix pr�c�dent.
     *             ( previous fixed point y )
     * @param nfpx La coordonn�e en x du point fix suivant. 
     *             ( previous fixed point x )
     * @param nfpy La coordonn�e en y du point fix suivant.
     *             ( previous fixed point y )
     * @param x La coordonn�e en x du point � marquer.
     * @param y La coordonn�e en y du point � marquer.          
     * \endfrench
     *
     * \english
     * Marks a possibility in the search space.
     *
     * @param s The search space to fill.
     * @param pfpx The x coordinate of the previous fixed point.
     * @param pfpy The y coordinate of the previous fixed point.
     * @param nfpx The x coordinate of the next fixed point.
     * @param nfpy The y coordinate of the next fixed point.
     * @param x The x coordinate of the point to mark.
     * @param y The y coordinate of the point to mark.
     * \endenglish
     */
    virtual void operator()( SearchSpace& s,
                             const int pfpx, const int pfpy,
                             const int nfpx, const int nfpy,
                             const int x, const int y ) = 0;
};

}// namespace japa

#endif
