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

#ifndef JAPA_BITEXT_SYNONYM_CONTAINER_H
#define JAPA_BITEXT_SYNONYM_CONTAINER_H

using namespace std;

#include <string>

#include "synonymcontainer.h"
#include "text.h"

namespace japa
{

/**
 * \french
 * G�re l'ajout des synonymes dans le dictionnaire d'un texte source.
 * \endfrench
 *
 * \english
 * Manage synonyms addition in a source text's dictionary. 
 * \endenglish
 * 
 *
 * @version 1.1
 */
class BitextSynonymContainer : public SynonymContainer< wstring >
{
public :
    /**
     * \french
     * Constructeur.
     *
     * @param sourceDict Le dictionnaire source.
     * @param targetDict Le dictionnaire cible.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param sourceDict The source text's dictionary.
     * @param targetDict The target text's dictionary. 
     * \endenglish
     */
    BitextSynonymContainer( TextDictionary& sourceDict, 
            TextDictionary& targetDict ); 
    
    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~BitextSynonymContainer();

    void addSynonyms( wstring& word1, wstring& word2 );

private :
    /** 
     * \french
     * Une r�f�rence vers le dictionnaire source. 
     * \endfrench
     *
     * \english
     * A reference to the source text's dictionary.
     * \endenglish
     */
    TextDictionary& m_sourceDict;

    /** 
     * \french
     * Une r�f�rence vers le dictionnaire cible. 
     * \endfrench
     *
     * \english
     * A reference to the target text's dictionary.
     * \endenglish
     */
    TextDictionary& m_targetDict;
};

}// namespace japa

#endif
