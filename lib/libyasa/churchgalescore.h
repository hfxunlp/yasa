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

#ifndef JAPA_CHURCH_GALE_SCORE_H
#define JAPA_CHURCH_GALE_SCORE_H

#include "scorefunction.h"
#include "text.h"

#include <utility>
#include <vector>

namespace japa
{

/**
 * \french
 * Function de score pour une table dynamique impl�mentant l'algorithme de
 * Church et Gale pour l'alignement de bi-textes.
 *
 * Par d�faut, les alignements 1-1, 0-1, 1-0, 1-2, 2-1 et 2-2 sont ajout�s.
 *
 * Le calcul du score d'un alignement se fait de la fa�on suivante :
 *
 * ( Pond�rationPenalit� * Penalit� ) + ( Pond�rationMatch * Match )
 *
 * Pour avoir une fonction de score [Church & Gale] classique, les deux 
 * pond�rations doivent �tre �gales.
 * 
 * @note  La notation [Church & Gale] sera utilis�e pour r�f�rer au document :
 *        <em>A Program for Aligning Sentences in Bilingual Corpora</em> �crit
 *        par William A. Gale et Kenneth W. Church.
 * \endfrench
 *
 * \english
 * Score function implementing the Church and Gale algorithm for a dynamic 
 * table.
 *
 * Default alignment are : 1-1, 0-1, 1-0, 1-2, 2-1 and 2-2.
 *
 * The score equation looks something like this :
 *
 * ( PenaltyWeight * Penalty ) + ( MatchWeight * Match )
 * 
 * In a classic [Church & Gale] score function, penalty weight and match weight
 * are the same.
 * 
 * @note [Church & Gale] notation will be used to refer to the document :
 *       <em>A Program for Aligning Sentences in Bilingual Corpora</em> written
 *       by William A. Gale and Kenneth W. Church.
 * \endenglish
 * 
 *
 * @version 1.1
 *
 * @see ::DynamicTable
 */
class ChurchGaleScore : public ScoreFunction< double >
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
    ChurchGaleScore( const Text& src, const Text& tgt );

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~ChurchGaleScore();
    
    /**
     * \french
     * Ajoute un alignement possible.
     *
     * @param lengthSource La longueur en phrase de l'alignement dans le texte 
     *                     source.
     * @param lengthTarget La longueur en phrase de l'alignement dans le texte
     *                     cible.
     * @param probability  La probabilit� de l'alignement.
     * \endfrench
     *
     * \english
     * Add a possible alignment.
     *
     * @param lengthSource The number of sentences in source text.
     * @param lengthTarget The number of sentences in target text.
     * @param probability   The alignment probability.
     * \endenglish
     */ 
    void addAlignment( const size_t lengthSource, const size_t lengthTarget, 
                       const double probability );
    
    double operator()( const DynamicTable< double >& dt, 
                       const int i, const int j,
                       int& pi, int& pj );
    
    /**
     * \french
     * Retourne la production de caract�res.
     * 
     * @return La production des caract�res.
     * \endfrench
     *
     * \english
     * Gets the characters' production.
     *
     * @return The characters' production.
     * \endenglish
     * 
     * @see setProduction(double)
     */
    double getProduction() const;
    
    /** 
     * \french
     *  Ajuste la production des caract�res.
     *
     *  La production est le nombre de caract�res cible qu'engendre un 
     *  caract�re source en moyenne.
     *
     *  @param production La nouvelle production.
     * \endfrench
     *
     * \english
     * Sets the characters' production.
     *
     * The characthers' production is the average number of characters in the 
     * target language for each character in the source language.
     *
     * @param production The characters' production.
     * \endenglish
     */
    void setProduction( const double production );
   
    /**
     * \french
     * Retourne la variance du nombre de caract�res des phrases.
     * 
     * @return La variance.
     * \endfrench
     *
     * \english
     * Gets the sentences' length variance in characters.
     *
     * @return The sentences' length variance.
     * \endenglish
     */
    double getVariance() const;
    
    /**
     * \french
     * Ajuste la variance du nombre de caract�res des phrases.
     *
     * @param variance La nouvelle variance.
     * \endfrench
     *
     * \english
     * Sets the sentences' length variance in characters.
     *
     * @param variance The new sentences' length variance.
     * \endenglish
     */
    void setVariance( const double variance );
    
    /**
     * \french
     * Retourne la pond�ration de la partie <em>match</em> de l'algorithme de
     * [Church & Gale]
     *  
     * @return La pond�ration de la partie "match" de l'algorithme de 
     *         [Church & Gale].
     * \endfrench
     *
     * \english
     * Gets the <em>match</em>'s weight used when computing [Church & Gale] 
     * score.
     *
     * @return The <em>match</em>'s weight.
     * \endenglish
     */
    double getMatchWeight() const;

