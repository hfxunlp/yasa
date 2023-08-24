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

#ifndef JAPA_FELIPE_SCORE_H
#define JAPA_FELIPE_SCORE_H

#include "churchgalescore.h"
#include "text.h"

namespace japa
{

/**
 * \french
 * Les modes FullFelipe.
 * 
 * Les modes FullFelipe permettent d'apporter un correction au score lors
 * d'insertion ou de suppression ( 0-x ou x-0 ).
 * \endfrench
 *
 * \english
 * FullFelipe modes.
 *
 * FullFelipe modes allow to correct insertion's and deletion's score ( 0-x or
 * x-0 )
 * \endenglish
 */
typedef enum
{
    /** 
     * \french
     * Seulement le score Church and Gale est corrig�. 
     * \endfrench
     *
     * \english
     * Only Church and Gale's score is corrected.
     * \endenglish
     */
    CHURCHGALE, 
    /** 
     * \french
     * Seulement le score Simard est corrig�. 
     * \endfrench
     *
     * \english
     * Only Simard's score is corrected.
     * \endenglish
     */
    SIMARD,     
    /** 
     * \french
     * Le score total est corrig�. 
     * \endfrench
     *
     * \english
     * The global score is corrected.
     * \endenglish
     */
    ALL,        
    /** 
     * \french
     * Aucune correction. 
     * \endfrench
     *
     * \english
     * No correction.
     * \endenglish
     */
    NONE        
}FullFelipeMode;

/**
 * \french
 * Fonction de score pour une table dynamique impl�mentant l'algorithme de
 * Felipe pour l'alignement de bi-textes.
 *
 * L'algorithme Felipe utilise le score de Church & Gale, mais prend aussi en 
 * compte les cognates ( mots �quivalents ).
 * \endfrench
 *
 * \english
 * Felipe score function to use with a \link ::DynamicTable 
 * dynamic table \endlink.
 *
 * Felipe score function uses Church and Gale's score but also takes into
 * consideration cognates and synonyms.  It also allows to weight these
 * scores.
 * \endenglish
 *
 *
 * @version 1.1
 *
 * @see ::DynamicTable
 */
class FelipeScore : public ChurchGaleScore
{
public :
    /**
     * \french
     * Constructeur.
     *
     * @param src Une r�f�rence vers le texte source.
     * @param tgt Une r�f�rence vers le texte cible.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param src A reference to the source text.
     * @param tgt A reference to the target text.
     * \endenglish
     */
    FelipeScore( const Text& src, const Text& tgt );

    /**
     * \french
     * Retourne la poid du score Church and Gale lors du calcul du score
     * Felipe.
     * 
     * @return La pond�ration du score Church and Gale
     * \endfrench
     *
     * \english
     * Gets the Churh and Gale score function's weight in the Felipe's score.
     *
     * @return The Churh and Gale score function's weight.
     * \endenglish
     */
    double getChurchGaleWeight() const;

    /**
     * \french
     * Ajuste la pond�ration du calcule de score selon la m�thode Church & Gale.
     *
     * @param weight La nouvelle pond�ration.
     * \endfrench
     *
     * \english
     * Sets the Church and Gale score function's weight in the Felipe's score.
     *
     * @param weight The new Church and Gale score function's weigth.
     * \endenglish
     */
    void setChurchGaleWeight( const double weight );

    /**
     * \french
     * Retourne la pond�ration du calcul de score selon la m�thode des cognates
     * de Simard dans le calcul du score Felipe.
     * 
     * @return La pond�ration du score de Simard.
     * \endfrench
     *
     * \english
     * Gets the Simard score function's weight in the Felipe's score.
     * 
     * @return The Simard score function's weight.
     * \endenglish
     */
    double getSimardWeight() const;

    /**
     * \french
     * Ajuste la pond�ration du calcul de score selon la m�thode des cognates
     * de Simard.
     *
     * @param weight La nouvelle pond�ration.
     * \endfrench
     *
     * \english
     * Sets the Simard score function's weight in the Felipe's score.
     *
     * @param weight The new Simard score function's weight.
     * \endenglish
     */
    void setSimardWeight( const double weight );
   
    /**
     * \french
     * Retourne la probabilit� qu'un mot ait un cognate dans deux phrases qui
     * sont traductions l'une de l'autre.
     * 
     * @note <code>getCPT</code> = getCognateProbabilityInTraduction
     * 
     * @return La probabilit�.
     * \endfrench
     * 
     * \english
     * Gets the probability that a word has a cognate in two sentences that
     * are traductions of each other.
     *
     * @note <code>getCPT</code> stands for getCognateProbabilityInTraduction.
     *
     * @return The probability.
     * \endenglish
     */
    double getCPT() const;

    /**
     * \french
     * Ajuste la probabilit� qu'un mot ait un cognate dans deux phrases qui
     * sont traductions l'une de l'autre.
     * 
     * @note <code>setCPT</code> = setCognateProbabilityInTraduction
     *
     * @param probability La probabilit�.
     * \endfrench
     *
     * \english
     * Sets the probability that a word has a cognate in two sentences that
     * are traductions of each other.
     *
     * @note <code>setCPT</code> stands for setCognateProbabilityInTraduction.
     *
     * @param probability The probability.
     * \endenglish
     */
    void setCPT( const double probability );
 
