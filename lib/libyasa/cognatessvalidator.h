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
#ifndef JAPA_COGNATE_SS_VALIDATOR_H
#define JAPA_COGNATE_SS_VALIDATOR_H

#include "validator.h"
#include "wordinfo.h"

namespace japa
{

/**
 * \french
 * Filtre des mots � partir de leurs fr�quence.
 * \endfrench
 *
 * \english
 * Word filter based on frequency.
 * \endenglish
 *
 *
 * @version 1.1
 * @see ::CognateSSF
 */
class CognateSSValidator : public Validator< WordInfo >
{
public :
    /** 
     * \french
     * La fr�quence maximale par d�faut. 
     * \endfrench
     *
     * \english
     * Default maximum frequecy.
     * \endenglish
     */
    static const size_t DEFAULT_MAX_FREQUENCY = 25;
    
    /**
     * \french
     * Constructeur.
     *
     * @param maxFrequency La fr�quence maximum d'un mot.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param maxFrequency Maximum frequency of a word.
     * \endenglish
     */
    CognateSSValidator( const size_t maxFrequency );
    
    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~CognateSSValidator();
    
    bool operator()( const WordInfo& data );

    /**
     * \french
     * Ajuste la fr�quence maximum qu'un mot doit avoir pour �tre accept� par 
     * le filtre.
     *
     * @param frequency La nouvelle fr�quence maximum.
     * \endfrench
     *
     * \english
     * Sets the maximum frequency allowed for a word to be accepted by the
     * filter.
     *
     * @param frequency The new maximum frequency.
     * \endenglish
     */
    void setMaxFrequency( const size_t frequency );

    /**
     * \french
     * Retourne la fr�quence maximum qu'un mot doit avoir pour �tre accept� par
     * le filtre.
     * 
     * @return La fr�quence maximum.     
     * \endfrench
     *
     * \english
     * Gets the maximum frequency allowed for a word to be accepted by the
     * filter
     * 
     * @return The maximum frequency allowed.
     * \endenglish
     */
    size_t getMaxFrequency() const;

private :
    /** 
     * \french
     * La fr�quence maximale d'un mot. 
     * \endfrench
     *
     * \english
     * The maximum allowed frequency of a word.
     * \endenglish
     */
    size_t m_maxFrequency;
};

}// namespace japa

#endif
