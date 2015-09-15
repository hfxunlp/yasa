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

#ifndef JAPA_JAPA_EXCEPTION_H
#define JAPA_JAPA_EXCEPTION_H

#include <exception>
#include <string>

namespace japa
{

/**
 * \french
 * Exception lanc�e lors d'une erreur encontr� par <code>japa</code>
 * \endfrench
 *
 * \english
 * Exception thrown by <code>japa</code>
 * \endenglish
 *
 * @version 1.1
 */
class Exception : public std::exception
{
public :
    /**
     * \french
     * Constructeur.
     *
     * @param what Une description de l'exception.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param what The exception's description.
     * \endenglish
     */
    Exception( const std::string& what );
    
    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~Exception() throw();

    /**
     * \french
     * @return Une description de l'exception.
     * \endfrench
     *
     * \english
     * @return The exception's description.
     * \endenglish
     */
    virtual const char* what() const throw();

private :

    /**
     * \french
     * Une description de l'exception.
     * \endfrench
     *
     * \english
     * The exception's definition.
     * \endenglish
     */
    std::string m_what;
};

}//namespace japa

#endif
