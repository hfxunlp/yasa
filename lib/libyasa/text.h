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

#ifndef JAPA_TEXT_H
#define JAPA_TEXT_H

using namespace std;

#include <iostream>
#include <string>
#include <vector>

#include "dictionary.h"
#include "wordinfo.h"

namespace japa
{

/** 
 * \french
 * Le type de l'identificateur d'un mot 
 * \endfrench
 *
 * \english
 * Word id's data type. 
 * \endenglish
 */
typedef WordInfo* WORD_ID;

/** 
 * \french
 * Le type d'un mot.
 * \endfrench
 *
 * \english
 * Word's data type. 
 * \endenglish
 */
typedef std::vector< WORD_ID > TextWord;

/** 
 * \french
 * Le type d'une phrase 
 * \endfrench
 *
 * \english
 * Sentence's data type.
 * \endenglish
 */
typedef std::vector< size_t > TextSentence;

/** 
 * \french
 * Le type d'un paragraphe 
 * \endfrench
 *
 * \english
 * Paragraph's data type. 
 * \endenglish
 */
typedef std::vector< size_t > TextParagraph;

/** 
 * \french
 * Le type d'une division 
 * \endfrench
 *
 * \english
 * Division's data type. 
 * \endenglish
 */
typedef std::vector< size_t > TextDivision;

/** 
 * \french
 * Le type du dictionnaire du texte 
 * \endfrench
 *
 * \english
 * Text dictionary's data type. 
 * \endenglish
 */
typedef Dictionary< WordInfo > TextDictionary;

/**
 * \french
 * Repr�sente un texte.
 *
 * Un texte est un vecteur de phrases dont les mots sont r�f�renc�s dans un
 * dictionnaire.
 * \endfrench
 *
 * \english
 * Represents a text.
 *
 * A text is a vector of sentences of which the words are referenced in a
 * dictionary.
 * \endenglish
 *
 *
 * @version 1.1
 */
class Text 
{
public :
    /**
     * \french
     * Constructeur.
     * \endfrench
     *
     * \english
     * Constructor. 
     * \endenglish
     */
    Text();

    /**
     * \french
     * Destructeur
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~Text();
    
    /**
     * \french
     * Retourne une r�f�rence vers le dictionnaire du texte.
     * 
     * @return Une r�f�rence vers le dictionnaire.
     * \endfrench
     *
     * \english
     * Gets a reference on the text's dictionary.
     *
     * @return A reference to the text's dictionary.
     * \endenglish
     */
    TextDictionary& getDictionary();
    
    /**
     * \french
     * Trouve un mot du texte. 
     *
     * @note Le premier mot soyant indic� � 0. Le comportement est ind�fini si 
     *       l'indice est invalide.
     * 
     * @param indice L'indice d'un mot du texte.
     *
     * @return Une r�f�rence vers le mot dont l'indice est sp�cifi�.
     * \endfrench
     *
     * \english
     * Gets a word of the text.
     * 
     * @note The words' subscript are 0 based.  The behaviors are undefined if
     *       the subscript is invalid.
     *
     * @param indice The subscript of the word.
     *
     * @return A reference on the searched word.
     * \endenglish
     */
    WordInfo& getWord( const size_t indice ) const;
    
    /**
     * \french
     * Retourne le nombre de mots dans le texte.
     * 
     * @return Le nombre de mots dans le texte.
     * \endfrench
     *
     * \english
     * Gets the number of words in the text.
     *
     * @return The number of words.
     * \endenglish
     */
    size_t getWordCount() const;
   
    /**
     * \french
     * Retourne le nombre de mots dans une phrase.
     * 
     * @param indice L'indice de la phrase.
     * 
     * @return Le nombre de mots dans la phrase.  Si l'indice est invalide,
     *         0 est retourn�.
     * \endfrench
     *
     * \english
     * Gets the number of words in a sentence.
     *
     * @param indice The sentence's subscript.
     *
     * @return The number of word in the sentence.  If the subscript is not
     *         valid, 0 is returned.
     * \endenglish
     */
    size_t getSentenceWordCount( const size_t indice ) const;
    
