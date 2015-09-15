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

#ifndef JAPA_SOLUTION_PRINTER_H
#define JAPA_SOLUTION_PRINTER_H

#include <iostream>
#include <list>

#include "alignment.h"

namespace japa
{

/**
 * \french
 * Interface pour les afficheurs de solutions.
 * 
 * Cette interface doit �tre impl�ment�e par les classes qui veulent formatter
 * la solution.
 *
 * @param T Le type de donn�e du score.
 * \endfrench
 *
 * \english
 * Solution printers' common interface.
 *
 * @param T The score's data type.
 * \endenglish
 * 
 *
 * @version 1.1
 */
template< class T >
class SolutionPrinter
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
    typedef std::list< Alignment< T > > Solution;

    /**
     * \french
     * Imprime la solution.
     *
     * @param out Le flux vers lequel imprimer la solution.
     * @param solution La solution � imprimer.
     * \endfrench
     *
     * \english
     * Prints the solution.
     *
     * @param out The stream where to print the solution.
     * @param solution The solution to print. 
     * \endenglish
     */
    virtual void operator()( std::wostream& out, const Solution& solution ) = 0;
};

}// namespace japa

#endif
