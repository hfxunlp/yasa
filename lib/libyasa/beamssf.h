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

#ifndef JAPA_BEAM_SSF_H
#define JAPA_BEAM_SSF_H

#include "searchspacefiller.h"
#include "solutionmarker.h"

namespace japa
{

/**
 * \french
 * Remplit un espace de recherche form�e d'un faisceau partant du coin
 * inf�rieur de l'espace de recherche jusqu'au coin sup�rieur.
 * \endfrench
 *
 * \english
 * Fill a search space with a beam starting at <code>(min, min)</code>
 * and ending at <code>(max, max)</code>.
 * \endenglish
 * 
 *
 * @version 1.1
 */
class BeamSSF : public SearchSpaceFiller
{
public :
    /**
     * \french
     * Constructeur.
     * 
     * @param marker Une r�f�rence vers un marqueur de solution.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param marker A reference pointing to a solution marker.
     * \endenglish
     */
    BeamSSF( SolutionMarker& marker );

    SearchSpace& operator()( SearchSpace& s );

private :
    /** 
     * \french
     * Le marqueur de solution. 
     * \endfrench
     *
     * \english
     * The solution marker. 
     * \endenglish
     */
    SolutionMarker& m_marker;
};

}// namespace japa
#endif