    /**
     * \french
     * Retourne la probabilit� qu'un mot ait un cognate dans deux phrases qui
     * ne sont pas traductions l'une de l'autre.
     * 
     * @note <code>getCNPT</code> = getCognateProbabilityNotInTraduction
     * 
     * @return La probabilit�.
     * \endfrench
     * 
     * \english
     * Gets the probability that a word has a cognate in two sentences that
     * are not traductions of each other.
     *
     * @note <code>getCNPT</code> stands for 
     *       getCognateProbabilityNotInTraduction.
     *
     * @return The probability.
     * \endenglish
     */
    double getCPNT() const;

    /**
     * \french
     * Ajuste la probabilit� qu'un mot ait un cognate dans deux phrases qui
     * ne sont pas traductions l'une de l'autre.
     * 
     * @note <code>setCNPT</code> = setCognateProbabilityNotInTraduction
     *
     * @param probability La probabilit�.
     * \endfrench
     *
     * \english
     * Sets the probability that a word has a cognate in two sentences that
     * are not traductions of each other.
     *
     * @note <code>setCNPT</code> stands for 
     *       setCognateProbabilityNotInTraduction.
     *
     * @param probability The probability.
     * \endenglish
     */
    void setCPNT( const double probability );   

    /**
     * \french
     * Ajuste le mode FullFelipe.
     *
     * @param mode Le nouveau mode FullFelipe.
     * \endfrench
     *
     * \english
     * Sets the FullFelipe mode.
     *
     * @param mode The new FullFelipe mode.
     * \endenglish
     */
    void setMode( const FullFelipeMode mode );

    /**
     * \french
     * Retourne le mode FullFelipe courant.
     * 
     * @return Le mode FullFelipe.
     * \endfrench
     *
     * \english
     * Gets the current FullFelipe mode.
     *
     * @return The FullFelipe mode.
     * \endenglish
     */
    FullFelipeMode getMode() const;

    /**
     * \french
     * Ajuste la correction FullFelipe.
     *
     * La correction FullFelipe est appliqu� quand la longueur de la source ou
     * de la cible d'un alignement est 0.  La correction consiste � diviser le
     * score concern� par le mode FullFelipe par la valeur de correction.
     *
     * @param correction La correction � appliqu�e.
     * \endfrench
     *
     * \english
     * Sets the FullFelipe correction.
     *
     * The FullFelipe correction is applied on alignment where the source's
     * or target's length is 0.  The correction divided the score concerned by
     * the FullFelipe mode by the value of the parameter.
     *
     * @param correction The applyed correction.
     * \endenglish
     */
    void setCorrection( const double correction );

    /**
     * \french
     * Retourne la correction FullFelipe.
     * 
     * @return La correction FullFelipe.
     * \endfrench
     *
     * \english
     * Gets the FullFelipe correction.
     *
     * @return The correction value.
     * \endenglish
     */
    double getCorrection() const;
    
    /** 
     * \french
     * La pond�ration par d�faut du score de Church & Gale. 
     * \endfrench
     *
     * \english
     * The default weight of the Church and Gale's score function.
     * \endenglish
     */ 
    static constexpr double DEFAULT_CHURCH_GALE_WEIGHT = 1;

    /** 
     * \french
     * La pond�ration par d�fault du calcul du score selon Simard. 
     * \endfrench
     *
     * \english
     * The default weight of the Simard's score function.
     * \endenglish
     */
    static constexpr double DEFAULT_SIMARD_WEIGHT = 0.85;

    /** 
     * \french
     * La probabilit� par d�faut qu'un mot aient un cognates lorsque deux
     * phrases sont traductions l'une de l'autre.
     * \endfrench
     *
     * \english
     * The default probability that a word has a cognate in two sentences that
     * are traductions of each other.
     * \endenglish
     */
    static constexpr double DEFAULT_CPT = 0.3;

    /**
     * \french
     * La probabilit� par d�faut qu'un mot ait un cognate dans deux phrases qui
     * ne sont pas traductions l'une de l'autre.
     * \endfrench
     *
     * \english
     * The default probability that a word has a cognate in two sentences that
     * are not traductions of each other.
     * \endenglish
     */
    static constexpr double DEFAULT_CPNT = 0.09;

    /** 
     * \french
     * Mode FullFelipe par d�faut. 
     * \endfrench
     *
     * \english
     * Default FullFelipe mode.
     * \endenglish
     */
    static const FullFelipeMode DEFAULT_MODE = ALL;

    /** 
     * \french
     * Correction FullFelipe par d�faut. 
     * \endfrench
     *
     * \english
     * Default FullFelipe correction.
     * \endenglish
     */
    static constexpr double DEFAULT_CORRECTION = 2;

protected :
    
