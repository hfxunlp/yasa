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

#ifndef JAPA_JAPA_OPTIONS_H
#define JAPA_JAPA_OPTIONS_H

#ifdef HAVE_CONFIG_H
    #include <config.h>
#endif

#include <string>

#include "options.h"

namespace japa
{

/**
 * \french
 * Analyse la ligne de commande du programme <code>japa</code>.
 * \endfrench
 *
 * \english
 * <code>japa</code>'s command line analyzer. 
 * \endenglish
 *
 *
 * @version 1.1
 */
class JapaOptions : public Options
{
public :
   
    /** 
     * \french
     * Aiguillage du rayon du faisceau dans l'espace de recherche. 
     * \endfrench
     *
     * \english
     * Search space beam radius' switch.
     * \endenglish
     *
     * @see BEAM_RADIUS_DEFAULT
     */
    static const char BEAM_RADIUS = 'b';
    
    /** 
     * \french
     * Aiguillage du style de cognate. 
     * \endfrench
     *
     * \english
     * Cognate style's switch.
     * \endenglish
     *
     * @see COGNATE_NONE
     * @see COGNATE_PREFIX
     * @see COGNATE_WORD
     * @see COGNATE_DEFAULT
     */
    static const char COGNATE = 'c';
    
    /** 
     * \french
     * Aiguillage de la fr�quence maximale d'un cognate qui peut �tre un point
     * de passage. 
     * \endfrench
     *
     * \english
     * Cognate maximum frequency to be a passage point switch.
     * \endenglish
     *
     * @see COGNATE_MAX_FREQUENCY_DEFAULT
     */
    static const char COGNATE_MAX_FREQUENCY = 'n';
    
    /** 
     * \french
     * Aiguillage de la longueur minimale d'un cognate. 
     * \endfrench
     *
     * \english
     * Cognate minumum length's switch.
     * \endenglish
     *
     * @see COGNATE_MIN_LENGTH_DEFAULT
     */
    static const char COGNATE_MIN_LENGTH = 'l';
    
    /** 
     * \french
     * Aiguillage de la longueur des pr�fixes des cognates. 
     * \endfrench
     *
     * \english
     * Cognate prefix length's switch.
     * \endenglish
     * 
     * @see COGNATE_PREFIX_LENGTH_DEFAULT
     */
    static const char COGNATE_PREFIX_LENGTH = 'p';
    
    /** 
     * \french
     * Aiguillage de la d�viance maximale lors de la concordance de cognates.
     * \endfrench
     *
     * \english
     * Cognate search space beam radius' switch.
     * \endenglish
     *
     * @see COGNATE_RADIUS_DEFAULT
     */
    static const char COGNATE_RADIUS = 'd';
    
    /** 
     * \french
     * Aiguillage du co�t d'un retour lors de la recherche de cognates. 
     * \endfrench
     *
     * \english
     * Cognate search space return cost's switch.
     * \endenglish
     *
     * @see COGNATE_RETURN_COST_DEFAULT
     */
    static const char COGNATE_RETURN_COST = 'R';

    /** 
     * \french
     * Aiguillage du nombre de retours permis lors de la recherche de cognates. 
     * \endfrench
     *
     * \english
     * Cognate search space maximum allowed return's switch.
     * \endenglish
     *
     * @see COGNATE_RETURN_COUNT_DEFAULT
     */
    static const char COGNATE_RETURN_COUNT = 'r';
    
    /** 
     * \french
     * Aiguillage pour l'ajout d'un alignement. 
     * \endfrench
     *
     * \english
     * Alignment adding switch.
     * \endenglish
     */
    static const char CHURCH_GALE_ALIGNMENT = 'a';
    
    /** 
     * \french
     * Aiguillage du poid de la partie "match" dans le calcul du score du 
     * score de Church and Gale. 
     * \endfrench
     *
     * \english
     * Church and Gale match weight's switch.
     * \endenglish
     *
     * @see CHURCH_GALE_MATCH_DEFAULT
     */
    static const char CHURCH_GALE_MATCH = 'm';
    
