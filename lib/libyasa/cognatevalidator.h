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

#ifndef JAPA_COGNATE_VALIDATOR_H
#define JAPA_COGNATE_VALIDATOR_H

using namespace std;

#include "validator.h"
#include "wordinfo.h"

namespace japa
{

/**
 * \french
 * V�rifie si un mot est un candidat pour �tre un cognate.
 * \endfrench
 *
 * \english
 * Filter that checks if a word is a possible cognate.
 * \endenglish
 *
 *
 * @version 1.1
 */
class CognateValidator : public Validator< WordInfo >
{
public :

    /** 
     * \french
     * La longueur minimale par d�faut. 
     * \endfrench
     *
     * \english
     * Default minimum length.
     * \endenglish
     */
    static const size_t DEFAULT_MIN_LENGTH = 4;
    
    /**
     * \french
     * Constructeur.
     *
     * @param minLength La longueur minimale d'un cognate uniquement
     *                  alphab�tique.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param minLength The minimum lenght of an alphabetic cognate.
     * \endenglish
     */
    CognateValidator( size_t minLength = DEFAULT_MIN_LENGTH );

    bool operator()( const WordInfo& data );

    /**
     * \french
     * Ajuste la longueur minimum qu'un mot strictement alphab�tique doit avoir 
     * pour �tre consid�r� comme cognate potentiel.
     *
     * @param length La nouvelle longueur minimum.
     * \endfrench
     *
     * \english
     * Set the minimum length of an alphabetic cognate.
     *
     * @param length The new minimum length.
     * \endenglish
     */
    void setMinLength( const size_t length );

    /**
     * \french
     * Retourne la longueur minimum qu'un mot strictement alphab�tique doit 
     * avoir  pour �tre consid�r� comme cognate potentiel.
     * 
     * @return La longueur minimum.
     * \endfrench
     *
     * \english
     * Gets the minimum length of an alphabetic cognate.
     * \endenglish
     */
    size_t getMinLength() const;

private :

    /** 
     * \french
     * La longueur minimale d'un mot uniquement alphab�tique. 
     * \endfrench
     *
     * \english
     * The minimum length of an alphabetic cognate.
     * \endenglish
     */
    size_t m_minLength;
};

}// namespace japa

#endif