    virtual double computeScore( const size_t sentSource, 
                                 const size_t sentTarget, 
                                 const size_t lengthSource,
                                 const size_t lengthTarget,
                                 const double penalty );
    /**
     * \french
     * Calcule le score selon l'algorithme de Simard sur les cognates.
     *
     * @param sentSource L'indice de la derni�re phrase de la r�gion dans le 
     *                   texte source.
     * @param sentTarget L'indice de la derni�re phrase de la r�gion dans le 
     *                   texte cible.
     * @param lengthSource Le nombre de phrase dans la r�gion du texte source.
     * @param lengthTarget Le nombre de phrase dans la r�gion du texte cible.
     *
     * @return Le score selon l'algorithme de Simard.
     * \endfrench
     *
     * \english
     * Compute the Simard's score which depends on cognates.
     *
     * @param sentSource The last sentence's indice of the source segment.
     * @param sentTarget The last sentence's indice of the target segment.
     * @param lengthSource The number of sentences in the source segment.
     * @param lengthTarget The number of sentences in the target segment.
     *
     * @return The Simard's score.
     * \endenglish
     */
    double computeSimardScore( const size_t sentSource, 
                               const size_t sentTarget, 
                               const size_t lengthSource,
                               const size_t lengthTarget ) const;
    
    /**
     * \french
     * Trouve le nombre de cognate commun � deux r�gions.
     *
     * @param sentSource L'indice de la derni�re phrase de la r�gion dans le 
     *                   texte source.
     * @param sentTarget L'indice de la derni�re phrase de la r�gion dans le 
     *                   texte cible.
     * @param lengthSource Le nombre de phrase dans la r�gion du texte source.
     * @param lengthTarget Le nombre de phrase dans la r�gion du texte cible.
     *
     * @return Le nombre de cognates dans les deux r�gions.
     * \endfrench
     *
     * \english
     * Compute the number of cognates in two segments.
     *
     * @param sentSource The last sentence's indice of the source segment.
     * @param sentTarget The last sentence's indice of the target segment.
     * @param lengthSource The number of sentences in the source segment.
     * @param lengthTarget The number of sentences in the target segment.
     *
     * @return The number of cognates in the two segments.
     * \endenglish
     */
    int countCognate( const size_t sentSource, 
                      const size_t sentTarget, 
                      const size_t lengthSource, 
                      const size_t lengthTarget ) const;

private :
    /**
     * \french
     * Initialise l'�tat de l'objet.
     * \endfrench
     *
     * \english
     * Initialize the object.
     * \endenglish
     */
    void init();
    
    /**
     * \french
     * Met � jour les variables utilis�es pour calculer la loi bin�miale 
     * utilis�e dans Simard.
     * \endfrench
     *
     * \english
     * Update the variables involved in the computing of the binomial law used
     * in the Simard's score.
     * \endenglish
     */
    void updateBinomial();
    
    /** 
     * \french
     * Une r�f�rence vers le texte source. 
     * \endfrench
     *
     * \english
     * A reference to the source text.
     * \endenglish
     */
    const Text& m_source;

    /** 
     * \french
     * Une r�f�rence vers le texte cible. 
     * \endfrench
     *
     * \english
     * A reference to the target text.
     * \endenglish
     */
    const Text& m_target;
    
    /** 
     * \french
     * La pond�ration du score selon Gale & Church. 
     * \endfrench
     *
     * \english
     * The Church and Gale score function's weight.
     * \endenglish
     */
    double m_churchGaleWeight;

    /** 
     * \french
     * La pond�ration du score selon les cognates de Simard. 
     * \endfrench
     *
     * \english
     * The  Simard's score function's weight.
     * \endenglish
     */
    double m_simardWeight;

    /** 
     * \french
     * La probabilit� qu'un mot ait un cognate dans deux phrases qui
     * sont traductions l'une de l'autre.
     * \endfrench
     *
     * \english
     * The probability that a word has a cognate in two sentences that
     * are traductions of each other.
     * \endenglish
     */
    double m_cpt;

    /** 
     * \french
     * La probabilit� qu'un mot ait un cognate dans deux phrases qui
     * ne sont pas traductions l'une de l'autre.
     * \endfrench
     *
     * \english
     * The probability that a word has a cognate in two sentences that
     * are not traductions of each other.
     * \endenglish
     */
    double m_cpnt;

    /** 
     * \french
     * Utilis� pour calculer le score de Simard. 
     * \endfrench
     *
     * \english
     * Involved in Simard's score.
     * \endenglish
     */
    double m_r1;

    /** 
     * \french
     * Utilit� pour calculer le score de Simard. 
     * \endfrench
     *
     * \english
     * Involved in Simard's score.
     * \endenglish
     */
    double m_r2;
    
    /** 
     * \french
     * Le mode FullFelipe. 
     * \endfrench
     *
     * \english
     * The FullFelipe mode.
     * \endenglish
     */
    FullFelipeMode m_mode;

    /** 
     * \french
     * La correction � apporter en mode FullFelipe. 
     * \endfrench
     *
     * \english
     * The FullFelipe correction.
     * \endenglish
     */
    double m_correction;
};

}// namespace japa

#endif
