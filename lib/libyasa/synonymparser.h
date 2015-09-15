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

#ifndef JAPA_SYNONYM_PARSER_H
#define JAPA_SYNONYM_PARSER_H


#include <iostream>

#include "synonymcontainer.h"

namespace japa
{

/**
 * \french
 * Interface permettant d'analyser des flux r�f�ren�ant des synonymes.
 * \endfrench
 *
 * \english
 * Interface for classes that parse synonyms definitions.  
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class SynonymParser
{
public :
    /**
     * \french
     * Lance l'analyse d'un flux de synonyme.
     *
     * @param in Le flux de synonyme.
     * @param sc La structure utilis�e pour ajouter les synonymes.
     * \endfrench
     *
     * \english
     * Parses the synonyms.
     *
     * @param in The stream where the synonyms are defined.
     * @param sc The structure where the synonyms are added. 
     * \endenglish
     */
    virtual void operator()( std::wistream& in, SynonymContainer< T >& sc ) = 0;
};

}// namespace japa

#endif
