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

#ifndef JAPA_WORD_SCORE_FUNCTION_H
#define JAPA_WORD_SCORE_FUNCTION_H

#include "mapsetsearchspace.h"
#include "scorefunction.h"

namespace japa
{

/**
 * \french
 * Calcule le score d'un cognate dans une table dynamique dont les coordonn�es
 * en y repr�sentent l'indice d'un mot source et les coordonn�es en x l'indice 
 * d'un mot cible.
 *
 * Le nombre de retour repr�sente le nombre de cognates pr�c�dant imm�diatement
 * celui dont le score est calcul� qu'il est permis d'ignorer.
 * \endfrench
 *
 * \english
 * Compute the score of a cognate in a dynamic table where the y coordinates
 * correspond to the source words subscripts and the x coordinates to the
 * target words subscripts.
 *
 * The number of returns define the maximum number of cognates that can be
 * ignored between two cognates.
 * \endenglish
 *
 *
 * @version 1.1
 */
class WordScoreFunction : public ScoreFunction< double >
{
public :
    /** 
     * \french
     * Le nombre de retours permis par d�faut. 
     * \endfrench
     *
     * \english
     * The default number of allowed returns. 
     * \endenglish
     */
    static const int DEFAULT_RETURN_COUNT = 50;

    /** 
     * \french
     * Le co�t par d�faut d'un retour. 
     * \endfrench
     *
     * \english
     * The default cost of a return. 
     * \endenglish
     */
    static constexpr double DEFAULT_RETURN_COST = 5;
    
    /**
     * \french
     * Constructeur.
     *
     * @param searchspace L'espace de recherche de la table dynamique.
     * @param returnCount Le nombre de retours permis.
     * @param returnCost  Le co�t d'un retour.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param searchspace A reference to the dynamic table's search space.
     * @param returnCount The number of allowed returns.
     * @param returnCost  The cost of a return. 
     * \endenglish
     */
    WordScoreFunction( const MapSetSearchSpace& searchspace,
                       const int returnCount = DEFAULT_RETURN_COUNT,
                       const double returnCost = DEFAULT_RETURN_COST );
    
    double operator()( const DynamicTable< double >& dt, 
                       const int i, const int j,
                       int& pi, int& pj );

    /**
     * \french
     * Ajuste le nombre de retours permis.
     * 
     * @param returnCount Le nouveau nombre de retours permis.
     * \endfrench
     *
     * \english
     * Sets the number of allowed returns.
     *
     * @param returnCount The new number of allowed returns. 
     * \endenglish
     */
    void setReturnCount( const int returnCount );

    /**
     * \french
     * Retourne le nombre de retours permis.
     * 
     * @return Le nombre de retours.
     * \endfrench
     *
     * \english
     * Gets the number of allowed returns.
     *
     * @return The number of returns.
     * \endenglish
     */
    int getReturnCount() const;

    /**
     * \french
     * Ajuste le co�t d'un retour.
     *
     * @param returnCost Le nouveau co�t d'un retour.
     * \endfrench
     *
     * \english
     * Sets the cost of a return.
     *
     * @param returnCost The new cost of a return. 
     * \endenglish
     */
    void setReturnCost( const double returnCost );

    /**
     * \french
     * Retourne le co�t d'un retour.
     * 
     * @return Le co�t d'un retour.
     * \endfrench
     *
     * \english
     * Gets the cost of a return.
     *
     * @return The cost of a return.
     * \endenglish
     */
    double getReturnCost() const;

private :
    /** 
     * \french
     * L'espace de recherche de la table dynamique. 
     * \endfrench
     *
     * \english
     * The search space of the dynamic table. 
     * \endenglish
     */
    const MapSetSearchSpace& m_searchspace;

    /** 
     * \french
     * Le nombre de retours permis. 
     * \endfrench
     *
     * \english
     * The number of allowed returns. 
     * \endenglish
     */
    int m_returnCount;

    /** 
     * \french
     * Le co�t d'un retour. 
     * \endfrench
     *
     * \english
     * The cost of a return. 
     * \endenglish
     */
    double m_returnCost;
};

}// namespace japa

#endif
