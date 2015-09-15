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


#ifndef JAPA_SCORE_PRINTER_H
#define JAPA_SCORE_PRINTER_H

#include "solutionprinter.h"

namespace japa
{

/**
 * \french
 * Imprime le score d'une solution d'alignement.
 *
 * Le format est le suivant :
 * \<Fichier source\> \<Fichier cible\> \<Score\>
 * 
 * @param T Le type de donn�e du score.
 * \endfrench
 *
 * \english
 * Prints an alignment's score.
 *
 * The format is the following:
 * \<Source file\>-\<Target file\> \<score\>
 *
 * @param T The score's data type.
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class ScorePrinter : public SolutionPrinter< T >
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
     * S�parateur entre le nom du fichier source et le nom du fichier cible. 
     * \endfrench
     *
     * \english
     * Separator between the names of the source the target files. 
     * \endenglish
     */
    static const char FILENAME_SEPARATOR = ' ';

    /** 
     * \french
     * S�parateur entre le nom du fichier cible et le score.
     * \endfrench
     *
     * \english
     * Separator between the target file name and the score.
     * \endenglish
     */
    static const char SCORE_SEPARATOR = ' ';

    /** 
     * \french
     * Terminateur d'alignement.
     * \endfrench
     *
     * \english
     * Alignement terminator. 
     * \endenglish
     */
    static const char ALIGNMENT_TERMINATOR = '\n';
    
    /**
     * \french
     * Constructeur.
     *
     * @param sourceName Le nom de la source.
     * @param targetName Le nom de la cible.
     * \endfrench
     *
     * \english
     * Constructor. 
     *
     * @param sourceName Source's name.
     * @param targetName Target's name.
     * \endenglish
     */
    ScorePrinter( const std::wstring sourceName, const std::wstring targetName );

    void operator()( std::wostream& out, const Solution& solution );

private :
    /**
     * \french
     * Le nom de la source.
     * \endfrench
     * 
     * \english
     * Source's name.
     * \endenglish
     */
    std::wstring m_sourceName;

    /**
     * \french
     * Le nom de la cible.
     * \endfrench
     * 
     * \english
     * Target's name.
     * \endenglish
     */
    std::wstring m_targetName;
};

// ------------------------------------------------------------------------ //
template< class T >
ScorePrinter< T >::ScorePrinter( const std::wstring sourceName,
        const std::wstring targetName ) : m_sourceName( sourceName ),
                                         m_targetName( targetName )
{}

// ------------------------------------------------------------------------ //
template< class T >
void ScorePrinter< T >::operator()( std::wostream& out,
        const Solution& solution )
{
    out << m_sourceName << FILENAME_SEPARATOR
        << m_targetName << SCORE_SEPARATOR
        << solution.back().getScore() << ALIGNMENT_TERMINATOR;

}

}// namespace japa

#endif