    /** 
     * \french
     * Aiguillage du poid de la partie "p�nalit�" dans le calcul du score du
     * score de Church and Gale. 
     * \endfrench
     *
     * \english
     * Church and Gale penalty weight's switch.
     * \endenglish
     *
     * @see CHURCH_GALE_PENALTY_DEFAULT
     */
    static const char CHURCH_GALE_PENALTY = 'M';
    
    /** 
     * \french
     * Aiguillage de la production des caract�res pour le score Church and 
     * Gale.
     * \endfrench
     *
     * \english
     * Church and Gale character production's switch.
     * \endenglish
     *
     * @see CHURCH_GALE_PRODUCTION_DEFAULT
     */
    static const char CHURCH_GALE_PRODUCTION = 'P';
    
    /** 
     * \french
     * Aiguillage du facteur de variance pour le score Church and Gale. 
     * \endfrench
     *
     * \english
     * Church and Gale variance's switch.
     * \endenglish
     *
     * @see CHURCH_GALE_VARIANCE_DEFAULT
     */
    static const char CHURCH_GALE_VARIANCE = 'S';
    
    /** 
     * \french
     * Aiguillage du poid de la partie Church and Gale dans le score Felipe.
     * \endfrench
     *
     * \english
     * Church and Gale score's weight in Felipe's score switch.
     * \endenglish
     *
     * @see FELIPE_CHURCH_GALE_WEIGHT_DEFAULT
     */
    static const char FELIPE_CHURCH_GALE_WEIGHT = 'w';
    
    /** 
     * \french
     * Aiguillage de la correction en mode FullFelipe. 
     * \endfrench
     *
     * \english
     * FullFelipe correction's switch.
     * \endenglish
     *
     * @see FELIPE_CORRECTION_DEFAULT
     */
    static const char FELIPE_CORRECTION = 'F';
    
    /** 
     * \french
     * Aiguillage du mode FullFelipe. 
     * \endfrench
     *
     * \english
     * FullFelipe mode's switch.
     * \endenglish
     *
     * @see FELIPE_MODE_ALL
     * @see FELIPE_MODE_CHURCHGALE
     * @see FELIPE_MODE_DEFAULT
     * @see FELIPE_MODE_NONE
     * @see FELIPE_MODE_SIMARD
     */
    static const char FELIPE_MODE = 'f';
    
    /** 
     * \french
     * Aiguillage du poid du score de Simard dans le score Felipe. 
     * \endfrench
     *
     * \english
     * Simard score's weight in Felipe's score switch.
     * \endenglish
     *
     * @see FELIPE_SIMARD_WEIGHT_DEFAULT
     */
    static const char FELIPE_SIMARD_WEIGHT = 'W';
    
    /** 
     * \french
     * Aiguillage pour afficher l'aide. 
     * \endfrench
     *
     * \english
     * Online help switch.
     * \endenglish
     */
    static const char HELP = 'h';
    
    /**
     * \french
     * Aiguillage pour indiquer le format de compression de l'entr�e.
     * \endfrench
     *
     * \english
     * Input compression switch.
     * \endenglish
     */
    static const char INPUT_COMPRESSION = 'z';
    
    /** 
     * \french
     * Aiguillage du format d'entr�e. 
     * \endfrench
     *
     * \english
     * Input format's switch.
     * \endenglish
     *
     * @see INPUT_FORMAT_ARCADE
     * @see INPUT_FORMAT_CESANA
     * @see INPUT_FORMAT_DEFAULT
     * @see INPUT_FORMAT_OSPL
     * @see INPUT_FORMAT_RALI
     */
    static const char INPUT_FORMAT = 'i';

    /** 
     * \french
     * Aiguillage du format de sortie. 
     * \endfrench
     *
     * \english
     * Output format's switch.
     * \endenglish
     *
     * @see OUTPUT_FORMAT_ARCADE
     * @see OUTPUT_FORMAT_DEFAULT
     * @see OUTPUT_FORMAT_CESALIGN
     * @see OUTPUT_FORMAT_FRIENDLY
     * @see OUTPUT_FORMAT_RALI
     */
    static const char OUTPUT_FORMAT = 'o';

