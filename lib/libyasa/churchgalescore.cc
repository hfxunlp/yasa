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

#include <cmath>

#include "churchgalescore.h"
#include "statistic.h"

namespace japa
{

/** Valeur très grande */
static const double INCREDIBLY_BIG_DOUBLE = 1.0E30;

// ------------------------------------------------------------------------ //
ChurchGaleScore::ChurchGaleScore( const Text& src, const Text& tgt )
        : m_source( src ), m_target( tgt ), m_maxProbability( 0 ),
          m_production( DEFAULT_PRODUCTION ), m_variance( DEFAULT_VARIANCE ),
          m_matchWeight( DEFAULT_MATCH_WEIGHT ), 
          m_penaltyWeight( DEFAULT_PENALTY_WEIGHT )
{
    init();
}

// ------------------------------------------------------------------------ //
ChurchGaleScore::~ChurchGaleScore()
{}

// ------------------------------------------------------------------------ //
void ChurchGaleScore::init()
{ 
    // initialisation des alignements par défaut
    addAlignment( 1, 1, DEFAULT_PROB_11 );
    addAlignment( 0, 1, DEFAULT_PROB_01 );
    addAlignment( 1, 0, DEFAULT_PROB_10 );
    addAlignment( 1, 2, DEFAULT_PROB_12 );
    addAlignment( 2, 1, DEFAULT_PROB_21 );
    addAlignment( 2, 2, DEFAULT_PROB_22 );
}

// ------------------------------------------------------------------------ //
void ChurchGaleScore::addAlignment( const size_t lengthSource, 
                                    const size_t lengthTarget, 
                                    const double probability )
{
    bool exists = false;
    PossibleAlignments::iterator iter;
    
    if( probability > m_maxProbability )
    {
        // Met à jour les pénalités    
        m_maxProbability = probability;
        updatePenalties();
    }

    // On vérifie si l'alignement existe
    for( iter = m_alignments.begin(); iter != m_alignments.end() && !exists; 
         iter++ )
    {
        if( ( iter -> first ).first == lengthSource &&
            ( iter -> first ).second == lengthTarget )
        {
            exists = true;
            ( iter -> second ).first = probability;
            ( iter -> second ).second = computePenalty( probability );
        }
    } 

    if( !exists )
    {
        Alignment align;
        
        // L'alignement est nouveau, il faut l'ajouter.
        align.first.first = lengthSource;
        align.first.second = lengthTarget;

        align.second.first = probability;
        align.second.second = computePenalty( probability );

        m_alignments.push_back( align );
    }
}

// ------------------------------------------------------------------------ //
double ChurchGaleScore::operator()( const DynamicTable< double >& dt,
                                    const int i, const int j,
                                    int& pi, int& pj )
{    
    double score;
    double minScore = INCREDIBLY_BIG_DOUBLE;

    // Nécessaire pour l'initialisation des premières cases.
    if( i < 0 && j < 0 )
    {
        minScore = 0;
    }
    else if( i >= 0 && j >= 0 )
    {
        size_t lengthSrc;
        size_t lengthTgt;
        double penalty;
        PossibleAlignments::const_iterator iter;
        
        // Considère chacun des alignements possibles.
        for( iter = m_alignments.begin(); iter != m_alignments.end(); iter++ )
        {
            lengthSrc = ( iter -> first ).first;
            lengthTgt = ( iter -> first ).second;
            penalty = ( iter -> second ).second;
            
            if( dt.getScore( i - lengthSrc, j - lengthTgt, score ) )
            {
                score += computeScore( i, j, lengthSrc, lengthTgt, penalty );
                
                if( score < minScore )
                {
                    minScore = score;
                    pi = i - lengthSrc;
                    pj = j - lengthTgt;
                }
            }
        }
        
    }

    return minScore;
}

// ------------------------------------------------------------------------ //
double ChurchGaleScore::computeScore( const size_t sentSource, 
                                      const size_t sentTarget, 
                                      const size_t lengthSource,
                                      const size_t lengthTarget,
                                      const double penalty )
{
    size_t charSource = 0;  // Le nombre de caractères dans la section source.
    size_t charTarget = 0;  // Le nombre de caracteres dans la section cible.
    
    // Calcule la longueur en caractères du segment source
    for( size_t i = 0; i < lengthSource && sentSource >= i; i ++ )
    {
        charSource += m_source.getSentenceLength( sentSource - i );
    }     

    // Calcule la longueur en caractères du segment cible
    for( size_t i = 0; i < lengthTarget && sentTarget >= i; i ++ )
    {
        charTarget += m_target.getSentenceLength( sentTarget - i );
    }     

    return ( getMatchWeight() * match( charSource, charTarget ) ) + 
           ( getPenaltyWeight() * penalty );
}
 
// ------------------------------------------------------------------------ //
double ChurchGaleScore::match( const size_t length1, 
                               const size_t length2 ) const
{
    /* 
     * Cette fonction est très fortement inspirée du code dans le document
     * [Church & Gale]
     */
    static const double VERY_SMALL = 10E-25;
    double z;           // Variable aléatoire normale standard
    double pd;
    double mean;        
    double value = 0;   // La valeur retournée.

    if( length1 != 0 || length2 != 0 ) // évite division par 0
    {
        mean = average( length1, m_production * length2 );
        z = standardize( length1 - ( m_production * length2 ), 
                         mean, getVariance() ); 
        z = fabs( z );

        pd = 2 *( 1 - pnorm( z ) );

        
        // Démarche plutôt laide, mais si cette valeur n'est pas bornée, les 
        // suppressions ou insertions de longues phrases deviennent impossibles,
        // car la valeur devient infinie.
        // 
        // Le seuil a été choisi à peu près aléatoirement, si quelqu'un trouve 
        // une démarche pour choisir un seuil plus "intelligent", ça ne ferait
        // pas de tord.
        if( pd < VERY_SMALL )
        {
            pd = VERY_SMALL;
        }
        
        value = -log( pd );
    }

    return value;
}

// ------------------------------------------------------------------------ //
double ChurchGaleScore::computePenalty( double probability )
{
    return -log( probability / m_maxProbability );
}

// ------------------------------------------------------------------------ //
void ChurchGaleScore::updatePenalties()
{
    PossibleAlignments::iterator iter;

    for( iter = m_alignments.begin(); iter != m_alignments.end(); iter++ )
    {
        ( iter -> second ).second = 
                computePenalty( ( iter -> second ).first );
    }
}

// ------------------------------------------------------------------------ //
double ChurchGaleScore::getProduction() const
{
    return m_production;
}

// ------------------------------------------------------------------------ //
void ChurchGaleScore::setProduction( const double production )
{
    m_production = production;
}

// ------------------------------------------------------------------------ //
double ChurchGaleScore::getVariance() const
{
    return m_variance;
}

// ------------------------------------------------------------------------ //
void ChurchGaleScore::setVariance( const double variance )
{
    m_variance = variance;
}

// ------------------------------------------------------------------------ //
double ChurchGaleScore::getMatchWeight() const
{
    return m_matchWeight;
}

// ------------------------------------------------------------------------ //
void ChurchGaleScore::setMatchWeight( const double weight )
{
    m_matchWeight = weight;
}

// ------------------------------------------------------------------------ //
double ChurchGaleScore::getPenaltyWeight() const
{
    return m_penaltyWeight;
}

// ------------------------------------------------------------------------ //
void ChurchGaleScore::setPenaltyWeight( double weight )
{
    m_penaltyWeight = weight;
}

}// namespace japa
