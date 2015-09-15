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

#ifndef JAPA_PREFIX_COGNATE_FINDER_H
#define JAPA_PREFIX_COGNATE_FINDER_H

#include "cognatefinder.h"
#include "text.h"
#include "validator.h"

namespace japa
{

/**
 * \french
 * Un foncteur qui consid�re les cognates comme les mots ayant un pr�fixe
 * commun.
 * \endfrench
 *
 * \english
 * A fonctor that consider words that have a common prefix as cognates.  
 * \endenglish
 *
 *
 * @version 1.1
 */
class PrefixCognateFinder : public CognateFinder
{
public :
    /** 
     * \french
     * La longueur par d�faut des pr�fixes � consid�rer. 
     * \endfrench
     *
     * \english
     * The default length of the prefix. 
     * \endenglish
     */
    static const size_t DEFAULT_PREFIX_LENGTH = 4;
    
    /**
     * \french
     * Constructeur.
     *
     * @param length La longueur du pr�fixe � consid�rer.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param length The length of the prefix. 
     * \endenglish
     */
    PrefixCognateFinder( const size_t length = DEFAULT_PREFIX_LENGTH );
    
    void operator()( Text& source, Text& target, 
                     Validator< WordInfo >& validator );
   
    /**
     * \french
     * Ajuste la longueur du pr�fixe � consid�rer.
     *
     * @param length La nouvelle longueur du pr�fix.
     * \endfrench
     *
     * \english
     * Sets the prefix length.
     *
     * @param length The new length of the prefix. 
     * \endenglish
     */
    void setPrefixLength( const size_t length );

    /**
     * \french
     * Retourne la longueur du pr�fixe.
     * 
     * @return La longueur du pr�fixe.
     * \endfrench
     *
     * \english
     * Gets the length of the prefix.
     *
     * @return The length of the prefix.
     * \endenglish
     */
    size_t getPrefixLength() const;
    
private :
    /**
     * \french
     * Ajoute un cognate � un mot source qui se retrouve aussi dans le texte 
     * cible.
     *
     * @param word Le mot dans le texte source.
     * @param wi   L'objet repr�sentant le mot.
     * @param validator Le validateur de mots
     * @param tgtDict Le dictionnaire cible.
     * \endfrench
     *
     * \english
     * Add a cognate to a source word if the word is present in the
     * target text's dictionary.
     *
     * @param word The source text's word.
     * @param wi   The source text word's object.
     * @param validator The word filter.
     * @param tgtDict The target text's dictionary.
     * \endenglish
     */
    void addWordCognate( const wstring& word, WordInfo& wi,
    //void addWordCognate( const UTF8::String& word, WordInfo& wi,
                         Validator< WordInfo >& validator,
                         TextDictionary& tgtDict ) const;
   
    /**
     * \french
     * Ajoute des cognates � un mot source dont le pr�fixe est le m�me que
     * des mots dans le texte cible.
     *
     * @param word Le mot dans le texte source.
     * @param wi   L'objet repr�sentant le mot.
     * @param validator Le validateur de mots
     * @param tgtDict Le dictionnaire cible.
     * \endfrench
     *
     * \english
     * Add earch target text's word that have the same prefix as the source 
     * word in the synonyms list of the source word.
     *
     * @param word The source text's word.
     * @param wi   The source text word's object.
     * @param validator The word filter.
     * @param tgtDict The target text's dictionary.

     * \endenglish
     */
    void addPrefixCognate( const wstring& word, WordInfo& wi,
    //void addPrefixCognate( const UTF8::String& word, WordInfo& wi,
                           Validator< WordInfo >& validator,
                           TextDictionary& tgtDict ) const;

    
    /** 
     * \french
     * La longueur du pr�fixe � consid�rer. 
     * \endfrench
     *
     * \english
     * The length of the prefix. 
     * \endenglish
     */
    size_t m_prefixLength;
};
}// namespace japa

#endif
