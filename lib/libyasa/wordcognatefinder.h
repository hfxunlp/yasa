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

#ifndef WORD_COGNATE_FINDER_H
#define WORD_COGNATE_FINDER_H

#include "cognatefinder.h"
#include "validator.h"

namespace japa
{

/**
 * \french
 * Un foncteur qui consid�re les cognates comme les mots exactement identiques.
 * \endfrench
 *
 * \english
 * A fonctor that consider for cognates only identical words. 
 * \endenglish
 *
 *
 * @version 1.1
 */
class WordCognateFinder : public CognateFinder
{
public :

    void operator()( Text& source, Text& target, 
                     Validator< WordInfo >& validator );
};

}// namespace japa

#endif
