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

#ifndef JAPA_FRIENDLY_PRINTER_H
#define JAPA_FRIENDLY_PRINTER_H

#include "solutionprinter.h"
#include "text.h"

namespace japa
{

/**
 * \french
 * �crit le r�sultat d'un alignement de mani�re facilement lisible pour les
 * humains.
 *
 * @param T Le type de donn�es du score.
 * \endfrench
 *
 * \english
 * Human friendly alignment printer.
 *
 * @param T The score's data type.
 * \endenglish
 * 
 *
 * @version 1.1
 */
template< class T >
class FriendlyPrinter : public SolutionPrinter< T >
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
     * Constructeur.
     *
     * @param source Une r�f�rence vers le texte source.
     * @param target Une r�f�rence vers le texte cible.
     * \endfrench
     *
     * \english
     * Constructor
     *
     * @param source A reference to the source text.
     * @param target A reference to the target text.
     * \endenglish
     */
    FriendlyPrinter( const Text& source, const Text& target );

    void operator()( std::wostream& out, const Solution& solution );

private :
    /**
     * \french
     * Imprime une le contenu d'une phrase dans un flux.
     *
     * @param out Le flux dans lequel imprimer la phrase.
     * @param text Le texte contenant la phrase.
     * @param indice L'indice de la phrase.
     * \endfrench
     *
     * \english
     * Print a text sentence.
     *
     * @param out The output stream.
     * @param text The text containing the sentence.
     * @param indice The sentence's indice.
     * \endenglish
     */
    void printSentence( std::wostream& out, const Text& text, const size_t indice );

    
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
};

// ------------------------------------------------------------------------ //
template< class T >
FriendlyPrinter< T >::FriendlyPrinter( const Text& source, const Text& target )
        : m_source( source ), m_target( target )
{}

// ------------------------------------------------------------------------ //
template< class T >
void FriendlyPrinter< T >::operator()( std::wostream& out,
                                       const Solution& solution )
{
    size_t isrc = 0;    // Indice de la phrase dans le texte source
    size_t itgt = 0;    // Indice de la phrase dans le texte cible
    typename Solution::const_iterator iter;

    // Parcour tous les alignements
    for( iter = solution.begin(); iter != solution.end(); iter++ )
    {
        out << "***************************************************" 
            << std::endl; 
        
        // Imprime les phrases sources
        for( size_t i = 0; i < iter -> getSourceLength(); i++, isrc++ )
        {
            out << isrc + 1 << "(" << m_source.getSentenceID( isrc ) << "):\t";
            printSentence( out, m_source, isrc );
            out << std::endl;
        }
        
        out << "---------------------------------------------------" 
            << std::endl;
        
        // Imprime les phrases cibles
        for( size_t j = 0; j < iter -> getTargetLength(); j++, itgt++ )
        {
            out << itgt + 1 << "(" << m_target.getSentenceID( itgt ) << "):\t";
            printSentence( out, m_target, itgt );
            out << std::endl;
        }

        out << "***************************************************" 
            << std::endl;
    }

}


// ------------------------------------------------------------------------ //
template< class T >
void FriendlyPrinter< T >::printSentence( std::wostream& out, const Text& text,
                                          const size_t indice )
{
    size_t begin;
    size_t end;

    text.getSentenceBounds( indice, begin, end );

    for( size_t i = begin; i < end; i++ )
    {
        wcout << " " << text.getWord( i ).getWord();
    }
}

}// namespace japa

#endif