    /** 
     * \french
     * L'aiguillage de la fonction de score. 
     * \endfrench
     *
     * \english
     * Score function's switch.
     * \endenglish
     *
     * @see SCORE_FUNCTION_DEFAULT
     * @see SCORE_FUNCTION_CHURCH_GALE
     * @see SCORE_FUNCTION_FELIPE
     */
    static const char SCORE_FUNCTION = 's';
    
    /** 
     * \french
     * Aiguillage du type d'espace de recherche. 
     * \endfrench
     *
     * \english
     * Search space type's switch. 
     * \endenglish
     *
     * @see SEARCH_SPACE_BEAM
     * @see SEARCH_SPACE_COGNATE
     */
    static const char SEARCH_SPACE = 'e';

    /** 
     * \french
     * Aiguillage de la probabilit� qu'un mot source ait un cognate dans une 
     * phrase cible qui traduit la phrase source.  Utilis�e dans le score de 
     * Simard.
     * \endfrench
     *
     * \english
     * Cognate probability in traduction's switch.
     * \endenglish
     *
     * @see SIMARD_CPT_DEFAULT
     */
    static const char SIMARD_CPT = 't';

    /**
     * \french
     * Aiguillage de la probabilit� qu'un mot source ait un cognate dans une 
     * phrase cible qui ne traduit pas la phrase source.  Utilis�e dans le 
     * score de Simard.
     * \endfrench
     *
     * \english
     * Cognate probability not in traduction's switch.
     * \endenglish
     *
     * @see SIMARD_CPNT_DEFAULT
     */
    static const char SIMARD_CPNT = 'T';

    /** 
     * \french
     * Aiguillage pour l'ajout de lexiques.
     * \endfrench
     *
     * \english
     * Lexicons' switch.
     * \endenglish
     */
    static const char SYNONYM_DICTIONARY = 'L';

    /** 
     * \french
     * Aiguillage de la verbosit� normale. 
     * \endfrench
     *
     * \english
     * Verbosity's switch.
     * \endenglish
     *
     * @see VERBOSE_DEFAULT
     */
    static const char VERBOSE = 'v';

    /** 
     * \french
     * Aiguillage de la grande verbosit�. 
     * \endfrench
     *
     * \english
     * Great verbosity's switch.
     * \endenglish
     *
     * @see VERY_VERBOSE_DEFAULT
     */
    static const char VERY_VERBOSE = 'V';
    
    /** 
     * \french
     * La cha�ne d�finissant le format de la ligne de commande. 
     * \endfrench
     *
     * \english
     * Command line options definition.
     * \endenglish
     */
    static const char OPTSTRING[];


    /** 
     * \french
     * La grosseur par d�faut du rayon de faisceau. 
     * \endfrench
     *
     * \english
     * Default search space beam's radius.
     * \endenglish
     *
     * @see BEAM_RADIUS
     */
    static const size_t BEAM_RADIUS_DEFAULT;
    
    /** 
     * \french
     * Le poid par d�faut de la partie "match". 
     * \endfrench
     *
     * \english
     * Church and Gale match's default weigth.
     * \endenglish
     *
     * @see CHURCH_GALE_MATCH
     */
    static const double CHURCH_GALE_MATCH_DEFAULT;
    
    /** 
     * \french
     * Le poid par d�faut de la partie "p�nalit�". 
     * \endfrench
     *
     * \english
     * Church and Gale penalty's default weight.
     * \endenglish
     *
     * @see CHURCH_GALE_PENALTY
     */
    static const double CHURCH_GALE_PENALTY_DEFAULT;
    
