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

#ifndef JAPA_SYNONYM_CONTAINER_H
#define JAPA_SYNONYM_CONTAINER_H


namespace japa
{

/**
 * \french
 * Interface permettant de r�f�rencer des mots qui sont synonymes.
 * \endfrench
 *
 * \english
 * Interface for classes that reference synonyms.  
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class SynonymContainer
{
public :
    /**
     * \french
     * R�f�rence une paire de mots qui sont synonymes.
     *
     * @param word1 Le premier mot.
     * @param word2 Le deuxi�me mot.
     * \endfrench
     *
     * \english
     * Reference a pair of words that are synonyms. 
     *
     * @param word1 The first word.
     * @param word2 The second word.
     * \endenglish
     */
    virtual void addSynonyms( T& word1, T& word2 ) = 0;
};

}// namespace japa

#endif
