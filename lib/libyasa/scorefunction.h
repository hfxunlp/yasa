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

#ifndef JAPA_SCORE_FUNCTION_H
#define JAPA_SCORE_FUNCTION_H

#include "dynamictable.h"

namespace japa
{

/**
 * \french
 * Foncteur pour calculer le score d'une cellule dans une table dynamique.
 *
 * @param T Le type de donn�e du score.
 * \endfrench
 *
 * \english
 * Fonctor that compute the score of a dynamic table's cell.
 *
 * @param T The score's data type.
 * \endenglish
 *
 *
 * @version 1.1
 *
 * @see ::DynamicTable
 */
template< class T >
class ScoreFunction
{
public :
    /**
     * \french
     * Calcule le score d'une cellule d'une table dynamique.
     *
     * Post-condition : Si aucune cellule n'est pr�c�dente, les valeurs de 
     *                  <code>pi</code> et <code>pj</code> doivent rester
     *                  inchang�es. 
     *
     * @param dt La table dynamique contenant la cellule.
     * @param i  Le num�ro de la colonne de la cellule.
     * @param j  Le num�ro de la ligne de la cellule.
     * @param pi ( out ) Le num�ro de la colonne de la cellule pr�c�dente.
     *           ( utilis� pour reconstruire la solution ).
     * @param pj ( out ) Le num�ro de la ligne de la cellule pr�c�dente.
     *           ( utilis� pour reconstruire la solution ).
     *
     * @return Le score attribu� � la cellule.
     * \endfrench
     *
     * \english
     * Compute the score of a dynamic table's cell. 
     *
     * Post-condition : If there's is no preceding cell, the values of 
     *                  <code>pi</code> and <code>pj</code> must stay
     *                  unchanged.
     *
     * @param dt The dynamic table that owns the cell.
     * @param i  The column number of the cell.
     * @param j  The row number of the cell.
     * @param pi ( out ) The previous column number. 
     *           ( Necessary to rebuild the solution )
     * @param pj ( out ) The previous row number.
     *           ( Necessary to rebuild the solution )
     * 
     * @return The cell's score.              
     * \endenglish
     */
    virtual T operator()( const DynamicTable< T >& dt, 
                          const int i, const int j,
                          int& pi, int& pj ) = 0;
};

}// namespace japa

#endif
