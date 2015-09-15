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

/**@file
 * \french
 * Contient des fonctions d'utilit� g�n�rale.
 * \endfrench
 *
 * \english
 * Contains general purposes functions. 
 * \endenglish
 *
 *
 * @version 1.1
 */

#ifndef JAPA_TOOLBOX_H
#define JAPA_TOOLBOX_H

using namespace std;

#include <iostream>
#include <string>
#include <sstream>

namespace japa
{

/**
 * \french
 * Remplace les caract�res accentu�s d'une phrase par leurs �quivalents
 * non-accentu�s.
 *
 * @param str La cha�ne � traiter.
 * 
 * @return La cha�ne trait�e ( Une r�f�rence vers le param�tre ).
 * \endfrench
 *
 * \english
 * Replace the accentuated characters of a sentence by their equivalents
 * whithout accents.
 * 
 * @param str The string to process.
 *
 * @return A reference to the processed string ( a reference to the parameter ).
 * \endenglish
 */
wstring& stripAccents( wstring& str );

/**
 * \french
 * Enl�ve les espaces se trouvant au d�but d'un flux entrant.
 *
 * @param in Le flux entrant auquel enlever les espaces.
 *
 * @return Le nombre d'espaces qui ont �t� enlev�es.
 * \endfrench
 *
 * \english
 * Removes the white spaces at the beginning of a stream.
 *
 * @param in The stream to process.
 *
 * @return The number of removed white spaces.
 * \endenglish
 */
int stripSpaces( std::wistream& in );

/**
 * \french
 * V�rifie si un mot est form� uniquement de caract�res alphab�tiques.
 *
 * @param str La cha�ne � v�rifier.
 * @return <code>true</code> si la cha�ne est uniquement alphab�tique.
 * \endfrench
 *
 * \english
 * Checks if a word contains only alphabetic characters.
 *
 * @param str The string to check.
 *
 * @return <code>true</code> if the string contains only alphabetic
 *         characters. 
 * \endenglish
 */
bool isAlphabetic( const wstring& str );

/**
 * \french
 * Convertit chaque caract�re d'une cha�ne en majuscule.
 *
 * @param str La cha�ne � convertir.
 * 
 * @return La cha�ne convertie ( une r�f�rence vers le param�tre ).
 * \endfrench
 *
 * \english
 * Put all the characters of a string into upper case.
 *
 * @param str The string to process.
 *
 * @return The converted string ( a reference to the parameter ). 
 * \endenglish
 */
wstring& toUpperCase( wstring& str );

/**
 * \french
 * V�rifie si un caract�re est un d�limiteur de mot.
 *
 * @param c Le caract�re � v�rifier.
 *
 * @return <code>true</code> si le caract�re est un d�limiteur de mots.
 * \endfrench
 *
 * \english
 * Checks if a character is a word delimiter.
 *
 * @param c The character to check.
 *
 * @return <code>true</code> if the character is effectively a word delimiter. 
 * \endenglish
 */
bool isDelimiter(  wchar_t c );

/**
 * \french
 * V�rifie si un caract�re est un d�limiteur de mot qui est un mot.
 *
 * @param c Le caract�re � v�rifier.
 * 
 * @return <code>true</code> si le caract�re est un d�limiteur de mots.
 * \endfrench
 *
 * \english
 * Checks if a character is a word delimiter that is also a word.
 *
 * @param c The character to check.
 *
 * @return <code>true</code> if the character is effectively a word delimiter
 *         that is also a word.
 * \endenglish
 */
bool isWordDelimiter( wchar_t c );

/**
 * \french
 * Convertit une donn�e d'un type de base en cha�ne de caract�res.
 *
 * @param n La donn�e � convertir.
 *
 * @return La cha�ne de caract�re d�finissant le type de base.
 * \endfrench
 *
 * \english
 * Convert a object of which the class implement the <code><<</code>
 * operator into a string.
 *
 * @param n The data to convert.
 *
 * @return The string representation of the object.
 * \endenglish
 */
template< class T > string toString( const T n )
{
    std::ostringstream oss;

    oss << n;

    return oss.str();
}

/**
 *
 */

template< class T > wstring toString1( const T n )
{
    std::wostringstream oss;

    oss << n;

    return oss.str();
}

/**
 *
 */
wstring strToWstr( const string str );



}// namespace japa

#endif