    /** 
     * \french
     * La variance par d�faut pour le score Church and Gale. 
     * \endfrench
     *
     * \english
     * Church and Gale variance's default value.
     * \endenglish
     *
     * @see CHURCH_GALE_VARIANCE
     */
    static const double CHURCH_GALE_VARIANCE_DEFAULT;
    
    /** 
     * \french
     * La production par d�faut pour Church and Gale. 
     * \endfrench
     *
     * \english
     * Church and Gale production's default value.
     * \endenglish
     *
     * @see CHURCH_GALE_PRODUCTION
     */
    static const double CHURCH_GALE_PRODUCTION_DEFAULT;
    
    /** 
     * \french
     * Le type de cognates par d�faut. 
     * \endfrench
     *
     * \english
     * Default cognate type.
     * \endenglish
     *
     * @see COGNATE
     */
    static const char COGNATE_DEFAULT;
    
    /** 
     * \french
     * La longueur minimale par d�faut d'un cognate. 
     * \endfrench
     *
     * \english
     * Default cognates' minimal length.
     * \endenglish
     *
     * @see COGNATE_MIN_LENGTH
     */
    static const size_t COGNATE_MIN_LENGTH_DEFAULT;
    
    /** 
     * \french
     * La fr�quence maximale par d�faut qu'un cognate doit avoir pour �tre
     * un point de passage. 
     * \endfrench
     *
     * \english
     * Default maximum frequency for a cognate to be a passage point.
     * \endenglish
     *
     * @see COGNATE_MAX_FREQUENCY
     */
    static const size_t COGNATE_MAX_FREQUENCY_DEFAULT;
    
    /** 
     * \french
     * Le type de cognates 'aucun cognate'. 
     * \endfrench
     *
     * \english
     * No cognate option.
     * \endenglish
     *
     * @see COGNATE
     */
    static const char COGNATE_NONE = 'n';

    /** 
     * \french
     * Le type de cognates 'pr�fixe'. 
     * \endfrench
     *
     * \english
     * Prefix cognate type option.
     * \endenglish
     *
     * @see COGNATE
     */
    static const char COGNATE_PREFIX = 'p';

    /** 
     * \french
     * La longueur des pr�fixes des cognates par d�faut. 
     * \endfrench
     *
     * \english
     * Default cognate prefix's length.
     * \endenglish
     *
     * @see COGNATE_PREFIX_LENGTH
     */
    static const size_t COGNATE_PREFIX_LENGTH_DEFAULT; 

    /** 
     * \french
     * La d�viance maximale par d�faut d'un cognate. 
     * \endfrench
     *
     * \english
     * Default cognate's variance.
     * \endenglish
     *
     * @see COGNATE_RADIUS
     */
    static const size_t COGNATE_RADIUS_DEFAULT;
    
    /** 
     * \french
     * Le co�t d'un retour par d�faut lors de la recherche de cognates. 
     * \endfrench
     *
     * \english
     * Default return cost's value.
     * \endenglish
     *
     * @see COGNATE_RETURN_COST
     */
    static const double COGNATE_RETURN_COST_DEFAULT;
    
    /** 
     * \french
     * Le nombre de retour par d�faut lors de la recherche de cognates. 
     * \endfrench
     *
     * \english
     * Default number of allowed returns.
     * \endenglish
     *
     * @see COGNATE_RETURN_COUNT
     */
    static const size_t COGNATE_RETURN_COUNT_DEFAULT;
    
    /** 
     * \french
     * Le type de cognates 'Mot complet'. 
     * \endfrench
     *
     * \english
     * Complete word cognate type.
     * \endenglish
     *
     * @see COGNATE
     */
    static const char COGNATE_WORD = 'w';

    /** 
     * \french
     * Le poid par d�faut de la partie Church and Gale dans le score Felipe. 
     * \endfrench
     *
     * \english
     * Default Church and Gale's weight in Felipe score.
     * \endenglish
     *
     * @see FELIPE_CHURCH_GALE_WEIGHT
     */
    static const double FELIPE_CHURCH_GALE_WEIGHT_DEFAULT;
    
