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

#include <cmath>

#include "statistic.h"

namespace japa
{

// ------------------------------------------------------------------------ //
double pnorm( const double magnitude )
{		
    /*
     * Source : Prise du document "A Program for Aligning in Bilingual Corpora" 
     *          par : William A. Gale et Kenneth W. Church.
     */
    double t;
    double pd;
    
    t = 1 / (1 + 0.2316419 * magnitude);

    pd = 1 - 0.3989423 *
         exp( -magnitude * magnitude / 2 ) *
         ( ( ( ( 1.330274429 * t - 1.821255978 ) * t + 1.781477937 ) * 
             t - 0.356563782 ) * t + 0.319381530 ) * t;

    return pd;
}

// ------------------------------------------------------------------------ //
double standardize( const double value, const double mean, 
                    const double variance )
{
    return value / sqrt( variance * mean ); 
}

// ------------------------------------------------------------------------ //
double average( const double value1, const double value2 )
{
    return ( value1 + value2 ) / 2;
}

}// namespace japa
