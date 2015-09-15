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

#include "cognatessvalidator.h"
#include "cognatevalidator.h"
#include "churchgalescore.h"
#include "constantbeammarker.h"
#include "felipescore.h"
#include "japaexception.h"
#include "japaoptions.h"
#include "prefixcognatefinder.h"
#include "toolbox.h"
#include "wordscorefunction.h"
#include "wordssf.h"

namespace japa
{

// ------------------------------------------------------------------------ //
// Initialisation des constantes

const char JapaOptions::OPTSTRING[] =   { 
                                            BEAM_RADIUS, ':', 
                                            CHURCH_GALE_ALIGNMENT, ':',
                                            CHURCH_GALE_MATCH, ':',
                                            CHURCH_GALE_PENALTY, ':',
                                            CHURCH_GALE_PRODUCTION, ':',
                                            CHURCH_GALE_VARIANCE, ':',
                                            COGNATE, ':',
                                            COGNATE_MAX_FREQUENCY, ':',
                                            COGNATE_MIN_LENGTH, ':',
                                            COGNATE_PREFIX_LENGTH, ':',
                                            COGNATE_RADIUS, ':',
                                            COGNATE_RETURN_COUNT, ':',
                                            COGNATE_RETURN_COST, ':',
                                            FELIPE_CHURCH_GALE_WEIGHT, ':',
                                            FELIPE_CORRECTION, ':',
                                            FELIPE_MODE, ':',
                                            FELIPE_SIMARD_WEIGHT, ':',
                                            HELP,
                                            INPUT_COMPRESSION, ':',
                                            INPUT_FORMAT, ':',
                                            OUTPUT_FORMAT, ':', 
                                            SCORE_FUNCTION, ':',
                                            SEARCH_SPACE, ':',
                                            SIMARD_CPT, ':',
                                            SIMARD_CPNT, ':',
                                            SYNONYM_DICTIONARY, ':',
                                            VERBOSE,
                                            VERY_VERBOSE,
                                            '\0'
                                        };

const size_t JapaOptions::BEAM_RADIUS_DEFAULT           = ConstantBeamMarker::DEFAULT_RADIUS;
const double JapaOptions::CHURCH_GALE_MATCH_DEFAULT     = ChurchGaleScore::DEFAULT_MATCH_WEIGHT;
const double JapaOptions::CHURCH_GALE_PENALTY_DEFAULT   = ChurchGaleScore::DEFAULT_PENALTY_WEIGHT;
const double JapaOptions::CHURCH_GALE_PRODUCTION_DEFAULT= ChurchGaleScore::DEFAULT_PRODUCTION;
const double JapaOptions::CHURCH_GALE_VARIANCE_DEFAULT  = ChurchGaleScore::DEFAULT_VARIANCE;
const char   JapaOptions::COGNATE_DEFAULT               = COGNATE_PREFIX;
const size_t JapaOptions::COGNATE_MAX_FREQUENCY_DEFAULT = CognateSSValidator::DEFAULT_MAX_FREQUENCY;
const size_t JapaOptions::COGNATE_MIN_LENGTH_DEFAULT    = CognateValidator::DEFAULT_MIN_LENGTH;
const size_t JapaOptions::COGNATE_PREFIX_LENGTH_DEFAULT = PrefixCognateFinder::DEFAULT_PREFIX_LENGTH;
const size_t JapaOptions::COGNATE_RADIUS_DEFAULT        = WordSSF::DEFAULT_RADIUS;
const double JapaOptions::COGNATE_RETURN_COST_DEFAULT   = WordScoreFunction::DEFAULT_RETURN_COST;
const size_t JapaOptions::COGNATE_RETURN_COUNT_DEFAULT  = WordScoreFunction::DEFAULT_RETURN_COUNT;
const double JapaOptions::FELIPE_CHURCH_GALE_WEIGHT_DEFAULT = FelipeScore::DEFAULT_CHURCH_GALE_WEIGHT;
const double JapaOptions::FELIPE_CORRECTION_DEFAULT     = FelipeScore::DEFAULT_CORRECTION;
const char   JapaOptions::FELIPE_MODE_DEFAULT           = FELIPE_MODE_ALL;
const double JapaOptions::FELIPE_SIMARD_WEIGHT_DEFAULT  = FelipeScore::DEFAULT_SIMARD_WEIGHT;
const char   JapaOptions::INPUT_COMPRESSION_DEFAULT     = INPUT_COMPRESSION_NONE;
const char   JapaOptions::INPUT_FORMAT_DEFAULT          = INPUT_FORMAT_RALI;
const char   JapaOptions::OUTPUT_FORMAT_DEFAULT         = OUTPUT_FORMAT_RALI;
const char   JapaOptions::SCORE_FUNCTION_DEFAULT        = SCORE_FUNCTION_FELIPE;
const char   JapaOptions::SEARCH_SPACE_DEFAULT          = SEARCH_SPACE_COGNATE;
const double JapaOptions::SIMARD_CPT_DEFAULT            = FelipeScore::DEFAULT_CPT;
const double JapaOptions::SIMARD_CPNT_DEFAULT           = FelipeScore::DEFAULT_CPNT;
const bool   JapaOptions::VERBOSE_DEFAULT               = false;
const bool   JapaOptions::VERY_VERBOSE_DEFAULT          = false;

const std::string JapaOptions::USAGE_HELP = 
        "Usage : yasa [options] source_file target_file [output_file]";

const std::string JapaOptions::OPTIONS_HELP = std::string( "" ) +

"If the output file is omitted, the alignment is redirected to the standard\n" +
"output and verbose messages are redirected to the standard error output.\n\n " +

"Options \n\n" +

"Input Options \n\n" +

"-" + INPUT_FORMAT + 
" s    Set the format of the input. ( Default = " + INPUT_FORMAT_DEFAULT + " )\n" +
"          " + INPUT_FORMAT_ARCADE + "  Arcade input format\n" +
"          " + INPUT_FORMAT_CESANA + "  Cesana input format\n" +
"          " + INPUT_FORMAT_OSPL   + "  One sentence per line input format\n" +
"          " + INPUT_FORMAT_RALI   + "  RALI( GLM ) input format\n" +

"-" + INPUT_COMPRESSION +
" s    Set the input compression filter. ( Default = " + INPUT_COMPRESSION_DEFAULT + ")\n" +
"          " + INPUT_COMPRESSION_GZIP + "  GZIP compression filter.\n" +
"          " + INPUT_COMPRESSION_NONE + "  No compression.\n" +

"\n" +
"Cognate Options \n\n"

"-" + COGNATE +
" s    Set the cognate type. ( Default = " + COGNATE_DEFAULT + " )\n" +
"          " + COGNATE_NONE   + "  No cognate\n" +
"          " + COGNATE_PREFIX + "  Simard type cognate\n" +
"          " + COGNATE_WORD   + "  Only identical words are cognates\n" +

"-" + COGNATE_MIN_LENGTH +
" n    Set the minimum length of a cognate. ( Default = " +
       toString( COGNATE_MIN_LENGTH_DEFAULT ) + " )\n" +

"-" + COGNATE_MAX_FREQUENCY +
" n    Set the maximum frequency of a cognate. ( Default = " +
       toString( COGNATE_MAX_FREQUENCY_DEFAULT ) + " )\n" +

"-" + COGNATE_PREFIX_LENGTH +
" n    Set the length of the prefix for Simard type cognates. ( Default = " + 
       toString( COGNATE_PREFIX_LENGTH_DEFAULT ) + " )\n" +

"-" + SYNONYM_DICTIONARY +
" s    Specify a file containing a synonym dictionary.  The format of a\n" + 
"        entry in the synonym dictionary is as follow :\n"
"        source_word target_word\n"
"        Use the option for each dictionary\n" +

"\n" +
"Search Space Options \n\n" +

"-" + SEARCH_SPACE +
" s    Set the search space filling algorithm. ( Default = " + SEARCH_SPACE_DEFAULT + " )\n" +
"          " + SEARCH_SPACE_BEAM    + "  Use a diagonal beam\n" +
"          " + SEARCH_SPACE_COGNATE + "  Align cognates to find passage points\n" +

"-" + BEAM_RADIUS + 
" n    Set the radius of the beam sent between passage points. ( Default = " + 
       toString( BEAM_RADIUS_DEFAULT ) + " )\n" +

"-" + COGNATE_RADIUS +
" n    Set the maximum deviance of a cognate, " + toString( WordSSF::INFINITE_RADIUS ) + 
" being infinite deviance.\n" + 
"        ( Default = " + toString( COGNATE_RADIUS_DEFAULT ) + " )\n" +

       
"-" + COGNATE_RETURN_COUNT +
" n    Number of return allowed while aligning cognates. ( Default = " + 
       toString( COGNATE_RETURN_COUNT_DEFAULT ) + " )\n" +

"-" + COGNATE_RETURN_COST +
" r    Cost of a return while aligning cognates. ( Default = " +
       toString( COGNATE_RETURN_COST_DEFAULT ) + " )\n" +
       
"\n" +
"Resolution Option \n\n" +

"-" + SCORE_FUNCTION +
" s    Set the score function in dynamic table. ( Default = " + 
       SCORE_FUNCTION_DEFAULT + " )\n" +
"          " + SCORE_FUNCTION_FELIPE + " Felipe score function\n" +
"          " + SCORE_FUNCTION_CHURCH_GALE + " Gale and Church score function\n" +

"-" + CHURCH_GALE_ALIGNMENT +
" s    Add a possible alignment.\n" + 
"        An alignment is specified in the following way : \n" +
"        <Source sentences count>-<Target sentences count>-<Probability>\n" +
"        Default alignments : \n" +
"          0-1-" + toString( ChurchGaleScore::DEFAULT_PROB_01 ) + "\n" +
"          1-0-" + toString( ChurchGaleScore::DEFAULT_PROB_10 ) + "\n" +
"          1-1-" + toString( ChurchGaleScore::DEFAULT_PROB_11 ) + "\n" +
"          1-2-" + toString( ChurchGaleScore::DEFAULT_PROB_12 ) + "\n" +
"          2-1-" + toString( ChurchGaleScore::DEFAULT_PROB_21 ) + "\n" +
"          2-2-" + toString( ChurchGaleScore::DEFAULT_PROB_22 ) + "\n" +


"-" + CHURCH_GALE_VARIANCE +
" r    The variance of the number of characters in sentences. ( Default : " +
       toString( CHURCH_GALE_VARIANCE_DEFAULT ) + " )\n" +

"-" + CHURCH_GALE_PRODUCTION +
" r    Average production of target characters per source character.\n" +
"        ( Default = " +
       toString( CHURCH_GALE_PRODUCTION_DEFAULT ) + " )\n" +

"-" + CHURCH_GALE_MATCH +
" r    Weight of the match in Churh and Gale score. ( Default = " + 
       toString( CHURCH_GALE_MATCH_DEFAULT ) + " )\n" +

"-" + CHURCH_GALE_PENALTY +
" r    Weight of the penalty in Church and Gale score. ( Default = " +
       toString( CHURCH_GALE_PENALTY_DEFAULT ) + " )\n" +
       
"-" + FELIPE_CHURCH_GALE_WEIGHT +
" r    Weigth of the Church and Gale score in Felipe score. ( Default = " +
       toString( FELIPE_CHURCH_GALE_WEIGHT_DEFAULT ) + " )\n" + 

"-" + FELIPE_SIMARD_WEIGHT +
" r    Weight of the Simard score in Felipe score. ( Default = " +
       toString( FELIPE_SIMARD_WEIGHT_DEFAULT ) + " )\n" + 

"-" + SIMARD_CPT +
" r    Cognate probability in traduction. ( Default = " +
       toString( SIMARD_CPT_DEFAULT ) + " )\n" +

"-" + SIMARD_CPNT +
" r    Cognate probability not in traduction. ( Default = " +
       toString( SIMARD_CPNT_DEFAULT ) + " )\n" +

"-" + FELIPE_MODE +
" s    FullFelipe mode or deletion and insertion penalty type. ( Default = " +
       toString( FELIPE_MODE_DEFAULT ) + " )\n" +
"          " + FELIPE_MODE_NONE + " FullFelipe disabled.\n" +
"          " + FELIPE_MODE_CHURCHGALE + " Correct Church and Gale score.\n" +
"          " + FELIPE_MODE_SIMARD + " Correct Simard score.\n" +
"          " + FELIPE_MODE_ALL + " Correct the whole score.\n" +

"-" + FELIPE_CORRECTION +
" r    FullFelipe correction. A number by which a part of the score will be\n" + 
"        divided, so must be different of 0. ( Default = " + 
       toString( FELIPE_CORRECTION_DEFAULT ) + " )\n" +

"\n" +
"Output Options \n\n" +

"-" + OUTPUT_FORMAT +
" s    Set the format of the output. ( Default = " + 
       OUTPUT_FORMAT_DEFAULT + " )\n" +
"          " + OUTPUT_FORMAT_ARCADE   + " Arcade output format\n" +
"          " + OUTPUT_FORMAT_CESALIGN + " CesAlign output format\n" +
"          " + OUTPUT_FORMAT_FRIENDLY + " Human friendly output\n" +
"          " + OUTPUT_FORMAT_RALI     + " RALI output format\n" +
"          " + OUTPUT_FORMAT_SCORE    + " prints the final alignment score\n" +
"\n" +
"Other Options \n\n" +

"-" + HELP + "      Display this help message.\n"

"-" + VERBOSE + "      Be verbose.\n" +

"-" + VERY_VERBOSE + "      Be very verbose.\n";

const std::string JapaOptions::ONLINE_HELP = USAGE_HELP + "\n\n" + OPTIONS_HELP;



// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //
JapaOptions::JapaOptions() : Options( OPTSTRING, false )
{
    initDefault();
}

// ------------------------------------------------------------------------ //
void JapaOptions::initDefault()
{
    setOption( COGNATE, COGNATE_DEFAULT );
    setOption( INPUT_FORMAT, INPUT_FORMAT_DEFAULT );
    setOption( INPUT_COMPRESSION, INPUT_COMPRESSION_DEFAULT );
    setOption( OUTPUT_FORMAT, OUTPUT_FORMAT_DEFAULT );
    setOption( SCORE_FUNCTION, SCORE_FUNCTION_DEFAULT );
    setOption( SEARCH_SPACE, SEARCH_SPACE_DEFAULT );

    if( VERBOSE_DEFAULT )
    {
        setOption( VERBOSE, '1' );
    }

    if( VERY_VERBOSE_DEFAULT )
    {
        setOption( VERY_VERBOSE, '1' );
    }

    setOption( COGNATE_RADIUS, toString( COGNATE_RADIUS_DEFAULT ) );
    setOption( COGNATE_RETURN_COST, toString( COGNATE_RETURN_COST_DEFAULT ) );
    setOption( COGNATE_RETURN_COUNT, toString( COGNATE_RETURN_COUNT_DEFAULT ) ); 
    setOption( BEAM_RADIUS, toString( BEAM_RADIUS_DEFAULT ) );
    setOption( COGNATE_PREFIX_LENGTH, 
               toString( COGNATE_PREFIX_LENGTH_DEFAULT ) );

    setOption( COGNATE_MAX_FREQUENCY, 
               toString( COGNATE_MAX_FREQUENCY_DEFAULT ) );

    setOption( COGNATE_MIN_LENGTH, toString( COGNATE_MIN_LENGTH_DEFAULT ) );
    
    setOption( CHURCH_GALE_MATCH, toString( CHURCH_GALE_MATCH_DEFAULT ) );
    setOption( CHURCH_GALE_PENALTY, toString( CHURCH_GALE_PENALTY_DEFAULT ) );
    setOption( CHURCH_GALE_PRODUCTION, 
            toString( CHURCH_GALE_PRODUCTION_DEFAULT ) );
    setOption( CHURCH_GALE_VARIANCE, toString( CHURCH_GALE_VARIANCE_DEFAULT ) );
    
    setOption( FELIPE_CHURCH_GALE_WEIGHT, 
            toString( FELIPE_CHURCH_GALE_WEIGHT_DEFAULT ) );
    setOption( FELIPE_SIMARD_WEIGHT, toString( FELIPE_SIMARD_WEIGHT_DEFAULT ) );
    setOption( FELIPE_MODE, FELIPE_MODE_DEFAULT );
    setOption( FELIPE_CORRECTION, toString( FELIPE_CORRECTION_DEFAULT ) );
    
    setOption( SIMARD_CPT, toString( SIMARD_CPT_DEFAULT ) );
    setOption( SIMARD_CPNT, toString( SIMARD_CPNT_DEFAULT ) );
}

// ------------------------------------------------------------------------ //
void JapaOptions::error( const std::string& description )
{
    throw Exception( description );
}

// ------------------------------------------------------------------------ //
std::string JapaOptions::getOnlineHelp() const
{
    return ONLINE_HELP;    
}

}// namespace japa