    /** 
     * \french
     * Correction FullFelipe par d�faut. 
     * \endfrench
     *
     * \english
     * Default FullFelipe correction's value.
     * \endenglish
     *
     * @see FELIPE_CORRECTION
     */
    static const double FELIPE_CORRECTION_DEFAULT; 
    
    /** 
     * \french
     * Mode FullFelipe complet. 
     * \endfrench
     *
     * \english
     * <code>Complete</code> FullFelipe mode.
     * \endenglish
     *
     * @see FELIPE_MODE
     */
    static const char FELIPE_MODE_ALL = 'a';
    
    /** 
     * \french
     * Mode FullFelipe <code>Church and Gale</code>. 
     * \endfrench
     *
     * \english
     * <code>Church and Gale</code> FullFelipe mode.
     * \endenglish
     *
     * @see FELIPE_MODE
     */
    static const char FELIPE_MODE_CHURCHGALE = 'c';

    /** 
     * \french
     * Mode FullFelipe par d�faut. 
     * \endfrench
     *
     * \english
     * Default FullFelipe mode.
     * \endenglish
     *
     * @see FELIPE_MODE
     */
    static const char FELIPE_MODE_DEFAULT;
    
    /** 
     * \french
     * Mode FullFelipe inactiv�. 
     * \endfrench
     *
     * \english
     * <code>Disabled</code> FullFelipe mode.
     * \endenglish
     *
     * @see FELIPE_MODE 
     */
    static const char FELIPE_MODE_NONE = 'n';
    
    /** 
     * \french
     * Mode FullFelipe <code>Simard</code>.
     * \endfrench
     *
     * \english
     * <code>Simard</code> FullFelipe mode.
     * \endenglish
     *
     * @see FELIPE_MODE 
     */
    static const char FELIPE_MODE_SIMARD = 's';
    
    /** 
     * \french
     * Le poid par d�faut de la partie Simard dans le score Felipe. 
     * \endfrench
     *
     * \english
     * Default Simard score weight's in Felipe score.
     * \endenglish
     *
     * @see FELIPE_SIMARD_WEIGHT 
     */
    static const double FELIPE_SIMARD_WEIGHT_DEFAULT;
   
    /**
     * \french
     * Format de compression par d�faut.
     * \endfrench
     *
     * \english
     * Default compression.
     * \endenglish
     *
     * @see INPUT_COMPRESSION
     * @see INPUT_COMPRESSION_GZIP
     * @see INPUT_COMPRESSION_NONE
     */
    static const char INPUT_COMPRESSION_DEFAULT;

    /**
     * \french
     * Format de compression <code>gzip</code>.
     * \endfrench
     *
     * \english
     * <code>gzip</code> compression.
     * \endenglish
     *
     * @see INPUT_COMPRESSION
     * @see INPUT_COMPRESSION_NONE
     */
    static const char INPUT_COMPRESSION_GZIP = 'g';

    /**
     * \french
     * Aucun format de compression.
     * \endfrench
     *
     * \english
     * No compression.
     * \endenglish
     *
     * @see INPUT_COMPRESSION
     * @see INPUT_COMPRESSION_GZIP
     */
    static const char INPUT_COMPRESSION_NONE = 'n';
    
    /** 
     * \french
     * Le format d'entr�e <code>ARCADE</code>. 
     * \endfrench
     *
     * \english
     * <code>ARCADE</code> input format.
     * \endenglish
     *
     * @see INPUT_FORMAT 
     */
    static const char INPUT_FORMAT_ARCADE = 'a';

    /** 
     * \french
     * Le format d'entr�e <code>CESANA</code>.
     * \endfrench
     *
     * \english
     * <code>CESANA</code> input format.
     * \endenglish
     *
     * @see INPUT_FORMAT 
     */
    static const char INPUT_FORMAT_CESANA = 'c';

    /** 
     * \french
     * Le format d'entr�e par d�faut. 
     * \endfrench
     *
     * \english
     * Default input format.
     * \endenglish
     *
     * @see INPUT_FORMAT 
     */
    static const char INPUT_FORMAT_DEFAULT;

