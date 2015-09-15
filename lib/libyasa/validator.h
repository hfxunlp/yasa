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

#ifndef JAPA_VALIDATOR_H
#define JAPA_VALIDATOR_H

namespace japa
{

/**
 * \french
 * Foncteur d�cidant si une donn�e est valide.
 *
 * Interface pour les classes dont les instances agissent comme des filtres.
 * \endfrench
 *
 * \english
 * Fonctor for objects that act as filters.
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class Validator
{
public :
    /**
     * \french
     * D�cide si une donn�e est valide.
     *
     * @param data La donn�e � valider.
     *
     * @return <code>true</code> si la donn�e est valide, <code>false</code>
     *         sinon.
     * \endfrench
     *
     * \english
     * Checks the validity of a data.
     *
     * @param data The data to validate.
     *
     * @return <code>true</code> if the data is valid, <code>false</code>
     *         otherwise. 
     * \endenglish
     */
    virtual bool operator()( const T& data ) = 0;
};

}// namespace japa

#endif
