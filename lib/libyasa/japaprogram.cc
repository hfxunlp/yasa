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

#include <cstdlib>
#include <fstream>
#include <ctime>
//mes tests

#include <iostream>
using namespace std;


#include "alignment.h"
#include "arcadeparser.h"
#include "arcadeprinter.h"
#include "beamssf.h"
#include "bitextsynonymcontainer.h"
#include "cesalignprinter.h"
#include "cesanaparser.h"
#include "cognatessf.h"
#include "constantbeammarker.h"
#include "felipescore.h"
#include "filter.h"
#include "friendlyprinter.h"
#include "japaprogram.h"
#include "japasynonymparser.h"
#include "onesentperlineparser.h"
#include "prefixcognatefinder.h"
#include "raliparser.h"
#include "raliprinter.h"
#include "scoreprinter.h"
#include "setsearchspace.h"
#include "sparsedt.h"
#include "toolbox.h"
#include "wordcognatefinder.h"


namespace japa
{

// ------------------------------------------------------------------------ //
/**
 * Ajuste la valeur d'un pointeur automatique � un pointeur.
 *
 * @param autoptr Le pointeur automatique.
 * @param ptr Le pointeur � contenir.
 */
template< class T, class S >
void setPtr( std::auto_ptr< T >& autoptr, S* ptr )
{
    //std::auto_ptr< T > p( ptr );
    //autoptr = p;
    autoptr.reset (ptr);
}

// ------------------------------------------------------------------------ //
JapaProgram::JapaProgram() : m_solutionStream( NULL )
{}

// ------------------------------------------------------------------------ //
JapaProgram::~JapaProgram()
{
    // Ferme les flux
    if( m_solutionStream != NULL && m_solutionStream != &std::wcout )
    {
        ( ( std::wofstream* ) m_solutionStream ) -> close();
        delete m_solutionStream;
    }
}

// ------------------------------------------------------------------------ //
void JapaProgram::run()
{
    time_t startTime = time( NULL );
    
    if( isOption( HELP ) )
    {
        std::cout << getOnlineHelp() << std::endl;
    }
    else
    {
        // Initialise les composants
    	initStreams();
        initText();
        initCognate();

        initSynonymDictionaries();
        initSearchSpace();
        initTable();
        initPrinter(); 
        
        // Remplit l'espace de recherche
        verbose( "Filling search space" );
        ( *m_SSFiller )( *m_searchSpace );

        // Aligne les phrases
        verbose( "Finding best alignment" );
        m_dynamicTable -> solve();
        
        // Affiche les r�sultats
        DynamicTable< double >::Iterator iter = m_dynamicTable -> getIterator();
        std::list< Alignment< double > > l = buildAlignment< double >( iter );

        verbose( "Printing solution" );
        ( *m_solutionPrinter )( *m_solutionStream, l );

        verbose( toString( "japa took " ) + 
                 toString( time( NULL ) - startTime ) + 
                 " seconds to align bi-text." );

    }
}

// ------------------------------------------------------------------------ //
void JapaProgram::initStreams()
{
    std::string sol = getArgument( OUTPUT_FILE );
    
    // Initialise les flux de la solution et des messages.
    if( sol.empty() )
    {
        m_solutionStream = &std::wcout;
        m_messagesStream = &std::cerr;
    } 
    else
    {
        m_solutionStream = new std::wofstream( sol.c_str() );
        
        if( m_solutionStream -> fail() )
        {
            // Erreur avec le fichier source
            std::string desc( "Can't write solution to file : " );
            desc += sol;
            
            error( desc );
        } 
        
        m_messagesStream = &std::cout;
    }
}

// ------------------------------------------------------------------------ //
void JapaProgram::initText()
{
    char c;
    std::auto_ptr< TextParser > srcTextParser;
    std::auto_ptr< TextParser > tgtTextParser;
    std::wifstream sourceStream;
    std::wifstream targetStream;

    // Tra�te le format de compression de l'entr�e
    c = getOption( INPUT_COMPRESSION )[ 0 ];

    switch( c )
    {
    case INPUT_COMPRESSION_NONE :
    	//cout << "le fichier 1 est " << getArgument( SOURCE_FILE ).c_str() << endl;
    	//cout << "le fichier 2 est " << getArgument( TARGET_FILE ).c_str() << endl;
        sourceStream.open( getArgument( SOURCE_FILE ).c_str() );
        targetStream.open( getArgument( TARGET_FILE ).c_str() );
        break;

    //case INPUT_COMPRESSION_GZIP :
    //    gunzip( getArgument( SOURCE_FILE ), sourceStream );
    //    gunzip( getArgument( TARGET_FILE ), targetStream );
    //    break;

    default :
        std::string desc( "Unknown input compression : " );
        desc += c;
        error( desc );
        break;
    }
    
    if( sourceStream.fail() )
    {
        // Erreur avec le fichier source
        std::string desc( "Can't read file : " );
        desc += getArgument( SOURCE_FILE );
        
        error( desc );
    } 

    if( targetStream.fail() )
    {
        // Erreur avec le fichier cible
        std::string desc( "Can't read file : " );
        desc += getArgument( TARGET_FILE );

        error( desc );
    }

    
    setPtr( m_source, new Text() );
    setPtr( m_target, new Text() );

    // Traite le format de l'entr�e
    c = getOption( INPUT_FORMAT )[ 0 ];
    
    switch( c )
    {
    case INPUT_FORMAT_ARCADE :
        // Format arcade
        veryVerbose( "Input format : ARCADE" );
        setPtr( srcTextParser, new ArcadeParser() );
        setPtr( tgtTextParser, new ArcadeParser() );
        break;

    case INPUT_FORMAT_CESANA :
        // Format cesana
        veryVerbose( "Input format : CESANA" );
        setPtr( srcTextParser, new CesanaParser() );
        setPtr( tgtTextParser, new CesanaParser() );
        break;
    
    case INPUT_FORMAT_OSPL :
        // Format une phrase par ligne
        veryVerbose( "Input format : ONE SENTENCE PER LINE" );
        setPtr( srcTextParser, new OneSentPerLineParser() );
        setPtr( tgtTextParser, new OneSentPerLineParser() );
        break;
        
    case INPUT_FORMAT_RALI :
        // Format RALI
        veryVerbose( "Input format : RALI ( GLM )" );
        setPtr( srcTextParser, new RaliParser() );
        setPtr( tgtTextParser, new RaliParser() );
        break;
        
    default :
        std::string desc( "Unknown input format : " );
        desc += c;
        error( desc );
        break;    
    }

    verbose( "Parsing source" );
    ( *srcTextParser )( sourceStream, *m_source );

    veryVerbose( std::string( "Source contains " ) + 
                 toString( m_source -> getSentenceCount() ) +
                 " sentences and " + toString( m_source -> getWordCount() ) +
                 " words." );
    
    verbose( "Parsing target" );
    ( *tgtTextParser )( targetStream, *m_target );
    
    veryVerbose( std::string( "Target contains " ) + 
                 toString( m_target -> getSentenceCount() ) +
                 " sentences and " + toString( m_target -> getWordCount() ) +
                 " words." );

    sourceStream.close();
    targetStream.close();
}

// ------------------------------------------------------------------------ //
void JapaProgram::initCognate()
{
    char c;
    
    // Traite le type de cognates
    c = getOption( COGNATE )[ 0 ];
    verbose( "Finding cognates" );

    switch( c )
    {
    case COGNATE_NONE :
        // Aucun cognate, rien � faire.
        veryVerbose( "Cognate mode : NONE" );
        break;

    case COGNATE_PREFIX :
        // Cognate de type pr�fixe
        veryVerbose( "Cognate mode : PREFIX" );
        initCognatePrefix();    
        break;
    
    case COGNATE_WORD :
        // Cognate au niveau des mots
        veryVerbose( "Cognate mode : WORD" );
        initCognateWord();
        break;

    default :
        std::string desc( "Unknown cognate option : " );
        desc += c;
        error( desc );
        break;    
    }
}

// ------------------------------------------------------------------------ //
void JapaProgram::initCognateValidator( CognateValidator& cv )
{
    int minLength;
     
    // Initialise la longueur minimale d'un cognate
    minLength = atoi( getOption( COGNATE_MIN_LENGTH ).c_str() );
    veryVerbose( toString( "Cognate minimum length : " ) + 
                 toString( minLength ) );

    cv.setMinLength( minLength );
}

// ------------------------------------------------------------------------ //
void JapaProgram::initCognateWord()
{
    CognateValidator cv;
    WordCognateFinder wcf;

    initCognateValidator( cv );
    
    wcf( *m_source, *m_target, cv );
}

// ------------------------------------------------------------------------ //
void JapaProgram::initSynonymDictionaries()
{
    OptionList ol = getOptionList( SYNONYM_DICTIONARY );
    OptionList::const_iterator iter;
    std::string filename;
    BitextSynonymContainer bsc( m_source -> getDictionary(), 
            m_target -> getDictionary() );    
    JapaSynonymParser parser;
    std::wifstream in;
    
    // Pour chaque alignement sp�cifi�
    for( iter = ol.begin(); iter != ol.end(); iter++ )
    {
        filename = *iter;
        
        veryVerbose( toString("Parsing synonym dictionary : " ) + filename );
        in.open( filename.c_str() );

        if( in.fail() )
        {
            error( toString("Can't open synonym dictionary : " ) + filename );
        }
            
        parser( in, bsc );
    }

}

// ------------------------------------------------------------------------ //
void JapaProgram::initCognatePrefix()
{
    CognateValidator cv;
    int prefixLength; 
    PrefixCognateFinder pcf;
    
    // Touve la longueur du pr�fixe
    prefixLength = atoi( getOption( COGNATE_PREFIX_LENGTH ).c_str() );
    pcf.setPrefixLength( prefixLength );
    
    veryVerbose( toString( "Prefix length : " ) + toString( prefixLength ) );

    initCognateValidator( cv );
    
    // Trouve les cognates
    pcf( *m_source, *m_target, cv );
}

// ------------------------------------------------------------------------ //
void JapaProgram::initSearchSpace()
{
    char c;
    int beamRadius;
    const size_t srcSize = m_source -> getSentenceCount();
    const size_t tgtSize = m_target -> getSentenceCount();
    
    verbose( "Initialising search space" );
    
    // Initialise l'espace de recherche
    setPtr( m_searchSpace, 
            new SetSearchSpace( -1, -1, srcSize - 1, tgtSize - 1 ) );

    // Initialisation du faisceau utilis�
    beamRadius = atoi( getOption( BEAM_RADIUS ).c_str() );
    setPtr( m_solutionMarker, new ConstantBeamMarker( beamRadius ) );
    veryVerbose( std::string( "Beam radius : " ) + toString( beamRadius ) );
    
    // Initialise l'emplisseur de l'espace de recherche
    c = getOption( SEARCH_SPACE )[ 0 ];
    
    switch( c )
    {
    case SEARCH_SPACE_BEAM :
        // Espace de recherche par faisceau
        veryVerbose( "Search space : BEAM" );
        setPtr( m_SSFiller, new BeamSSF( *m_solutionMarker ) );
        break;
        
    case SEARCH_SPACE_COGNATE :
        // Espace de recherche tenant rigueur des cognates
        veryVerbose( "Search space : COGNATE" );
        initSearchSpaceCognate();
        break;

    default :
        // Espace de recherche inconnu
        std::string desc( "Unknow search space : " );
        desc += c;
        error( desc );
        break;
    }
}

// ------------------------------------------------------------------------ //
void JapaProgram::initSearchSpaceCognate()
{
    int returnCount;
    double returnCost;
    size_t radius;
    size_t maxFrequency;
    
    // Trouve le nombre de retours permis
    returnCount = atoi( getOption( COGNATE_RETURN_COUNT ).c_str() ); 
    veryVerbose( toString( "Number of returns allowed : " ) + 
                 toString( returnCount ) );
    
    // Trouve le co�t d'un retour
    returnCost = strtod( getOption( COGNATE_RETURN_COST ).c_str(), NULL );
    veryVerbose( toString( "Return cost : " ) + toString( returnCost ) );
    
    // Trouve la d�viance maximum permise
    radius = atoi( getOption( COGNATE_RADIUS ).c_str() );
    veryVerbose( toString( "Maximum cognate deviance : " ) + 
            toString( radius ) );
    
    // Initialise la fr�quence maximale d'un cognate
    maxFrequency = atoi( getOption( COGNATE_MAX_FREQUENCY ).c_str() );
    veryVerbose( toString( "Cognate maximum frequency : " ) +
                 toString( maxFrequency ) );

    // Cr�e l'emplisseur de l'espace de recherche
    setPtr( m_SSFiller, new CognateSSF( *m_source, *m_target, 
                                        *m_solutionMarker, 
                                        returnCount, returnCost, 
                                        radius, maxFrequency ) );
    
}

// ------------------------------------------------------------------------ //
void JapaProgram::initTable()
{
    char c; 
    double var; // La variance Church and Gale
    double production;  // La production Church and Gale
    double matchWeight; // Le poid du match de Church and Gale    
    double penaltyWeight;   // Le poid de la p�nalit� de Church and Gale
    
    verbose( "Initialising resolution options" );
    
    // Ajuste la fonction de score utilis�e
    c = getOption( SCORE_FUNCTION )[ 0 ];

    switch( c )
    {
    case SCORE_FUNCTION_FELIPE :
        // Fonction de score Felipe
        veryVerbose( "Score function : FELIPE" );
        initScoreFelipe();
        break;

    case SCORE_FUNCTION_CHURCH_GALE :
        // Fonction de score Gale & Church
        veryVerbose( "Score function : GALE AND CHURCH" );
        setPtr( m_scoreFunction, new ChurchGaleScore( *m_source, *m_target ) );
        break;

    default :
        std::string desc( "Unknown score function : " );
        desc += c;
        error( desc );
        break;
    }    
    
    // Ajoute les possibilit�s d'alignements
    initAlignments();
    
    // Ajuste la production pour le score Church and Gale
    production = strtod( getOption( CHURCH_GALE_PRODUCTION ).c_str(), NULL );
    veryVerbose( toString( "Source character production : " ) +
                 toString( production ) );
    m_scoreFunction -> setProduction( production );
    
    // Ajuste la variance pour le score Church and Gale
    var = strtod( getOption( CHURCH_GALE_VARIANCE ).c_str(), NULL );
    veryVerbose( toString( "Sentences length variance : " ) + toString( var ) );
    m_scoreFunction -> setVariance( var );

    // Ajuste le poid du match
    matchWeight = strtod( getOption( CHURCH_GALE_MATCH ).c_str(), NULL );
    veryVerbose( toString( "Match weight : " ) + toString( matchWeight ) );
    m_scoreFunction -> setMatchWeight( matchWeight );

    // Ajuste le poid de la p�nalit�
    penaltyWeight = strtod( getOption( CHURCH_GALE_PENALTY ).c_str(), NULL );
    veryVerbose( toString( "Penalty weight : " ) + toString( penaltyWeight ) );
    m_scoreFunction -> setPenaltyWeight( penaltyWeight );
    
    // Ajuste la table dynamique utilis�e
    setPtr( m_dynamicTable, 
            new SparseDT< double >( *m_searchSpace, *m_scoreFunction ) );
}

// ------------------------------------------------------------------------ //
void JapaProgram::initAlignments()
{
    int sourceLength;
    int targetLength;
    double prob;
    char sep;
    OptionList ol = getOptionList( CHURCH_GALE_ALIGNMENT );
    OptionList::const_iterator iter;
    
    // Pour chaque alignement sp�cifi�
    for( iter = ol.begin(); iter != ol.end(); iter++ )
    {
        std::istringstream str( *iter );

        str >> sourceLength >> sep >> targetLength >> sep >> prob;
        
        m_scoreFunction -> addAlignment( sourceLength, targetLength, prob );
        
        veryVerbose( toString( "Alignment added : " ) +
                     toString( sourceLength ) + "-" + 
                     toString( targetLength ) + "-" +
                     toString( prob ) );
    }
    
}

// ------------------------------------------------------------------------ //
void JapaProgram::initScoreFelipe()
{
    FelipeScore* score;
    double cgWeight;
    double simardWeight;
    double cpt;
    double cpnt;
    FullFelipeMode mode = NONE;
    double correction;
    char c;
    
    score = new FelipeScore( *m_source, *m_target );

    // Initialise le poid de Church and Gale
    cgWeight = strtod( getOption( FELIPE_CHURCH_GALE_WEIGHT ).c_str(), NULL );
    veryVerbose( toString( "Church and Gale weight : " ) + 
                 toString( cgWeight ) );
    score -> setChurchGaleWeight( cgWeight );

    // Initialise le poid de Simard
    simardWeight = strtod( getOption( FELIPE_SIMARD_WEIGHT ).c_str(), NULL );
    veryVerbose( toString( "Simard weight : " ) + toString( simardWeight ) );
    score -> setSimardWeight( simardWeight );

    // Initialise la probabilit� d'un cognate dans une traduction
    cpt = strtod( getOption( SIMARD_CPT ).c_str(), NULL );
    veryVerbose( toString( "Cognate probability in traduction : " ) + 
                 toString( cpt ) );
    score -> setCPT( cpt );

    // Initialise la probabilit� d'un cognate dans une non-traduction
    cpnt = strtod( getOption( SIMARD_CPNT ).c_str(), NULL );
    veryVerbose( toString( "Cognate probability not in traduction : " ) +
                 toString( cpnt ) );
    score -> setCPNT( cpnt );

    // Initialisation du mode FullFelipe
    c = getOption( FELIPE_MODE )[ 0 ];
    switch( c )
    {
    case FELIPE_MODE_ALL :
        veryVerbose( "FullFelipe mode : All" );
        mode = ALL;
        break;
        
    case FELIPE_MODE_CHURCHGALE :
        veryVerbose( "FullFelipe mode : Church and Gale" );
        mode = CHURCHGALE;
        break;
    
    case FELIPE_MODE_NONE :
        veryVerbose( "FullFelipe mode : None" );
        mode = NONE;
        break;
        
    case FELIPE_MODE_SIMARD :
        veryVerbose( "FullFelipe Mode : Simard" );
        mode = SIMARD;
        break;

    default :
        error( toString( "Unknown FullFelipe Mode : " ) + toString( c ) );
        break;
    }

    score -> setMode( mode );
    
    // Initialisation de la correction
    correction = strtod( getOption( FELIPE_CORRECTION ).c_str(), NULL );
    veryVerbose( toString( "FullFelipe correction : " ) + 
                 toString( correction ) );
    
    score -> setCorrection( correction );
    
    setPtr( m_scoreFunction, score );
}

// ------------------------------------------------------------------------ //
void JapaProgram::initPrinter()
{
    char c;
    
    verbose( "Initialising printing options" );    
    
    // Ajuste le format de la solution
    c = getOption( OUTPUT_FORMAT )[ 0 ];

    switch( c )
    {
    case OUTPUT_FORMAT_ARCADE :
        // Format de sortie arcade
        veryVerbose( "Output format : ARCADE" );
        setPtr( m_solutionPrinter, new ArcadePrinter< double >( *m_source, *m_target ) );
        break;

    case OUTPUT_FORMAT_CESALIGN :
        // Format de sortie CesAlign
        veryVerbose( "Output format  : CESALIGN" );
        setPtr( m_solutionPrinter,
                new CesalignPrinter< double >( *m_source, *m_target,
                		strToWstr(getArgument( SOURCE_FILE )),
                		strToWstr(getArgument( TARGET_FILE ))
                		));
        break;
        
    //case OUTPUT_FORMAT_FRIENDLY :
        // Format de sortie gentil
    //    veryVerbose( "Output format : FRIENDLY" );
    //    setPtr( m_solutionPrinter,
    //            new FriendlyPrinter< double >( *m_source, *m_target ) );
    //    break;
   
    case OUTPUT_FORMAT_RALI :
        // Format de sortie du RALI
        veryVerbose( "Output format : RALI" );
        setPtr( m_solutionPrinter, new RaliPrinter< double >() );
        break;
        
    case OUTPUT_FORMAT_SCORE :
        // Format de sortie Score
        veryVerbose( "Output format  : SCORE" );
        setPtr( m_solutionPrinter,
                new ScorePrinter< double >( strToWstr(getArgument( SOURCE_FILE )),
                		strToWstr(getArgument( TARGET_FILE )) ) );
        break;

    default :
        std::string desc( "Unknown output format : " );
        desc += c;
        error( desc );
        break;
    }
}

// ------------------------------------------------------------------------ //
void JapaProgram::verbose( const std::string msg )
{
    if( isOption( VERBOSE ) || isOption( VERY_VERBOSE ) )
    {
        ( *m_messagesStream ) << msg << std::endl;
    }
}

// ------------------------------------------------------------------------ //
void JapaProgram::veryVerbose( const std::string msg )
{
    if( isOption( VERY_VERBOSE ) )
    {
        ( *m_messagesStream ) << '\t' << msg << std::endl;
    }
}

}// namespace japa
