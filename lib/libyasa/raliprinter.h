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


#ifndef JAPA_RALI_PRINTER_H
#define JAPA_RALI_PRINTER_H

#include "solutionprinter.h"

namespace japa
{

/**
 * \french
 * Imprime une solution dans le format RALI.
 *
 * Le format RALI est une suite de triplets respectant le format suivant :
 * \<Nombre Phrase Source\>-\<Nombre Phrase Cible\> \<Score\>
 * 
 * @param T Le type de donn�e du score.
 * \endfrench
 *
 * \english
 * Print an alignment in the RALI format.
 *
 * The RALI format is a sequence of triplets in the following format :
 * \<Number of source sentences\>-\<Number of target sentences\> \<score\>
 *
 * @param T The score's data type.
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class RaliPrinter : public SolutionPrinter< T >
{
public :
    /** 
     * \french
     * Le type de donn�e de la solution. 
     * \endfrench
     *
     * \english
     * The solution's data type. 
     * \endenglish
     */
    typedef typename SolutionPrinter< T >::Solution Solution;

    /** 
     * \french
     * S�parateur entre la longueur source et la longueur cible. 
     * \endfrench
     *
     * \english
     * Separator between the source length and the target length. 
     * \endenglish
     */
    static const char LENGTH_SEPARATOR = '-';

    /** 
     * \french
     * S�parateur entre les longueurs et le score. 
     * \endfrench
     *
     * \english
     * Separator between the target length and the score.
     * \endenglish
     */
    static const char SCORE_SEPARATOR = ' ';

    /** 
     * \french
     * S�parateur en les diff�rents alignements. 
     * \endfrench
     *
     * \english
     * Alignment separator. 
     * \endenglish
     */
    static const char ALIGNMENT_SEPARATOR = '\n';
    
    /**
     * \french
     * Constructeur.
     * \endfrench
     *
     * \english
     * Constructor. 
     * \endenglish
     */
    RaliPrinter();

    void operator()( std::wostream& out, const Solution& solution );
};

// ------------------------------------------------------------------------ //
template< class T >
RaliPrinter< T >::RaliPrinter()
{}

// ------------------------------------------------------------------------ //
template< class T >
void RaliPrinter< T >::operator()( std::wostream& out, const Solution& solution )
{
    typename Solution::const_iterator iter;
    double oldScore = 0;
    double score = 0;
    
    for( iter = solution.begin(); iter != solution.end(); iter++ )
    {
        oldScore = score;
        score = iter -> getScore() - oldScore;
        
        out << iter -> getSourceLength() << LENGTH_SEPARATOR
            << iter -> getTargetLength() << SCORE_SEPARATOR
            << iter -> getScore() << ALIGNMENT_SEPARATOR;
    }

    out.flush();
}

}// namespace japa

#endif
