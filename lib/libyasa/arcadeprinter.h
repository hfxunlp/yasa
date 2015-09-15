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


#ifndef JAPA_ARCADE_PRINTER_H
#define JAPA_ARCADE_PRINTER_H

#include "solutionprinter.h"
#include "text.h"
#include "toolbox.h"

namespace japa
{

/**
 * \french
 * Imprime la solution sous le format ARCADE.
 *
 * Le format ARCADE est compos� de balises.  La balise importante est 
 * <code>link</code> qui suit la convention suivante :
 *
 * <code> \<link xtargets="[source id1] [source id2] ... [sourceidn];
 * [target id1] [target id2] ... [target idn]" 
 * certainty="subjective float number"\></link></code>
 *
 * Exemple :
 *
 * <code> \<link xtargets="d1p1s1;d1p1s1 d1p1s2"\ certainty="0.23"></link>
 * </code>
 *
 * Une solution sous le format ARCADE est form�e d'une suite de balises 
 * <code>link</code>.  Il se peut que le fichier aient des balises d'en-t�tes
 * avant la premi�re balise <code>link</code>.
 *
 * @param T Le type du score de la solution.
 * \endfrench
 *
 * \english
 * Print an alignment solution in the ARCADE format.
 *
 * The ARCADE is composed of tags.  The only parsed tag is :
 * <code> \<link xtargets="[source id1] [source id2] ... [sourceidn];
 * [target id1] [target id2] ... [target idn]" 
 * certainty="subjective float number"\></link></code>
 *
 * Example :
 *
 * <code> \<link xtargets="d1p1s1;d1p1s1 d1p1s2" certainty="0.23"\></link>
 * </code>
 *
 * A solution in ARCADE format is composed of a sequence tag of type
 * <code>link</code>.  There may be an header at the beginning of the
 * file.
 *
 * @param T The score's data type.
 * 
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class ArcadePrinter : public SolutionPrinter< T >
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
     * @param source Le texte source.
     * @param target Le texte cible.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param source The soure text.
     * @param target The target text. 
     * \endenglish
     */
    ArcadePrinter( const Text& source, const Text& target );
    
    void operator()( std::wostream& out, const Solution& solution );

private :
    /** 
     * \french
     * Le texte source.
     * \endfrench
     *
     * \english
     * The source text. 
     * \endenglish
     */
    const Text& m_source;

    /** 
     * \french
     * Le texte cible. 
     * \endfrench
     *
     * \english
     * The target text. 
     * \endenglish
     */
    const Text& m_target;
};

// ------------------------------------------------------------------------ //
template< class T >
ArcadePrinter< T >::ArcadePrinter( const Text& source, const Text& target ) 
        : m_source( source ), m_target( target )
{}

// ------------------------------------------------------------------------ //
template< class T > void ArcadePrinter< T >::operator()( std::wostream& out,
        const Solution& solution )
{
    size_t isrc = 0;    // Indice de la phrase dans le texte source
    size_t itgt = 0;    // Indice de la phrase dans le texte cible
    double previousScore = 0; // Score de l'alignement pr�c�dent
    typename Solution::const_iterator iter;

    // Parcour tous les alignements
    for( iter = solution.begin(); iter != solution.end(); iter++ )
    {
        out << "<link xtargets=\"";
        
        // Imprime les phrases sources
        for( size_t i = 0; i < iter -> getSourceLength(); i++, isrc++ )
        {
            if( i != 0 )
            {
                out << " ";
            }
            
            out << m_source.getSentenceID( isrc );
        }
        
        out << ";";
        
        // Imprime les phrases cibles
        for( size_t j = 0; j < iter -> getTargetLength(); j++, itgt++ )
        {
            if( j != 0 )
            {
                out << " ";   
            }
            
            out << m_target.getSentenceID( itgt );
        }

        out << "\" certainty=\"" << iter -> getScore() - previousScore << "\">"
            << "</link>" << std::endl;

        previousScore = iter -> getScore();
    }
}

}//namespace japa
#endif
