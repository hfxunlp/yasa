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
 * Contient des fonctions permettant d'appliquer des filtres sur des fichiers.
 * \endfrench
 *
 * \english
 * Contains functions that act as a filter on files.
 * \endenglish
 *
 *
 * @version 1.1
 */

#ifndef JAPA_FILTER_H
#define JAPA_FILTER_H

#include <fstream>
#include <string>

namespace japa
{

/**
 * \french
 * Mn�monique utilis� pour le nom du fichier d'entr�e.
 * \endfrench
 *
 * \english
 * Input file's mnemonic.
 * \endenglish
 */
static const std::string INPUT_FILE_MNEMONIC = "@IN";

/**
 * \french
 * Mn�monique utilis� pour le nom du fichier de sortie.
 * \endfrench
 *
 * \english
 * Output file's mnemonic.
 * \endenglish
 */
static const std::string OUTPUT_FILE_MNEMONIC = "@OUT";



/**
 * \french
 * Applique un filtre sur un fichier.
 *
 * @param filter Le filtre � utiliser.  Le format du filtre est le suivant :
 *               <code>commande ... INPUT_FILE_MNEMONIC ... 
 *               OUTPUT_FILE_MNEMONIC ... </code> o� la commande et
 *               les ... peuvent �tre n'importe quoi.  Les champs @IN et @OUT
 *               seront remplac�s par le noms de fichier d'entr�e et le nom de
 *               fichier de sortie.
 *               
 * @param inputFile Le chemin du fichier d'entr�e. 
 * 
 * @param stream Le flux qui sera ouvert sur le fichier filtr�.
 *
 * @return <code>true</code> si aucune erreur ne s'est produite,
 *         <code>false</code> sinon.
 * \endfrench
 *
 * \english
 * Apply a filter on a file.
 *
 * @param filter The filter to apply.  The filter format is the following :
 *               <code>commande ... INPUT_FILE_MNEMONIC ... 
 *               OUTPUT_FILE_MNEMONIC ... </code> where command and
 *               ... can be anything.  The @IN and @OUT fields will be
 *               replaced by the input file and the output file respectively.
 *
 * @param inputFile The path to the input file.
 *
 * @param stream The stream that will be openned on the filtered file.
 *
 * @return <code>true</code if the function succeeds, <code>false</code>
 *         otherwise.
 * \endenglish
 */
void inputFilter( const std::string filter, const std::string inputFile, 
        std::ifstream& stream );


/**
 * \french
 * Applique un filtre gunzip sur un fichier.
 *
 * @note La commande <code>zcat</code> doit �tre accessible � partir du
 *      <code>PATH</code>.
 *      
 * @param stream Le flux qui sera ouvert sur le fichier filtr�.
 *
 * @return <code>true</code> si aucune erreur ne s'est produite,
 *         <code>false</code> sinon.
 * \endfrench
 *
 * \english
 * Apply a gunzip filter on a file.
 *
 * @note The <code>zcat</code> must be in the <code>PATH</code>.
 *
 * @param inputFile The path to the input file.
 *
 * @param stream The stream that will be openned on the gunzipped file.
 *
 * @return <code>true</code if the function succeeds, <code>false</code>
 *         otherwise.
 * \endenglish
 */
void gunzip( const std::string inputFile, std::ifstream& stream );

} //namespace japa

#endif