    /**
     * \french
     * Ajuste le poid de la partie <em>match</em> de l'algorithme de 
     * [Church & Gale].
     *
     * @param weight Le nouveau poid.
     * \endfrench
     *
     * \english
     * Sets the <em>match</em>'s weight used when computing [Church & Gale]
     * score.
     *
     * @param weight The new <em>match</em>'s weigth.
     * \endenglish
     */
    void setMatchWeight( const double weight );

    /**
     * \french
     * Retourne le poid de la partie <em>p�nalit�</em> de l'algorithme de
     * [Church & Gale].
     * 
     * @return Le poid de la p�nalit�.
     * \endfrench
     *  
     * \english
     * Gets the <em>penalty</em>'s weigth used when computing [Church & Gale]
     * score.
     *
     * @return The <em>penalty</em>'s weigth.
     * \endenglish
     */ 
    double getPenaltyWeight() const;

    /**
     * \french
     * Ajuste le poid de la p�nalit� de l'algorithme de Church & Gale.
     *
     * @param weight Le nouveau poid.
     * \endfrench
     *
     * \english
     * Sets the <em>penalty</em>'s weigth used when computing [Church & Gale]
     * score.
     *
     * @param weight The new <em>penalty</em>'s weigth.
     * \endenglish
     */
    void setPenaltyWeight( double weight );

    
    /** 
     * \french
     * Probabilit� d'une substition ( 1-1 ) selon [Church & Gale]. 
     * \endfrench
     *
     * \english
     * Substitution ( 1-1 ) probability as in [Church & Gale].
     * \endenglish
     */
    static constexpr double DEFAULT_PROB_11 = 0.89;

    /** 
     * \french
     * Probabilit� d'une insertion ( 0-1 ) selon [Church & Gale]. 
     * \endfrench
     *
     * \english
     * Insertion ( 0-1 ) probability as in [Church & Gale].
     * \endenglish
     */
    static constexpr double DEFAULT_PROB_01 = 0.0099;

    /** 
     * \french
     * Probabilit� d'une suppression ( 1-0 ) selon [Church & Gale]. 
     * \endfrench
     *
     * \english
     * Deletion ( 1-0 ) probability as in [Church & Gale].
     * \endenglish
     */
    static constexpr double DEFAULT_PROB_10 = 0.0099;

    /** 
     * \french
     * Probabilit� d'une expansion ( 1-2 ) selon [Church & Gale]. 
     * \endfrench
     *
     * \english
     * Expension ( 1-2 ) probability as in [Church & Gale]. 
     * \endenglish
     */
    static constexpr double DEFAULT_PROB_12 = 0.089;

    /** 
     * \french
     * Probabilit� d'une contraction ( 2-1 ) selon [Church & Gale]. 
     * \endfrench
     *
     * \english
     * Contraction ( 2-1 ) probability as in [Church & Gale].
     * \endenglish
     */
    static constexpr double DEFAULT_PROB_21 = 0.089;

    /** 
     * \french
     * Probabilit� d'une fusion ( 2-2 ) selon [Church & Gale]. 
     * \endfrench
     *
     * \english
     * Merge ( 2-2 ) probability as in [Church & Gale].
     * \endenglish
     */
    static constexpr double DEFAULT_PROB_22 = 0.011;
 
    /** 
     * \french
     * Le nombre moyen de caract�re dans le texte cible par caract�re du texte
     * source selon [Church & Gale].     
     * \endfrench
     *
     * \english
     * The average production as in [Church & Gale]. 
     * \endenglish
     */ 
    static constexpr double DEFAULT_PRODUCTION = 1;

    /**
     * \french
     * La variance par d�faut de la longueur en caract�res des phrases selon 
     * [Church & Gale].  ( moyenne de la variance anglais-allemand et 
     * anglais-fran�ais ).
     * \endfrench
     *
     * \english
     * The default variance of the sentences length in characters as in 
     * [Church & Gale] ( Average of english-deutch and english-french
     * variance ).
     * \endenglish
     */
    static constexpr double DEFAULT_VARIANCE = 6.8;
    
    /** 
     * \french
     * Le poid par d�faut du <em>match</em>. 
     * \endfrench
     *
     * \english
     * Default <em>match</em>'s weight.
     * \endenglish
     */
    static constexpr double DEFAULT_MATCH_WEIGHT  = 0.2;

    /** 
     * \french
     * Le poid de la p�nalit� par d�faut. 
     * \endfrench
     *
     * \english
     * Default <em>penalty</em>'s weight.
     * \endenglish
     */
    static constexpr double DEFAULT_PENALTY_WEIGHT = 1;

protected :    
    /**
     * \french
     * Calcule le score d'un alignement.
     *
     * @param sentSource L'indice de la phrase source.
     * @param sentTarget L'indice de la phrase cible.
     * @param lengthSource Le nombre de phrases sources.
     * @param lengthTarget Le nombre de phrases cibles.
     * @param penalty La p�nalit� associ�e � l'alignement.
     * \endfrench
     *
     * \english
     * Compute an alignment's score.
     *
     * @param sentSource Source sentence's indice.
     * @param sentTarget Target sentence's indice.
     * @param lengthSource Number of source's sentences.
     * @param lengthTarget Number of target's sentences.
     * @param penalty Alignment's penalty.
     * \endenglish
     */
    virtual double computeScore( const size_t sentSource, 
                                 const size_t sentTarget, 
                                 const size_t lengthSource,
                                 const size_t lengthTarget,
                                 const double penalty );
    
