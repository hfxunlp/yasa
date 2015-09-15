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

#ifndef JAPA_WORD_SSF_H
#define JAPA_WORD_SSF_H

#include "searchspacefiller.h"
#include "text.h"
#include "validator.h"

namespace japa
{

/**
 * \french
 * Remplit un espace de recherche en se basant sur les cognates.
 *
 * La coordonn�e en x doit correspondre � l'indice d'un mot du texte cible et la
 * coordonn�e en y � un indice d'un mot du texte source.  Quand le foncteur est
 * appel�, il ajoute des possibilit�s pour les mots qui sont cognates.
 * 
 * Une d�viance maximale d'un alignement parfait peut �tre sp�cifi�e pour 
 * permettre un traitement plus rapide.
 *
 * @note Le dictionnaire doit d�j� contenir les cognates lorsque le foncteur 
 *       est appel�.
 * \endfrench
 *
 * \english
 * Fills a search space based on texts' cognates.
 *
 * The x coordinate must correspond to the subscript of a word in the target
 * text and the y coordinate to the subscript of a word in the source text.
 * 
 * A maximal deviance to a perfect alignment can be set to speed up the
 * treatment.  This way the cognates intersection to far from the diagonal are
 * not tested.
 *
 * @note The cognate must have already been computed prior to the call to the
 *       filling function.
 * \endenglish
 *
 *
 * @version 1.1
 */
class WordSSF : public SearchSpaceFiller
{
public :
    /** 
     * \french
     * Une d�viance infinie d'un alignement parfait. 
     * \endfrench
     *
     * \english
     * An infinite deviance from a perfect alignment. 
     * \endenglish
     */
    static const size_t INFINITE_RADIUS = 0;
    
    /** 
     * \french
     * La d�viance maximum par d�faut. 
     * \endfrench
     *
     * \english
     * The default maximum deviance. 
     * \endenglish
     */
    static const size_t DEFAULT_RADIUS = INFINITE_RADIUS;
    
    /**
     * \french
     * Constructeur.
     *
     * @param source Une r�f�rence sur le texte source.
     * @param target Une r�f�rence sur le texte cible.
     * @param validator Le validateur des cognates sources.
     * @param radius La d�viance maximum.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param source A reference to the source text.
     * @param target A reference to the target text.
     * @param validator The source text cognates' validator.
     * @param radius The maximum deviance from a perfect alignment. 
     * \endenglish
     */
    WordSSF( Text& source, Text& target, Validator< WordInfo >& validator,
             const size_t radius = DEFAULT_RADIUS );

    
    SearchSpace& operator()( SearchSpace& s );

    /** 
     * \french
     * Ajuste la d�viance permise pour un cognate.
     *
     * La d�viance est l'�cart � un alignement de mot parfait.
     *
     * @param radius La nouvelle d�viance maximum.
     * \endfrench
     *
     * \english
     * Sets the maximum deviance that a cognate can have from a perfect
     * alignment.
     *
     * @param radius The new maximum deviance.
     * \endenglish
     */
    void setRadius( const size_t radius );

    /**
     * \french
     * Retourne la deviance maximum d'un alignement parfait permise.
     * 
     * @return La d�viance maximum permise.
     * \endfrench
     *
     * \english
     * Gets the maximum deviance that a cognate can have from a perfect
     * alignment.
     *
     * @return The maximum deviance.
     * \endenglish
     */
    size_t getRadius() const;
    
private :
    /** 
     * \french
     * R�f�rence vers le texte source. 
     * \endfrench
     *
     * \english
     * A reference to the source text. 
     * \endenglish
     */
    Text& m_source;

    /** 
     * \french
     * R�f�rence vers le texte cible. 
     * \endfrench
     *
     * \english
     * A reference to the target text. 
     * \endenglish
     */
    Text& m_target;

    /** 
     * \french
     * Validateur des mots sources. 
     * \endfrench
     *
     * \english
     * Source text words' validator. 
     * \endenglish
     */
    Validator< WordInfo >& m_validator;
    
    /** 
     * \french
     * La d�viance maximum. 
     * \endfrench
     *
     * \english
     * Maximum allowed deviance. 
     * \endenglish
     */
    size_t m_radius;
};

}// namespace japa

#endif
