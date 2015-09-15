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

#ifndef JAPA_COGNATE_FINDER_H
#define JAPA_COGNATE_FINDER_H

#include "text.h"
#include "validator.h"

namespace japa
{

/**
 * \french
 * Interface des algorithmes chercheur de cognates.
 * \endfrench
 *
 * \english
 * Cognate finding algorithms interface. 
 * \endenglish
 *
 *
 * @version 1.1
 */
class CognateFinder
{
public :
    /**
     * \french
     * Trouve les cognates entre le texte source et le texte cible.
     *
     * Les cognates des mots du texte source sont stock�s dans la liste des 
     * synonymes des mots de son dictionnaire.
     *
     * @param source Une r�f�rence vers le texte source.
     * @param target Une r�f�rence vers le texte cible.
     * @param validator Un filtre de mots qui indique si un mot est un 
     *                  cognate potentiel.
     * \endfrench
     *
     * \english
     * Find cognates between source and target texts.
     *
     * Source text's cognates are saved in the synonyms lists of the word
     * of its dictionary.
     *
     * @param source A reference to the source text.
     * @param target A reference to the target text.
     * @param validator A filter on the words that are checked for
     *                  cognateness.
     * \endenglish
     */
    virtual void operator()( Text& source, Text& target, 
                             Validator< WordInfo >& validator ) = 0;
};

}// namespace japa

#endif