    /**
     * \french
     * Trouve la longueur en caract�res de la phrase � l'indice sp�cifi�.
     *
     * @note La premi�re phrase est indic�e � 0.  Les blancs entre les unit�s
     *       lexicales ne sont pas compt�es.
     *
     * @param indice L'indice de la phrase ( en ordre d'ajout ).
     * 
     * @return La longueur de la phrase en caract�res.  Si la phrase n'existe
     *         pas ou la phrase est "vide", 0 est retourn�.
     * \endfrench
     *
     * \english
     * Gets the length in characters of a sentence.
     *
     * @note The sentences are 0 based.  The white spaces between lexical
     *       units are not considered.
     *
     * @param indice The sentence's subscript.
     *
     * @return The sentence's length in characters.  If the subscript is not
     *         valid, 0 is returned.
     * \endenglish
     */
    size_t getSentenceLength( const size_t indice ) const;
    
    /**
     * \french
     * Retourne le nombre de phrases dans le texte.
     * 
     * @return Le nombre de phrases dans le texte.
     * \endfrench
     *
     * \english
     * Gets the number of sentences in the text.
     *
     * @return The number of sentences. 
     * \endenglish
     */
    size_t getSentenceCount() const;

    /**
     * \french
     * Trouve les bornes d'une phrase.
     *
     * @note Si l'indice est invalide, les valeurs de begin et end sont 
     *       ind�finies.
     *
     * @param indice L'indice de la phrase.
     * @param begin (OUT) L'indice du premier mot de la phrase.
     * @param end (OUT) L'indice du mot apr�s le dernier de la phrase.
     * \endfrench
     *
     * \english
     * Gets a sentence's bounds.
     * 
     * @note On an invalid subscript, the behaviors of this function are
     *       undefined.
     *
     * @param indice The sentence's subscript.
     * @param begin (OUT) The subscript of the sentence's first word.
     * @param end   (OUT) The subscript of the word after the sentence's last
     *              word.
     * \endenglish
     */
    void getSentenceBounds( const size_t indice, size_t& begin, 
                            size_t& end ) const;
    
    /**
     * \french
     * Touve la phrase propri�taire d'un mot.
     *
     * @param wordIndice L'indice du mot dont il faut trouver la phrase 
     *                   propri�taire.
     *
     * @return L'indice de la phrase propri�taire.  Si l'indice est trop grand,
     *         l'indice de la derni�re phrase est retourn�.
     * \endfrench
     *
     * \english
     * Gets the subscript of a sentence that owns a word.
     *
     * @param wordIndice The word's subscript.
     * 
     * @return The proprietary sentence's subscript.  If the word's subscript
     *         is not valid,  the last sentence's subscript is returned.
     * \endenglish
     */
    size_t getSentenceIndice( const size_t wordIndice ) const;
    
    /**
     * \french
     * Retourne l'identificateur d'une phrase.
     * 
     * @param indice L'indice de la phrase.
     *
     * @return L'identificateur de la phrase ou une cha�ne vide si l'indice est
     *         invalide.
     * \endfrench
     *
     * \english
     * Gets a sentence's ID.
     *
     * @param indice The sentence's subscript.
     *
     * @return The sentence's ID or an empty string if the subscript is not
     *         valid.
     * \endenglish
     */
    wstring getSentenceID( const size_t indice ) const;

    /**
     * \french
     * Transformations apport�es � une cha�ne avant qu'elle ne soit stock�e.
     *
     * @param word Le mot � transformer.
     *
     * @return Le mot pr�t � �tre stock�e.
     * \endfrench
     *
     * \english
     * Transform a word before it is stocked in the dictionary.
     *
     * @param word The word to transform.
     *
     * @return The transformed word. 
     * \endenglish
     */
    static wstring prepareWord( wstring& word );
    
