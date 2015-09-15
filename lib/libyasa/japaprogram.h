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

#ifndef JAPA_JAPA_PROGRAM_H
#define JAPA_JAPA_PROGRAM_H

#include <iostream>
#include <memory>

#include "churchgalescore.h"
#include "cognatevalidator.h"
#include "dynamictable.h"
#include "japaoptions.h"
#include "scorefunction.h"
#include "searchspace.h"
#include "searchspacefiller.h"
#include "solutionmarker.h"
#include "solutionprinter.h"
#include "text.h"
#include "textparser.h"

namespace japa
{

/**
 * \french
 * Programme <code>japa</code>.
 *
 * Permet d'initialiser et de lancer l'alignement de phrases.
 * \endfrench
 *
 * \english
 * <code>japa</code> program.
 *
 * Interface to launch sentences alignment.
 * \endenglish
 *
 *
 * @version 1.1
 */
class JapaProgram : public JapaOptions
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
    JapaProgram();
    
    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~JapaProgram();
    
    /**
     * \french
     * Aligne deux textes parall�les.
     * \endfrench
     *
     * \english
     * Align two parallel texts.
     * \endenglish
     */
    void run();
    /**
         * \ma partie
         */
    void calc();
    
private :    
    /**
     * \french
     * Initialise les flux de donn�es.
     * \endfrench
     *
     * \english
     * Object's streams initializer.
     * \endenglish
     */
    void initStreams();
    
    /**
     * \french
     * Initialise les textes.
     * \endfrench
     *
     * \english
     * Text initializer.
     * \endenglish
     */
    void initText();

    /**
     * \french
     * Initialisation des cognates
     * \endfrench
     *
     * \english
     * Cognate initializer.
     * \endenglish
     */
    void initCognate();
   
    /**
     * \french
     * Initialise les cognates en mode pr�fixe.
     * \endfrench
     *
     * \english
     * Prefix cognate initializer.
     * \endenglish
     */
    void initCognatePrefix();

    /**
     * \french
     * Initialise le valideur de cognates.
     * \endfrench
     *
     * \english
     * Cognate validator initializer.
     * \endenglish
     */
    void initCognateValidator( CognateValidator& cv );
    
    /**
     * \french
     * Initialise les cognates en mode mot.
     * \endfrench
     *
     * \english
     * Word cognate initializer.
     * \endenglish
     */
    void initCognateWord();
   
    /**
     * \french
     * Initialise le dictionnaire des synonymes.
     * \endfrench
     *
     * \english
     * Synonym dictionaries initializer.
     * \endenglish
     */
    void initSynonymDictionaries();

    /**
     * \french
     * Initialise les alignements sp�cifi�s par l'utilisateur.
     * \endfrench
     *
     * \english
     * User defined alignments initializer.
     * \endenglish
     */
    void initAlignments();
    
    /**
     * \french
     * Initialise le score Felipe.
     * \endfrench
     *
     * \english
     * Felipe score's initializer. 
     * \endenglish
     */
    void initScoreFelipe();
    
    /**
     * \french
     * Initialise l'espace de recherche.
     * \endfrench
     *
     * \english
     * Search space's initializer. 
     * \endenglish
     */
    void initSearchSpace();

    /**
     * \french
     * Initialise l'espace de recherhce "cognate".
     * \endfrench
     *
     * \english
     * Cognate search space's initializer. 
     * \endenglish
     */
    void initSearchSpaceCognate();
    
    /**
     * \french
     * Initialise la r�solution de la solution.
     * \endfrench
     *
     * \english
     * Initialize dynamic programming algorithm. 
     * \endenglish
     */
    void initTable();
    
    /**
     * \french
     * Initialise l'impression des r�sultats.
     * \endfrench
     *
     * \english
     * Result printer's initializer. 
     * \endenglish
     */
    void initPrinter();
    
    /**
     * \french
     * Affiche un message en mode verbeux.
     *
     * @param msg Le message � afficher.
     *  \endfrench
     *
     * \english
     * Print a verbose level message.
     *
     * @param msg The message to be printed. 
     * \endenglish
     */ 
    void verbose( const std::string msg );
   
    /**
     * \french
     * Affiche un message en mode tr�s verbeux.
     *
     * @param msg Le message � afficher.
     *  \endfrench
     *
     * \english
     * Print a very verbose level message.
     *
     * @param msg The message to be printed. 
     * \endenglish
     */ 
    void veryVerbose( const std::string msg );
   
    
    /** 
     * \french
     * Le texte source. 
     * \endfrench
     *
     * \english
     * Source text. 
     * \endenglish
     */
    std::auto_ptr< Text > m_source;

    /** 
     * \french
     * Le texte cible. 
     * \endfrench
     *
     * \english
     * Target text. 
     * \endenglish
     */
    std::auto_ptr< Text > m_target;

    /** 
     * \french
     * L'emplisseur de l'espace de recherche. 
     * \endfrench
     *
     * \english
     * Search space filler. 
     * \endenglish
     */
    std::auto_ptr< SearchSpaceFiller > m_SSFiller;

    /** 
     * \french
     * Le marqueur de solution. 
     * \endfrench
     *
     * \english
     * Solution marker. 
     * \endenglish
     */
    std::auto_ptr< SolutionMarker > m_solutionMarker;

    /** 
     * \french
     * L'espace solution. 
     * \endfrench
     *
     * \english
     * Solution's search space. 
     * \endenglish
     */
    std::auto_ptr< SearchSpace > m_searchSpace;

    /** 
     * \french
     * La fonction de score. 
     * \endfrench
     *
     * \english
     * Score function. 
     * \endenglish
     */
    std::auto_ptr< ChurchGaleScore > m_scoreFunction;

    /** 
     * \french
     * La table dynamique. 
     * \endfrench
     *
     * \english
     * The dynamic table that solves the alignment problem. 
     * \endenglish
     */
    std::auto_ptr< DynamicTable< double > > m_dynamicTable;

    /** 
     * \french
     * L'afficheur de solution. 
     * \endfrench
     *
     * \english
     * Solution printer. 
     * \endenglish
     */
    std::auto_ptr< SolutionPrinter< double > > m_solutionPrinter;
 
    /** 
     * \french
     * Le flux vers lequel la solution est envoy�e. 
     * \endfrench
     *
     * \english
     * The stream where the solution is to be printed. 
     * \endenglish
     */
    std::wostream* m_solutionStream;

    /** 
     * \french
     * Le flux vers lequel les messages sont envoy�es. 
     * \endfrench
     *
     * \english
     * The stream where the messages to the user are to be printed. 
     * \endenglish
     */
    std::ostream* m_messagesStream;
        
    /** 
     * \french
     * Le nombre de retours permis lors de la recherche de cognates. 
     * \endfrench
     *
     * \english
     * Maximum number of returns allowed when computing the cognate 
     * search space. 
     * \endenglish
     */
    size_t m_cognateReturn;
};

}// namespace japa

#endif
