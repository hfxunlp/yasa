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

#ifndef JAPA_SEARCH_SPACE_FILLER_H
#define JAPA_SEARCH_SPACE_FILLER_H

#include "searchspace.h"

namespace japa
{

/**
 * \french
 * Rempli un espace de recherche de solution � v�rifier.
 *
 * Cette interface permet de d�finir les possibilit�s � envisager lors de la
 * recherche de la solution optimale.
 * \endfrench
 *
 * \english
 * Interface for a search space filler.
 *
 * It allows to defined the possibilities that will be tried while searching
 * for an optimal solution.  
 * \endenglish
 *
 *
 * @version 1.1
 */
class SearchSpaceFiller
{
public :

    /**
     * \french
     * Fonction appel� pour remplir l'espace de recherche sp�cifi�e en 
     * param�tre.
     *
     * @param s L'espace de recherche � remplir.
     * 
     * @return L'espace de recherche rempli ( celle en param�tre ).
     * \endfrench
     *
     * \english
     * Fills a search space.
     *
     * @param s The search space to fill.
     *
     * @return <code>s</code> once filled.
     * \endenglish
     */
    virtual SearchSpace& operator()( SearchSpace& s ) = 0;
};

}// namespace japa

#endif