    /**
     * \french
     * Ajoute un mot � la fin du texte.
     *
     * @param word Le mot � ajouter
     * \endfrench
     *
     * \english
     * Add a word at the end of the text.
     *
     * @param word The word to add. 
     * \endenglish
     */
    void pushWord( wstring& word );

    /**
     * \french
     * Commance une nouvelle.
     *
     * @param id L'identificateur de la cha�ne de caract�re.
     * \endfrench
     *
     * \english
     * Begin a new sentence.
     *
     * @param id The new sentence's ID.
     * \endenglish
     */
    void pushSentence( const wstring& id );

    /**
     * \french
     * Commence un nouveau paragraph.
     * \endfrench
     *
     * \english
     * Begins a new paragraph. 
     * \endenglish
     */
    void pushParagraph();

    /**
     * \french
     * Commence une nouvelle division.
     * \endfrench
     *
     * \english
     * Begins a new division. 
     * \endenglish
     */
    void pushDivision();

private :
    /**
     * \french
     * Indexe un mot dans le dictionnaire.
     *
     * @param word Le mot � indexer
     * 
     * @return L'identificateur du mot
     * \endfrench
     *
     * \english
     * Index a word in the dictionary.
     *
     * @param word The word to index.
     *
     * @return The word's ID.
     * \endenglish
     */
    WORD_ID indexWord( const wstring& word );

    /** 
     * \french
     * Dictionnaire liant un mot � ses informations 
     * \endfrench
     *
     * \english
     * Dictionary of words. 
     * \endenglish
     */
    TextDictionary m_dictionary;

    /** 
     * \french
     * Les mots du texte. 
     *
     * Contient les r�f�rence vers les descriptions des mots.  Les mots sont
     * dans l'ordre du texte.
     * \endfrench
     *
     * \english
     * The words of the text.
     *
     * Contains references to the words' description.  The word are in the
     * same order as in the text. 
     * \endenglish
     */ 
    TextWord m_words;

    /** 
     * \french
     * Les phrases du texte.
     *
     * Contient les indices des premiers mots de chaque phrase.
     * \endfrench
     *
     * \english
     * The text's sentences.
     *
     * Contains the subscript of the first words of each sentences.
     * \endenglish
     */
    TextSentence m_sentences;

    /**
     * \french
     * Les paragraphes du texte.
     *
     * Contient l'indice de la premi�re phrase du paragraphe.
     * \endfrench
     *
     * \english
     * The text's paragraphs.
     *
     * Contains the subscript of the first sentences of each paragraphs. 
     * \endenglish
     */
    TextParagraph m_paragraphs;

    /**
     * \french
     * Les divisions du texte.
     *
     * Contient l'indice des premiers paragaphes de chaque division.
     * \endfrench
     *
     * \english
     * The text's divisions. 
     *
     * Contains the subscript of the first paragraphs of each division.
     * \endenglish
     */
    TextDivision m_divisions;

    /** 
     * \french
     * Les longueurs des phrases. 
     * \endfrench
     *
     * \english
     * The sentences' length. 
     * \endenglish
     */
    std::vector< size_t > m_sentencesLength;
    
    /** 
     * \french
     * Les identificateurs des phrases. 
     * \endfrench
     *
     * \english
     * The sentences' ID. 
     * \endenglish
     */
    std::vector< wstring > m_sentencesID;
    
    // Permet d'afficher le l'objet
    friend std::ostream& operator<<( std::ostream& out, const Text& text );
};

/**
 * \french
 * Permet d'afficher le contenu d'un objet <code>Text</code>.
 *
 * @param out Le flux dans lequel afficher l'objet.
 * @param text Le texte � afficher.
 *
 * @return Le flux dans lequel l'objet a �t� affich�.
 * \endfrench
 *
 * \english
 * Prints the content of a <code>Text</code>.
 *
 * @param out The stream where to print.
 * @param text The text to print.
 *
 * @return The stream where the text were printed.
 * \endenglish
 */
std::ostream& operator<<( std::ostream& out, const Text& text );

}// namespace japa

#endif
