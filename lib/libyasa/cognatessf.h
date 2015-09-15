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

#ifndef JAPA_COGNATE_SSF_H
#define JAPA_COGNATE_SSF_H

#include "cognatessvalidator.h"
#include "dynamictable.h"
#include "searchspacefiller.h"
#include "solutionmarker.h"
#include "text.h"
#include "wordscorefunction.h"
#include "wordssf.h"

namespace japa
{

/**
 * \french
 * Remplit un espace de recherche en tenant compte des cognates ( mots
 * �quivalents ou synonymes ).
 *
 * L'algorithme selectionne des mots comme �tant des points de passage et
 * ensuite rempli un espace de recherche en lan�ant un faisceau entre ces
 * points.
 * 
 * Les cognates doivent avoir �t� ajout�s au pr�alable dans le dictionnaire du 
 * texte source.
 * \endfrench
 *
 * \english
 * Search space filler based on cognates.
 *
 * The algorithm choose passage points ( words ) and then fills a search space
 * by linking these points with a beam.
 * 
 * Before using an object of this class, the cognates must have been added to
 * the synonyms list of the source text dictionary's words.
 * \endenglish
 *
 *
 * @version 1.1
 */
class CognateSSF : public SearchSpaceFiller
{
public :
    /**
     * \french
     * Constructeur.
     *
     * @param source Une r�f�rence vers le texte source.
     * @param target Une r�f�rence vers le texte cible.
     * @param solMarker Une r�f�rence vers le marqueur de solution � utiliser.
     * @param returnCount Le nombre maximum de retour permis lorsque les 
     *                    cognates optimales sont trouv�s.
     * @param returnCost Le co�t d'un retour.
     * @param radius La d�viance maximum d'un alignement de cognates parfait 
     *               permise.
     * @param maxFrequency La fr�quence maximum d'un mot pour �tre un point de
     *                     passage.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param source Reference to the source text.
     * @param target Reference to the target text.
     * @param solMarker Reference to the solution marker.
     * @param returnCount The maximum number of return allowed in the dynamic
     *                    table
     * @param returnCost A return's <em>cost</em>
     * @param radius The radius of the beam sent between passage points.
     * @param maxFrequency The maximum frequency of a word to be a passage
     * \endenglish
     */ 
    CognateSSF( Text& source, Text& target, 
                SolutionMarker& solMarker,
                const int returnCount = WordScoreFunction::DEFAULT_RETURN_COUNT,
                const double returnCost = WordScoreFunction::DEFAULT_RETURN_COST,
                const size_t radius = WordSSF::DEFAULT_RADIUS,
                const size_t maxFrequency = CognateSSValidator::DEFAULT_MAX_FREQUENCY );
    
    SearchSpace& operator()( SearchSpace& s );
    
private :
    /**
     * \french
     * Remplit l'espace de recherche des phrases � partir de la solution 
     * optimale de l'alignement des cognates.
     *
     * @param searchspace Une r�f�rence vers l'espace de recherche � remplir.
     * @param wordDT Le table contenant la solution optimale de l'alignement 
     *               des cognates.
     * \endfrench
     *
     * \english
     * Fill the sentences' search space based on the optimal word alignment.
     *
     * @param searchspace A reference to the search space to fill.
     * @param wordDT Dynamic table containing the word alignment optimal
     *               solution
     * \endenglish
     */
    void fill( SearchSpace& searchspace, 
               DynamicTable< double >& wordDT ) const;
    
    /** 
     * \french
     * Une r�f�rence vers le texte source. 
     * \endfrench
     *
     * \english
     * A reference to the source text.
     * \endenglish
     */
    Text& m_source;

    /** 
     * \french
     * Une r�f�rence vers le texte cible. 
     * \endfrench
     *
     * \english
     * A reference to the target text.
     * \endenglish
     */
    Text& m_target;

    /** 
     * \french
     * Une r�f�rence vers le marqueur de solution. 
     * \endfrench
     *
     * \english
     * A reference to the solution marker.
     * \endenglish
     */
    SolutionMarker& m_solMarker;

    /** 
     * \french
     * Le nombre maximum de retours permis. 
     * \endfrench
     *
     * \english
     * The maximum number of returns allowed.
     * \endenglish
     */
    const int m_returnCount;

    /** 
     * \french
     * Le co�t d'un retour. 
     * \endfrench
     *
     * \english
     * A return's cost.
     * \endenglish
     */
    const double m_returnCost;

    /** 
     * \french
     * La d�viance maximum d'un alignement de cognate parfait permise. 
     * \endfrench
     *
     * \english
     * The radius of the beam sent between passage points.
     * \endenglish
     */
    const size_t m_radius;

    /** 
     * \french
     * La fr�quence maximum d'un mot servant de point de rep�re. 
     * \endfrench
     *
     * \english
     * The maximum frequency of a word serving as a passage point.
     * \endenglish
     */
    const size_t m_maxFrequency;
};

}// namespace japa

#endif
