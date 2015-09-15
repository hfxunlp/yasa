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

#ifndef JAPA_CONSTANT_BEAM_MARKER
#define JAPA_CONSTANT_BEAM_MARKER

#include "solutionmarker.h"

namespace japa
{

/**
 * \french
 * Faisceau de largeur constante.
 * \endfrench
 *
 * \english
 * Beam of constant radius. 
 * \endenglish
 *
 *
 * @version 1.1
 */
class ConstantBeamMarker : public SolutionMarker
{
public :
    /** 
     * \french
     * La largeur par d�faut du rayon. 
     * \endfrench
     *
     * \english
     * The default beam radius.
     * \endenglish
     */
    static const size_t DEFAULT_RADIUS = 30;
    
    /**
     * \french
     * Constructeur.
     *
     * @param radius Le rayon du faisceau.  Si la valeur est plus petite ou 
     *               �gale � 1, le faisceau n'ajoute que les points sur 
     *               l'interpollation.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param radius The beam's radius.  0 is interpreted as 1.
     * \endenglish
     */
    ConstantBeamMarker( const size_t radius = DEFAULT_RADIUS );

    void operator()( SearchSpace& s,
                     const int pfpx, const int pfpy,
                     const int nfpx, const int nfpy,
                     const int x, const int y );
private :
    /** 
     * \french
     * Le rayon du faisceau. 
     * \endfrench
     *
     * \english
     * The beam's radius.
     * \endenglish
     */
    size_t m_radius;
};

}// namespace japa

#endif
