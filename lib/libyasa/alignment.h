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

#ifndef JAPA_ALIGNMENT_H
#define JAPA_ALIGNMENT_H

#include <list>
#include "dynamictable.h"

namespace japa
{

/**
 * \french
 * Un alignement de phrases.
 *
 * Un alignement est compos� d'un nombre de phrases sources, d'un nombre de 
 * phrases cibles ainsi qu'un d'un score.  Le score est la valeur attribu�e
 * � l'alignement lors d'une r�solution par programmation dynamique et n'est
 * pas n�cessairement repr�sentatif.
 *
 * @param T Le type de donn�e contenant le score.
 * 
 * \endfrench
 * 
 * \english
 * A alignment of sentences.
 *
 * An alignment is composed of a number of source's sentences, a number of 
 * target's sentences and a score.  The score is almost irrelevant and
 * is given while solving the problem using dynamic programming.
 *
 * @param T The score's data type.
 * 
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class Alignment
{
public :
    /**
     * \french
     * Constructeur.
     *
     * @param sourceLength Le nombre de phrases de l'alignement dans le texte 
     *                     source.
     * @param targetLength Le nombre de phrases de l'alignement dans le texte 
     *                     cible.
     * @param score        Le score attribu� � l'alignement.
     * \endfrench
     * 
     * \english
     * Constructor.
     *
     * @param sourceLength Number of source sentences in alignment.
     * @param targetLength Number of target sentences in alignment
     * @param score Score of the alignment.
     * \endenglish
     */
    Alignment( const size_t sourceLength = 0, const size_t targetLength = 0, 
               const T score = T() );

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~Alignment();
    
    /**
     * \french
     * Ajuste le nombre de phrases source dans l'alignement.
     *
     * @param sourceLength Le nouveau nombre de phrases source dans 
     *                     l'alignement.
     * \endfrench
     *
     * \english
     * Set the number of source sentences in alignment.
     *
     * @param sourceLength The new number of source sentences.
     * \endenglish
     */
    void setSourceLength( const size_t sourceLength );

    /**
     * \french
     * Trouve le nombre de phrases sources dans l'alignement.
     * 
     * @return Le nombre de phrases sources dans l'alignement.
     * \endfrench
     *
     * \english
     * Gets the number of source sentences.
     * 
     * @return The number of source sentences in alignment.
     * \endenglish
     */
    size_t getSourceLength() const;

    /**
     * \french
     * Ajuste le nombre de phrases cibles dans l'alignement.
     *
     * @param targetLength Le nouveau nombre de phrases cibles dans 
     *                     l'alignement.
     * \endfrench
     *
     * \english
     * Set the number of target sentences in alignment.
     *
     * @param  targetLength The new number of target sentences.
     * \endenglish
     */
    void setTargetLength( const size_t targetLength );

    /**
     * \french
     * Trouve le nombre de phrases cibles dans l'alignement.
     * 
     * @return Le nombre de phrases cibles dans l'alignement.
     * \endfrench
     *
     * \english
     * Gets the number of target sentences.
     *
     * @return The number of target sentence in alignemnt.
     * \endenglish
     */
    size_t getTargetLength() const;

    /**
     * \french
     * Ajuste le score de l'alignement.
     *
     * @param score Le nouveau score.
     * \endfrench
     *
     * \english
     * Set the alignment's score.
     *
     * @param score The new alignment's score.
     * \endenglish
     */
    void setScore( const T score );

    /**
     * \french
     * Trouve le score de l'alignement.
     * 
     * @return Le score de l'alignement.
     * \endfrench
     *
     * \english
     * Gets the alignment's score.
     *
     * @return The alignment's score.
     * \endenglish
     */
    T getScore() const;
    
private :
    /** 
     * \french
     * Le nombre de phrases dans le texte source. 
     * \endfrench
     *
     * \english
     * The number of source's sentences in alignement.
     * \endenglish
     */
    size_t m_sourceLength;

    /**
     * \french
     *  Le nombre de phrases dans le texte cible. 
     * \endfrench
     *
     * \english
     * The number of target's sentences in alignment. 
     * \endenglish
     */
    size_t m_targetLength;

    /** 
     * \french
     * Le score attribu�.
     * \endfrench
     *
     * \english
     * The alignment's score.
     * \endenglish
     */
    T m_score;
    
};

/**
 * \french
 * Construit un alignement de deux textes � partir d'une table dynamique.
 *
 * @param iter Un it�rateur sur la solution du meilleur alignement.
 *
 * @return Les alignements des phrases des textes.
 * \endfrench
 *
 * \english
 * Generate a bi-texte alignment based on a dynamic table.
 *
 * @param iter An iterator on the best alignment solution.
 *
 * @return The alignment between source and target texts.
 * \endenglish
 */
template< class T >
std::list< Alignment< T > > buildAlignment( 
        typename DynamicTable< T >::Iterator& iter )
{
    size_t lasti, lastj, i, j;
    double score;
    Alignment< T > align;
    std::list< Alignment< T > > l;
    
    
    if( iter.hasNext() )
    {
        iter.next();
        i = iter.i();
        j = iter.j();

        // Ajoute les alignements.
        while( iter.hasNext() )
        {       
            score = iter.score();
            iter.next();
            lasti = i;
            lastj = j;
            i = iter.i();
            j = iter.j();

            align.setSourceLength( lasti - i );
            align.setTargetLength( lastj - j );
            align.setScore( score );

            l.push_front( align );
        }
    }
    
    return l;
}

// ------------------------------------------------------------------------ //
template< class T >
Alignment< T >::Alignment( const size_t sourceLength, const size_t targetLength, 
                           const T score ) : m_sourceLength( sourceLength ),
                                             m_targetLength( targetLength ),
                                             m_score( score ) 
{}

// ------------------------------------------------------------------------ //
template< class T >
Alignment< T >::~Alignment()
{}

// ------------------------------------------------------------------------ //
template< class T >
void Alignment< T >::setSourceLength( const size_t sourceLength )
{
    m_sourceLength = sourceLength;
}

// ------------------------------------------------------------------------ //
template< class T >
size_t Alignment< T >::getSourceLength() const
{
    return m_sourceLength;
}

// ------------------------------------------------------------------------ //
template< class T >
void Alignment< T >::setTargetLength( const size_t targetLength )
{
    m_targetLength = targetLength;
}

// ------------------------------------------------------------------------ //
template< class T >
size_t Alignment< T >::getTargetLength() const
{
    return m_targetLength;
}

// ------------------------------------------------------------------------ //
template< class T >
void Alignment< T >::setScore( const T score )
{
    m_score = score;
}

// ------------------------------------------------------------------------ //
template< class T >
T Alignment< T >::getScore() const
{
    return m_score;
}

}// namespace japa
#endif