    /** 
     * \french
     * Le format d'entr�e une phrase par ligne. 
     * \endfrench
     *
     * \english
     * One sentence per line input format.
     * \endenglish
     *
     * @see INPUT_FORMAT 
     */
    static const char INPUT_FORMAT_OSPL = 'o';

    /** 
     * \french
     * Le format d'entr�e GLM utilis� par le RALI. 
     * \endfrench
     *
     * \english
     * <code>GLM</code> input format.
     * \endenglish
     *
     * @see INPUT_FORMAT 
     */
    static const char INPUT_FORMAT_RALI = 'r';
    
    /** 
     * \french
     * Le format de sortie <code>ARCADE</code>. 
     * \endfrench
     *
     * \english
     * <code>ARCADE</code> output format.
     * \endenglish
     *
     * @see OUTPUT_FORMAT 
     */
    static const char OUTPUT_FORMAT_ARCADE = 'a';

    /** 
     * \french
     * Format de sortie par d�faut. 
     * \endfrench
     *
     * \english
     * Default output format.
     * \endenglish
     *
     * @see OUTPUT_FORMAT 
     */
    static const char OUTPUT_FORMAT_DEFAULT;

    /** 
     * \french
     * Format de sortie <code>CesAlign</code>. 
     * \endfrench
     *
     * \english
     * <code>CesAlign</code> output format.
     * \endenglish
     *
     * @see OUTPUT_FORMAT 
     */
    static const char OUTPUT_FORMAT_CESALIGN = 'c';
    
    /** 
     * \french
     * Format de sortie gentil pour les humains. 
     * \endfrench
     *
     * \english
     * Human friendly output format.
     * \endenglish
     *
     * @see OUTPUT_FORMAT 
     */
    static const char OUTPUT_FORMAT_FRIENDLY = 'f';

    /** 
     * \french
     * Format de sortie du <code>RALI</code>. 
     * \endfrench
     *
     * \english
     * <code>RALI</code> output format.
     * \endenglish
     *
     * @see OUTPUT_FORMAT 
     */
    static const char OUTPUT_FORMAT_RALI = 'r';
    
    /** 
     * \french
     * Format de sortie du <code>score</code>. 
     * \endfrench
     *
     * \english
     * <code>Score</code> output format.
     * \endenglish
     *
     * @see OUTPUT_FORMAT 
     */
    static const char OUTPUT_FORMAT_SCORE = 's';

    
    /** 
     * \french
     * Indice de l'argument fichier sortie. 
     * \endfrench
     *
     * \english
     * Output file position in command line arguments.
     * \endenglish
     */
    static const char OUTPUT_FILE = 2;
    
    /** 
     * \french
     * Fonction de score par d�faut. 
     * \endfrench
     *
     * \english
     * Default score function.
     * \endenglish
     *
     * @see SCORE_FUNCTION 
     */
    static const char SCORE_FUNCTION_DEFAULT;
    
    /** 
     * \french
     * La fonction de score Gale & Church. 
     * \endfrench
     *
     * \english
     * Church and Gale score function.
     * \endenglish
     *
     * @see SCORE_FUNCTION
     */
    static const char SCORE_FUNCTION_CHURCH_GALE = 'c';
    
    /** 
     * \french
     * La fonction de score Felipe. 
     * \endfrench
     *
     * \english
     * Felipe's score function.
     * \endenglish
     *
     * @see SCORE_FUNCTION 
     */
    static const char SCORE_FUNCTION_FELIPE = 'f';

    /** 
     * \french
     * L'espace de recherche remplis � l'aide d'un faisceau. 
     * \endfrench
     *
     * \english
     * Search space filled with a beam.
     * \endenglish
     *
     * @see SEARCH_SPACE 
     */
    static const char SEARCH_SPACE_BEAM = 'b';
    
