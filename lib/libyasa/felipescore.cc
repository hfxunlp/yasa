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

#include <list>
#include <cmath>

#include "felipescore.h"

namespace japa
{

// ------------------------------------------------------------------------ //
FelipeScore::FelipeScore( const Text& src, const Text& tgt ) 
        : ChurchGaleScore( src, tgt ), m_source( src ), m_target( tgt )
{
    init();
}

// ------------------------------------------------------------------------ //
void FelipeScore::init()
{
    setChurchGaleWeight( DEFAULT_CHURCH_GALE_WEIGHT );
    setSimardWeight( DEFAULT_SIMARD_WEIGHT );
    m_cpt = DEFAULT_CPT;
    m_cpnt = DEFAULT_CPNT;
    updateBinomial ();
    setMode( DEFAULT_MODE );
    setCorrection( DEFAULT_CORRECTION );
}

// ------------------------------------------------------------------------ //
double FelipeScore::computeScore( const size_t sentSource, 
                                  const size_t sentTarget, 
                                  const size_t lengthSource,
                                  const size_t lengthTarget,
                                  const double penalty )
{
    double simardScore;
    double churchGaleScore;

    simardScore = computeSimardScore( sentSource, sentTarget, 
                                      lengthSource, lengthTarget );

    churchGaleScore = ChurchGaleScore::computeScore( sentSource, sentTarget,
                                                     lengthSource, lengthTarget,
                                                     penalty );
 
    // Gère le mode FullFelipe
    if( lengthSource == 0 || lengthTarget == 0 )
    {
        switch( getMode() )
        {
        case CHURCHGALE :
            churchGaleScore /= getCorrection();
            break;
            
        case SIMARD :
            simardScore /= getCorrection();
            break;

        case ALL :
            churchGaleScore /= getCorrection();
            simardScore /= getCorrection();
            break;
        }
    }
    
    return ( getSimardWeight() * simardScore ) + 
           ( getChurchGaleWeight() * churchGaleScore );
}

// ------------------------------------------------------------------------ //
double FelipeScore::computeSimardScore( const size_t sentSource, 
                                        const size_t sentTarget, 
                                        const size_t lengthSource,
                                        const size_t lengthTarget ) const
{
    double score;
    size_t wordCount = 0;   // Le nombre moyen de mots
    size_t cognateCount = 0;// Le nombre de cognates

    //  Rescence les mots de la région source
    for( size_t i = 0; i < lengthSource && sentSource >= i; i ++ )
    {
        wordCount += m_source.getSentenceWordCount( sentSource - i );
    }
    
    //  Rescence les mots de la région cibles
    for( size_t i = 0; i < lengthTarget && sentTarget >= i; i ++ )
    {
        wordCount += m_target.getSentenceWordCount( sentTarget - i );
    }

    wordCount /= 2;

    cognateCount = countCognate( sentSource, sentTarget, 
                                 lengthSource, lengthTarget );
 
    // Calcul du score de Simard suivant une loi binômiale   
    score = ( cognateCount * m_r1 ) + ( ( wordCount - cognateCount ) * m_r2 );
    
    return score;
}

// ------------------------------------------------------------------------ //
double FelipeScore::getChurchGaleWeight() const
{
    return m_churchGaleWeight;
}

// ------------------------------------------------------------------------ //
void FelipeScore::setChurchGaleWeight( const double weight )
{
    m_churchGaleWeight = weight;
}

// ------------------------------------------------------------------------ //
double FelipeScore::getSimardWeight() const
{
    return m_simardWeight;
}

// ------------------------------------------------------------------------ //
void FelipeScore::setSimardWeight( const double weight )
{
    m_simardWeight = weight;
}

// ------------------------------------------------------------------------ //
double FelipeScore::getCPT() const
{
    return m_cpt;
}

// ------------------------------------------------------------------------ //
void FelipeScore::setCPT( const double probability )
{
    m_cpt = probability;
    updateBinomial();
}

// ------------------------------------------------------------------------ //
double FelipeScore::getCPNT() const
{
    return m_cpnt;
}

// ------------------------------------------------------------------------ //
void FelipeScore::setCPNT( const double probability )
{
    m_cpnt = probability;
    updateBinomial();
}

// ------------------------------------------------------------------------ //
void FelipeScore::setMode( const FullFelipeMode mode )
{
    m_mode = mode;
}

// ------------------------------------------------------------------------ //
FullFelipeMode FelipeScore::getMode() const
{
    return m_mode;
}

// ------------------------------------------------------------------------ //
void FelipeScore::setCorrection( const double correction )
{
    m_correction = correction;
}


// ------------------------------------------------------------------------ //
double FelipeScore::getCorrection() const
{
    return m_correction;
}

// ------------------------------------------------------------------------ //
void FelipeScore::updateBinomial()
{
    m_r1 = -log( getCPT() / getCPNT() );
    m_r2 = -log( ( 1 - getCPT() ) / ( 1 - getCPNT() ) );
}

// ------------------------------------------------------------------------ //
int FelipeScore::countCognate( const size_t sentSource, 
                               const size_t sentTarget, 
                               const size_t lengthSource, 
                               const size_t lengthTarget ) const
{
    
    size_t beginSrc;
    size_t endSrc;
    size_t beginTgt;
    size_t endTgt;
    size_t cognateCount = 0;    // Le nombre de cognates
    std::list< WordInfo* > targetWords;   // Les mots déjà pris
    std::list< WordInfo* >::iterator iter;
    bool found = false;    
    
    // Initialise la liste des mots cibles
    for( size_t i = 0; i < lengthTarget && sentTarget >= i; i ++ )
    {
        m_target.getSentenceBounds( sentTarget - i, beginTgt, endTgt );

        for( size_t j = beginTgt; j < endTgt; j++ )
        {
            targetWords.push_back( &( m_target.getWord( j ) ) );
        }
    }     

    // Compte le nombre de cognates
    for( size_t i = 0; i < lengthSource && sentSource >= i; i ++ )
    {
        m_source.getSentenceBounds( sentSource - i, beginSrc, endSrc );

        for( size_t j = beginSrc; j < endSrc; j++ )
        {
            found = false;
            
            // Si le mot source a des synonymes, on vérifie s'il y en a un dans
            // le bout de texte cible
            if( m_source.getWord( j ).hasSynonym() )
            {
                for( iter = targetWords.begin(); iter != targetWords.end() && !found; 
                     iter++ )
                {
                    if( m_source.getWord( j ).isSynonym( *( *iter ) ) ) 
                    {
                        // Un cognate est trouvé
                        found = true;
                        cognateCount++;
                        targetWords.erase( iter );
                    }
                }
            }
        }
    }     
    
    return cognateCount;
}

}// namespace japa
