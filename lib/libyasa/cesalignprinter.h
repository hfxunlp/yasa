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

#ifndef JAPA_CESALIGN_PRINTER_H
#define JAPA_CESALIGN_PRINTER_H

#include <string>

#include "arcadeprinter.h"
#include "solutionprinter.h"

namespace japa
{

/**
 * \french
 * Imprime une solution au format CesAlign.
 *
 * Le format CesAlign est pareil au format ARCADE � l'exception de l'en-t�te
 * et le "pied de page".
 *
 * @param T Le type du score de la solution.
 * \endfrench
 *
 * \english
 * Print a solution in CesAlign format.
 *
 * ARCADE and CesAlign format are the same except for the header and the footer.
 * 
 * @param T The score's data type. 
 * \endenglish
 *
 *
 * @version 1.1
 * @see ::ArcadeParser
 */
template< class T >
class CesalignPrinter : public SolutionPrinter< T >
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
     * @param sourceName Le nom du fichier source.
     * @param targetName Le nom du fichier cible.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param source A reference to the source text.
     * @param target A reference to the target text. 
     * @param sourceName The name of the source file.
     * @param targetName The name of the target file.
     * \endenglish
     */
    CesalignPrinter( const Text& source, const Text& target, 
            const std::wstring& sourceName = "",
            const std::wstring& targetName = "" );
    
    void operator()( std::wostream& out, const Solution& solution );

private :
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
     * Le nom du fichier source.
     * \endfrench
     *
     * \english
     * The name of the source file.
     * \endenglish
     */
    const std::wstring m_sourceName;

    /**
     * \french
     * Le nom du fichier cible.
     * \endfrench
     *
     * \english
     * The name of the target file.
     * \endenglish
     */
    const std::wstring m_targetName;
};

// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //
template< class T >
CesalignPrinter< T >::CesalignPrinter( const Text& source, const Text& target,
       const std::wstring& sourceName, const std::wstring& targetName )
        : m_source( source ), m_target( target ), 
          m_sourceName( sourceName ), m_targetName( targetName )
{}

// ------------------------------------------------------------------------ //
template< class T >
void CesalignPrinter< T >::operator()( std::wostream& out,
                                       const Solution& solution )
{
    ArcadePrinter< T > ap( m_source, m_target );

    out << L"<!DOCTYPE CESALIGN PUBLIC \"-//CES//DTD cesAlign//EN\" []>"
        << std::endl
        << L"<cesAlign VERSION=\"1.14\"  type=\"sent\" "
        << L"fromDoc=\"" << m_sourceName
        << L"\" toDoc=\"" << m_targetName << "\">" << std::endl
        << L"<linkList>" << std::endl
        << L"<linkGrp>" << std::endl;
    
    ap( out, solution );
    
    out << L"</linkGrp>" << std::endl
        << L"</linkList>" << std::endl
        << L"</cesAlign>" << std::endl;
}
}// namespace japa

#endif
