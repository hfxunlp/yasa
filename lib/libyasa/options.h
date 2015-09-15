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

#ifndef JAPA_OPTIONS_H
#define JAPA_OPTIONS_H

#include <map>
#include <list>
#include <string>


namespace japa
{

/**
 * \french
 * Contient les diff�rents options et arguments d'un programme.
 * \endfrench
 *
 * \english
 * Command line options and arguments parser.  
 * \endenglish
 * 
 *
 * @version 1.1
 */
class Options
{   
public :     
    /** 
     * \french
     * Le type d'une liste d'options. 
     * \endfrench
     *
     * \english
     * Option list's data type. 
     * \endenglish
     */
    typedef std::list< std::string > OptionList;
    
    /**
     * \french
     * Constructeur.
     *
     * @param optstring La cha�ne repr�sentant le format des options de la 
     *                  ligne de commande.  Le format est le m�me que celui de 
     *                  la fonction <code>getopt</code>.
     *
     * @param handleError Est � <code>true</code> si les messages d'erreur de 
     *                    <code>getopt</code> doivent �tre propag�s.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param optstring An options description string � la <code>getopt</code>.
     * @param handleError Is set to <code>true</code> if <code>getopt</code>
     *        error message must be propagated.
     * \endenglish
     */
    Options( const std::string& optstring, const bool handleError = true );

    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~Options();

    /**
     * \french
     * Analyse les arguments de la ligne de commande.
     * 
     * @param argc Le nombre d'arguments de la ligne de commande.
     * @param argv Les arguments tels que re�us dans la fonction
     *             <code>main</code>.
     * \endfrench
     *
     * \english
     * Parser command line options.
     *
     * @param argc <code>argv</code>'s size.
     * @param argv An array of the argument as received in the
     *             <code>main</code> function.
     * \endenglish
     */
    void parse( int argc, char** argv );

    /**
     * \french
     * Ajuste la valeur d'une option.
     *
     * @param option L'option � changer.
     * @param value La nouvelle valeur de l'option.
     * \endfrench
     *
     * \english
     * Sets an option's value.
     *
     * @param option The option.
     * @param value  The option's new value. 
     * \endenglish
     */
    void setOption( const int option, const std::string& value );
    
    /**
     * @copydoc setOption(const int,const std::string&) 
     */
    void setOption( const int option, const char value );
   
    /**
     * \french
     * V�rifie si une option est pr�sente.
     *
     * @param option L'option � v�rifier.
     *
     * @return <code>true</code> si l'option est pr�sente.
     * \endfrench
     *
     * \english
     * Checks an option's existance.
     *
     * @param option The option to check for.
     *
     * @return <code>true</code> if the option exists.
     * \endenglish
     */
    bool isOption( const int option ) const;
    
    /**
     * \french
     * Trouve la derni�re valeur d'une option.
     *
     * @param option L'option dont il faut trouver la valeur.
     *
     * @return La valeur de l'option sp�cifi�e.
     * \endfrench
     *
     * \english
     * Gets the last value of an option.
     *
     * @param option The option to check for.
     *
     * @return The last value associated with the option. 
     * \endenglish
     */
    std::string getOption( const int option ) const;

    /**
     * \french
     * Trouve toutes les valeurs sp�cifi�e � une option.
     *
     * Une option contient plusieurs valeurs si elle a �t� sp�cifi�e plusieurs
     * fois.
     *
     * @param option L'option dont il faut trouver la liste des valeurs.
     *
     * @return Le liste des valeurs.
     * \endfrench
     *
     * \english
     * Gets all the values associated with an option.
     *
     * An option is associated with many values if it has been specified many
     * times in the command line.
     *
     * @param option The option to check for.
     *
     * @return The option's values.
     * \endenglish
     */
    OptionList getOptionList( const int option ) const;
    
    /**
     * \french
     * Ajuste la valeur d'un argument.
     * 
     * @param indice L'indice de l'argument.
     * @param value  La valeur de l'argument.
     * \endfrench
     *
     * \english
     * Sets the value of an argument.
     *
     * @param indice The index of the argument.
     * @param value The value of the argument. 
     * \endenglish
     */
    void setArgument( const int indice, const std::string& value );

    /**
     * \french
     * Trouve la valeur d'un argument.
     *
     * @param indice L'indice de l'argument, le premier �tant 0.
     *
     * @return La valeur de l'argument.  Si l'argument n'est pas pr�sent, une
     *         cha�ne vide.
     * \endfrench
     *
     * \english
     * Gets the value of an argument.
     *
     * @param indice The argument's index.
     *
     * @return The argument's value.  An empty string is returned if the
     *         argument at the specified index does not exist. 
     * \endenglish
     */
    std::string getArgument( const int indice );
    
    /**
     * \french
     * Signale une erreur.
     *
     * @param description Une description de l'erreur.
     * \endfrench
     *
     * \english
     * Display an error.
     *
     * @param description The error's description. 
     * \endenglish
     */
    virtual void error( const std::string& description );

private :
    
    /** 
     * \french
     * Le type de la structure contenant les options. 
     * \endfrench
     *
     * \english
     * Option holder's data type. 
     * \endenglish
     */
    typedef std::map< int, OptionList > OptionMap;

    /** 
     * \french
     * Le type de la structure contenant les arguments. 
     * \endfrench
     *
     * \english
     * Argument holder's data type. 
     * \endenglish
     */
    typedef std::map< int, std::string > ArgumentMap; 
    
    /** 
     * \french
     * Le format des options de la ligne de commande. 
     * \endfrench
     *
     * \english
     * Command line options' specification. 
     * \endenglish
     */
    const std::string m_optstring;

    /** 
     * \french
     * Les options du programme. 
     * \endfrench
     *
     * \english
     * Program's options. 
     * \endenglish
     */
    OptionMap m_options;

    /** 
     * \french
     * Les arguments du programme. 
     * \endfrench
     *
     * \english
     * Program's arguments. 
     * \endenglish
     */
    ArgumentMap m_arguments;
};

}// namespace japa

#endif
