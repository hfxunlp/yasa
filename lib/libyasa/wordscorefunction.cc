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

#include "searchspace.h"
#include "wordscorefunction.h"
#include "iostream"

using namespace std;

namespace japa
{

/** Valeur très grande */
static const double INCREDIBLY_BIG_DOUBLE = 1.0E30;


// ------------------------------------------------------------------------ //
WordScoreFunction::WordScoreFunction( const MapSetSearchSpace& searchspace,
                                      const int returnCount,
                                      const double returnCost )
        : m_searchspace( searchspace ),
          m_returnCount( returnCount ),
          m_returnCost( returnCost )
{}



// ------------------------------------------------------------------------ //
double WordScoreFunction::operator()( const DynamicTable< double >& dt,
                                      const int i, const int j,
                                      int& pi, int& pj )
{
    double score = INCREDIBLY_BIG_DOUBLE;   // Le meilleur score rencontré
    double scoreTemp;                       // Score courant
    double delta;                           // La pente de l'espace de recherche
    int r = 0;                              // Le numéro du retour courant
    bool first;                             // Indique si premier essaie  
    int dx;
    int dy;

    MapSetSearchSpace::Row::const_iterator rowIter;
    MapSetSearchSpace::Column::const_iterator colIter;

    //ma partie

    //cout << "AAAAAAAAAAAAAAAAA" << endl;

    //ma partie

    delta = ( ( double ) 
                    ( m_searchspace.getUpperBoundX() - 
                      m_searchspace.getLowerBoundX() ) ) /
                    ( m_searchspace.getUpperBoundY() -
                      m_searchspace.getLowerBoundY() );

    //delta = ( double ) i/j;

    //cout << "J: " << j << " I: " << i << endl;
    //ma partie

    //for( rowIter = m_searchspace.begin(); rowIter != m_searchspace.end(); rowIter++ )
    //{
    //	for( colIter = ( rowIter -> second ).begin(); colIter != ( rowIter -> second ).end(); colIter++ )
    //		cout << "J: " << rowIter -> first << " I: " << *colIter << endl;
    //}
    //cout << "apel de j,i: " << j << " , " << i << endl;

    //ma partie
    //cout << "On est dans la fonction de score" << endl;

    // Faire le nombre de retours nécessaires
    for( rowIter = ++( m_searchspace.find( j ) );
         rowIter != m_searchspace.end() && r <= getReturnCount(); rowIter++ )
    {
    	//cout << "La boucle de X pour notre X a traiter " << rowIter -> first << endl;
        first = true;
        
        // Nous ne regardons que les mots précédents
        for( colIter = ( rowIter -> second ).begin(); 
             colIter != ( rowIter -> second ).end() && *colIter <= i;
             colIter++ )
        {
        	//cout << "La boucle de Y pour notre Y a traiter " << *colIter << endl;


            if( dt.getScore( *colIter, rowIter -> first, scoreTemp ) )
            {
                // Le score est définit par l'écart à la pente, le nombre
                // de saut effectués et le score du précédent.

                dx = i - *colIter;
                dy = j - ( rowIter -> first );

                //mon score
                scoreTemp += (fabs( ( ( double )dx ) - dy ) * delta) + (( r - 1 ) * getReturnCost() );
                //mon score

                //scoreTemp += (fabs( ( ( double )dx ) / dy ) - delta) + (( r - 1 ) * getReturnCost() );

                
                //scoreTemp += fabs( dx - ( delta * dy ) ) + ( ( r - 1 ) * getReturnCost() );
                
                //cout << "Le score actuel est: " << scoreTemp << endl;

                if( first )
                            {
                                // C'est un retour
                                r++;
                                first = false;
                            }

                // Si c'est la meilleure solution rencontrée
                if( scoreTemp < score )
                {
                	//cout << "Le nouveau score pour X,Y " << rowIter -> first << " , " << *colIter << " est " << score << endl;
                	//cout << rowIter -> first << "  " << *colIter << endl;

                    score = scoreTemp;
                    pi = *colIter;
                    pj = rowIter -> first;
                }
            }                
        }
    }

    if( r == 0 )
    {
        // Aucun cognate précédent         
        if( j != 0 )
        {
            // Le score est définit par l'écart à la pente
        	score =( double ) (i/ j) * delta ;
        	//cout << "X,Y= .. " << rowIter -> first << " , " << *colIter << " est " << score << endl;
        	//score = fabs( i - ( delta * j ) );
        }
        else /*if( i == 0 )*/// j == 0
        {
            score = i * delta; // Plus il y a de mots cibles par mot source,
                               // plus le mot cible associé au premier mot
                               // source peut être loin.
        }
    }
    //cout <<"J: " << j << "I: " << i << "score" << score << endl;

    return score;
}

// ------------------------------------------------------------------------ //
void WordScoreFunction::setReturnCount( const int returnCount )
{
    m_returnCount = returnCount;
}

// ------------------------------------------------------------------------ //
int WordScoreFunction::getReturnCount() const
{
    return m_returnCount;
}

// ------------------------------------------------------------------------ //
void WordScoreFunction::setReturnCost( const double returnCost )
{
    m_returnCost = returnCost;
}

// ------------------------------------------------------------------------ //
double WordScoreFunction::getReturnCost() const
{
    return m_returnCost;
}

}// namespace japa