    /**
     * \french
     * Calcule la probabilit� que deux segments correspondent.
     *
     * @param length1 La longueur en caract�res du premier segment.
     * @param length2 La longueur en caract�res du deuxi�me segment.
     *
     * @return L'oppos� du logarithme de la probabilit� que les deux segments 
     *         correspondent.
     * \endfrench
     *
     * \english
     * Compute the probability that two segments are translations of each
     * others based on their lengths.
     *
     * @param length1 First segment's length in characters.
     * @param length2 Second segment's length in characters.
     *
     * @return The probability's logarithm exponent -1.
     * \endenglish
     */
    double match( const size_t length1, const size_t length2 ) const;
        
private :
    /** 
     * \french
     * Le type de la structure qui contient une possibilit� d'alignement.
     * 
     * La premi�re paire contient la longueur en phrase de l'alignement en ordre 
     * dans le texte source et le texte cible.  Alors que la deuxi�me paire 
     * contient, dans l'ordre, la probabilit� et la p�nalit�.
     * \endfrench
     *
     * \english
     * The structure that hold a possible alignment.
     *
     * The first pair contains, in the following order, the number of source's
     * sentences and target's sentences and the second pair contains, in the
     * following order, the alignment's probability and penalty.
     * \endenglish
     */
    typedef std::pair< std::pair< size_t, size_t >, 
                       std::pair< double, double > > Alignment;

    /** 
     * \french
     * Structure qui contient des alignments. 
     * \endfrench
     *
     * \english
     * Structure that hold alignments.
     * \endenglish
     */
    typedef std::vector< Alignment > PossibleAlignments;
                       
    /**
     * \french
     * Initialise la configuration de l'objet aux valeurs par d�faut.
     * \endfrench
     *
     * \english
     * Initialize the object.
     * \endenglish
     */
    void init();

    /**
     * \french
     * Calcule la p�nalit� d'un alignement selon sa probabilit�.
     *
     * @param probability La probabilit� de l'alignement.
     * 
     * @return La p�nalit� associ�e � cet alignement.
     * \endfrench
     *
     * \english
     * Compute an alignment's penalty based on its penalty.
     *
     * @param probability The alignment's probability.
     * 
     * @return The alignment's penalty.
     * \endenglish
     */
    double computePenalty( double probability );
    
    /**
     * \french
     * Met � jour toutes les p�nalit�s de tous les alignements possibles.
     * \endfrench
     *
     * \english
     * Update all the stocked alignments' penalties.
     * \endenglish
     */
    void updatePenalties();
    
    /** 
     * \french
     * R�f�rence vers le texte source. 
     * \endfrench
     *
     * \english
     * Reference to source text.
     * \endenglish
     */
    const Text& m_source;

    /** 
     * \french
     * R�f�rence vers le texte cible. 
     * \endfrench
     *
     * \english
     * Reference to target text.
     * \endenglish
     */
    const Text& m_target;

    /** 
     * \french
     * Contient les alignements possibles. 
     * \endfrench
     *
     * \english
     * Hold the alignments to check.
     * \endenglish
     */
    PossibleAlignments m_alignments;
        
    /** 
     * \french
     * La plus grande probabilit� d'un alignement. 
     * \endfrench
     *
     * \english
     * The greatest probability of all stocked alignments.
     * \endenglish
     */
    double m_maxProbability;
    
    /** 
     * \french
     * Le nombre moyen de caract�re dans le texte cible par caract�re du texte
     * source 
     * \endfrench
     *
     * \english
     * The average production.
     * \endenglish
     *
     * @see setProduction(double)
     */ 
    double m_production;

    /** 
     * \french
     * La variance de la longueur en caract�res des phrases. 
     * \endfrench
     *
     * \english
     * The sentences' variance.
     * \endenglish
     *
     * @see setVariance(double)
     */
    double m_variance;

    /** 
     * \french
     * La pond�ration du <em>match</em>. 
     * \endfrench
     *
     * \english
     * The <em>match</em>'s weight.
     * \endenglish
     */
    double m_matchWeight;

    /** 
     * \french
     * La pond�ration de la <em>p�nalit�</em>.
     * \endfrench
     *
     * \english
     * The <em>penalty</em>'s weight.
     * \endenglish
     */
    double m_penaltyWeight;
};

}// namespace japa

#endif
