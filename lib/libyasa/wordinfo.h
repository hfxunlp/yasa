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

#ifndef JAPA_WORD_INFO
#define JAPA_WORD_INFO

using namespace std;

#include <iostream>
#include <set>
#include <string>

namespace japa
{

/**
 * \french
 * Stoque les informations pertinentes � propos d'un mot.
 * \endfrench
 *
 * \english
 * Contains the informations concerning a word.  
 * \endenglish
 *
 *
 * @version 1.1
 */
class WordInfo
{
public :
    /** 
     * \french
     * Permet l'affichage de l'objet 
     * \endfrench
     *
     * \english
     * Allow the word to be printed. 
     * \endenglish
     */
    friend std::wostream& operator<<( std::wostream& out, const WordInfo& w );

    /** 
     * \french
     * Le type de la structure qui contient les synonymes. 
     * \endfrench
     *
     * \english
     * The synonyms holder's data type.
     * \endenglish
     */
    typedef std::set< const WordInfo* > Synonyms;
   
    /**
     * \french
     * Constructeur
     *
     * @param word Le mot dont les informations doivent �tre stock�s.
     * @param frequency La fr�quence du mot.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param word The string representation of the word.
     * @param frequency The frequency of the word. 
     * \endenglish
     */
    WordInfo( const wstring& word, const size_t frequency = 0 );

    /**
     * \french
     * Constructeur.
     * \endfrench
     *
     * \english
     * Constructor. 
     * \endenglish
     */
    WordInfo();
    
    /**
     * \french
     * Destructeur
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~WordInfo();

    /**
     * \french
     * Retourne la repr�sentation du mot en cha�ne de caract�res.
     *  
     * @return Le mot.
     * \endfrench
     *
     * \english
     * Gets the string representation of the word.
     *
     * @return The word.
     * \endenglish
     */
    wstring getWord() const;
    
    /**
     * \french
     * Retourne la fr�quence du mot.
     * 
     * @return La fr�quence du mot.
     * \endfrench
     *
     * \english
     * Gets the word's frequency.
     *
     * @return The word's frequency.
     * \endenglish
     */
    size_t getFrequency() const;

    /**
     * \french
     * Ajuste la fr�quence du mot
     *
     * @param frequency La fr�quence d'apparition du mot
     * \endfrench
     *
     * \english
     * Sets the word frequency.
     *
     * @param frequency The new word's frequency. 
     * \endenglish
     */
    void setFrequency( const size_t frequency );

    /**
     * \french
     * Augmente de 1 la fr�quence du mot.
     * \endfrench
     *
     * \english
     * Add 1 to the word's frequency. 
     * \endenglish
     */
    void addOne();

    /**
     * \french
     * Ajoute un synonyme au mot.
     *
     * @param syn Le nouveau synonyme du mot.
     * \endfrench
     *
     * \english
     * Add a synonym to the word.
     *
     * @param syn The word's synonym. 
     * \endenglish
     */
    void addSynonym( const WordInfo& syn );

    /**
     * \french
     * V�rifie si un mot est synonyme du mot courant.
     *
     * @note La relation synonyme n'est pas sym�trique.
     *
     * @param w Le mot � tester.
     *
     * @return <code>true</code> si <code>w</code> est un synonyme du mot 
     *         courant, <code>false</code> sinon.
     * \endfrench
     *
     * \english
     * Checks if a word is a synonym of the current word.
     *
     * @note The synonym relation is not symetric.
     *
     * @param w The word to check.
     *
     * @return <code>true</code> if <code>w</code> is a synonyme of the
     *         current word, <code>false</code> otherwise.
     * \endenglish
     */
    bool isSynonym( const WordInfo& w ) const;

    /**
     * \french
     * V�rifie si le mot a des synonymes.
     *
     * @return <code>true</code> si le mot courant poss�de un ou des synonymes.
     * \endfrench
     *
     * \english
     * Checks if a word has synonyms.
     *
     * @return <code>true</code> if the word has at least one synonyme. 
     * \endenglish
     */
    bool hasSynonym() const;
    
    /**
     * \french
     * Retourne une r�f�rence vers la liste des synonymes du mot.
     * 
     * @return Une r�f�rence vers la structure qui contient les synonymes.
     * \endfrench
     *
     * \english
     * Gets a reference to the word's synonyms list.
     *
     * @return A reference to the word's synonyms list.
     * \endenglish
     */
    const Synonyms& getSynonyms() const;
    
private :

    /** 
     * \french
     * Le mot stock� 
     * \endfrench
     *
     * \english
     * The string representation of the word. 
     * \endenglish
     */
    wstring m_word;
    
    /** 
     * \french
     * Les synonymes du mot 
     * \endfrench
     *
     * \english
     * The word's synonyms. 
     * \endenglish
     */
    Synonyms m_synonyms;
    
    /** 
     * \french
     * La fr�quence du mot 
     * \endfrench
     *
     * \english
     * The word's frequency. 
     * \endenglish
     */
    size_t m_frequency;
};

/**
 * \french
 * Permet d'afficher une description caract�re de l'objet dans un flux
 *
 * @param out Le flux dans lequel afficher la description
 * @param w   L'objet <em>WordInfo</em> � afficher
 *
 * @return Le flux
 * \endfrench
 *
 * \english
 * Prints a string representation of the word.
 *
 * @param out The stream where to print the word.
 * @param w   The word to print.
 * 
 * @return The stream where the word was printed. 
 * \endenglish
 */
std::wostream& operator<<( std::wostream& out, const WordInfo& w );
}// namespace japa

#endif
