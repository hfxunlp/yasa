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

#ifndef JAPA_DICTIONARY
#define JAPA_DICTIONARY

using namespace std;

#include <iostream>
#include <map>
#include <string>

namespace japa
{

/**
 * \french
 * Un dictionnaire qui associe des cha�nes de caract�res � un objet.
 *
 * @param T Le type d'objet associ� � la cha�ne.
 * \endfrench
 *
 * \english
 * A dictinary thats map a string to an object.
 *
 * @param T The associated object's data type.
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class Dictionary : public std::map< wstring, T > /* DictionaryMap */



{
public :
    /** 
     * \french
     * La map utilis�e pour le dictionnaire. 
     * \endfrench
     *
     * \english
     * The map data type used for the dictionary.
     * \endenglish
     */
    typedef typename std::map< wstring, T > DictionaryMap;

    /** 
     * \french
     * Le type de l'it�rateur sur le dictionnaire. 
     * \endfrench
     *
     * \english
     * Dictionary iterator data type.
     * \endenglish
     */
    typedef typename DictionaryMap::iterator iterator;

    /** 
     * \french
     * Le type de l'it�rateur constant sur le dictionnaire. 
     * \endfrench
     *
     * \english
     * Dictionary constant iterator data type.
     * \endenglish
     */
    typedef typename DictionaryMap::const_iterator const_iterator;

    /** 
     * \french
     * Le type des valeurs stock�es dans la map du dictionnaire 
     * \endfrench
     *
     * \english
     * The dictionary's value data type.
     * \endenglish
     */
    typedef typename DictionaryMap::value_type value_type;
    
    /**
     * \french
     * Constructeur
     * \endfrench
     *
     * \english
     * Constructor.
     * \endenglish
     */
    Dictionary();
    
    /**
     * \french
     * Destructeur
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~Dictionary();

    /**
     * \french
     * Ajoute un mot et sa d�finition au dictionnaire.
     *
     * Si le mot est d�j� associ� � une d�finition, la d�finition existante
     * est pr�serv�e et retourn�e.
     *
     * @param word Une r�f�rence vers le mot � ajouter.
     * @param definition Une r�f�rence vers la d�finition du mot � ajouter.
     *
     * @return La d�finition associ�e au mot en param�tre.
     * \endfrench
     *
     * \english
     * Adds a word and its definition in the dictionary.
     *
     * If the word already have a definition, it is kept and returned.
     *
     * @param word A reference to the word to add.
     * @param definition A reference to the value associated with the word.
     *
     * @return A reference to the value associated with the added word.
     * \endenglish
     */
    T& insert( const wstring& word, const T& definition );

private :
     
//    friend std::ostream& operator<< < T >( std::ostream& out, 
//                                           const Dictionary< T >& d );
};

/**
 * \french
 * Permet d'afficher le contenu du dictionnaire en format texte.
 *
 * @param out Une r�f�rence vers le flux � travers lequel envoyer la 
 *            description
 * @param d   Une r�f�rence vers le dictionnaire � afficher.
 *
 * @return Le flux utilis�
 * \endfrench
 *
 * \english
 * Print a text representation of a dictionary.
 *
 * @param out A reference to the stream where the dictionary is printed.
 * @param d The dictionary to print.
 *
 * @return A reference to the stream where the dictionary were printed.
 * \endenglish
 */
template< class T >
std::ostream& operator<<( std::ostream& out, const Dictionary< T >& d );

// ------------------------------------------------------------------------ //
template< class T >
Dictionary< T >::Dictionary()
{}


// ------------------------------------------------------------------------ //
template< class T >
Dictionary< T >::~Dictionary()
{}


// ------------------------------------------------------------------------ //
template< class T >
T& Dictionary< T >::insert( const wstring& word, const T& definition )
{
    std::pair< iterator, bool > p;
    
    p = DictionaryMap::insert( value_type( word, definition ) );
     
    return p.first -> second;
}

// ------------------------------------------------------------------------ //

template< class T >
std::ostream& operator<<( std::ostream& out, const Dictionary< T >& d )
{
    // Affiche les objets du dictionnaire
    for( typename Dictionary< T >::const_iterator i = d.begin(); 
         i != d.end(); i++ )
    {
        out << "(" << i -> first << "): " << i -> second << std::endl;
    }

    return out;
}
}// namespace japa

#endif