    /** 
     * \french
     * L'espace de recherche remplis en tenant compte des cognates. 
     * \endfrench
     *
     * \english
     * Search space filled by an algorithm that uses some cognates as passage 
     * points.
     * \endenglish
     *
     * @see SEARCH_SPACE 
     */
    static const char SEARCH_SPACE_COGNATE = 'c';

    /** 
     * \french
     * Espace de recherche par d�faut. 
     * \endfrench
     *
     * \english
     * Default search space filling algorithm.
     * \endenglish
     *
     * @see SEARCH_SPACE 
     */
    static const char SEARCH_SPACE_DEFAULT;
    
    /** 
     * \french
     * La CPT par d�faut pour le score de Simard. 
     * \endfrench
     *
     * \english
     * Default Simard's Cognate Probability in traduction.
     * \endenglish
     *
     * @see SIMARD_CPT 
     */
    static const double SIMARD_CPT_DEFAULT;

    /** 
     * \french
     * La CPNT par d�faut pour le score de Simard. 
     * \endfrench
     *
     * \english
     * Default Simard's Cognate Probability Not in Traduction.
     * \endenglish
     *
     * @see SIMARD_CPNT 
     */
    static const double SIMARD_CPNT_DEFAULT;
    
    /** 
     * \french
     * L'indice de l'argument texte source. 
     * \endfrench
     *
     * \english
     * Source text's indice in program's argument list.
     * \endenglish
     */
    static const char SOURCE_FILE = 0;

    /** 
     * \french
     * L'indice de l'argument texte cible. 
     * \endfrench
     *
     * \english
     * Target text's indice in program's argument list.
     * \endenglish
     */
    static const char TARGET_FILE = 1;
    
    /** 
     * \french
     * Indique s'il faut �tre verbeux par d�faut. 
     * \endfrench
     *
     * \english
     * Be verbose ( <code>true</code> ) or not ( <code>false</code> ) by 
     * default.
     * \endenglish
     *
     * @see VERBOSE 
     */
    static const bool VERBOSE_DEFAULT;

    /** 
     * \french
     * Indique s'il faut �tre tr�s verbeux par d�faut. 
     * \endfrench
     *
     * \english
     * Be very verbose ( <code>true</code> ) or not ( <code>false</code> ) by 
     * default.

     * \endenglish
     *
     * @see VERY_VERBOSE 
     */
    static const bool VERY_VERBOSE_DEFAULT;
    
    
    /** 
     * \french
     * Le message d'aide en ligne. 
     * \endfrench
     *
     * \english
     * Online help content.
     * \endenglish
     */
    static const std::string ONLINE_HELP;
    
    /** 
     * \french
     * L'usage du program. 
     * \endfrench
     *
     * \english
     * Program's usage.
     * \endenglish
     */
    static const std::string USAGE_HELP;
    
    /** 
     * \french
     * L'aide sur les options. 
     * \endfrench
     *
     * \english
     * Options' description.
     * \endenglish
     */
    static const std::string OPTIONS_HELP;
    
    /**
     * \french 
     * Constructeur.
     * \endfrench
     *
     * \english
     * Constructor.
     * \endenglish
     */
    JapaOptions();

    /**
     * \french
     * Retourne le message d'aide en ligne.
     * 
     * @return Le message d'aide en ligne.
     * \endfrench
     *
     * \english
     * Gets the online help message.
     *
     * @return The online help message.
     * \endenglish
     */
    std::string getOnlineHelp() const;

protected :
    /**
     * \french
     * Initialise les options par d�faut.
     * \endfrench
     *
     * \english
     * Object's initializer.
     * \endenglish
     */
    virtual void initDefault();
    
    /**
     * \french
     * Fonction appel�e lorsqu'une erreur survient.
     *
     * Lance une exception contenant le message d'erreur.
     * 
     * @param description Description de l'erreur.
     * \endfrench
     *
     * \english
     * Throws an exception containing the error message.
     *
     * @param description The error description.
     * \endenglish
     */
    void error( const std::string& description ); 
};


}// namespace japa

#endif
