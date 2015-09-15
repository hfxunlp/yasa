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
 * Ce fichier contient des routines g�n�rales ayant rapport avec les
 * statistiques.
 *
 * @note Certaines routines ont �t� copi�s de code existant.
 * \endfrench
 *
 * \english
 * Contains general functions in link with statistics.
 *
 * @note Some functions where copied from various projects. 
 * \endenglish
 *
 *
 * @version 1.1
 */

#ifndef JAPA_STATISTIC_H
#define JAPA_STATISTIC_H

namespace japa
{


/**
 * \french
 * Calcule la probabilit� qu'une variable al�atoire standard ( moyenne = 0 et 
 * variance = 1 ) <em>z</em> ayant une distribution normale ait une magn�tude
 * de largeur au moins aussi large que <code>magnitude</code>.
 * 
 * @param magnitude Largeur minimum de la magnitude.
 *
 * @return La probabilit� d�crite plus haut.
 * \endfrench
 *
 * \english
 * Compute the probability that a standard random normal variable ( mean = 0,
 * variance = 1 ) <em>z</em> has a magnitude of width as large as
 * <code>magnitude</code>.
 *
 * @param magnitude Magnitude's minimum width.
 *
 * @return The probability as described above.
 * \endenglish
 */
double pnorm( const double magnitude );

/**
 * \french
 * Transforme une variable al�atoire normale en variable standard 
 * ( moyenne = 0, variance = 1 ).
 *
 * @param value La valeur � standardizer.
 * @param mean  La moyenne de la variable al�atoire.
 * @param variance La variance de la variable al�atoire.
 *
 * @return La valeur "standardiz�e".
 * \endfrench
 *
 * \english
 * Transform a normal random variable in a normal standard random variable (
 * mean = 0, variance = 1 ).
 *
 * @param value The value to standardize.
 * @param mean The mean of the random variable.
 * @param variance The variance of the random variable. 
 *
 * @return The standardized value.
 * \endenglish
 */
double standardize( const double value, const double mean, 
                    const double variance );

/**
 * \french
 * Calcule la moyenne de deux valeurs.
 *
 * @param value1 La premi�re valeur.
 * @param value2 La deuxi�me valeur.
 *
 * @return La moyenne.
 * \endfrench
 *
 * \english
 * Compute the average of two values.
 *
 * @param value1 The first value.
 * @param value2 The second value.
 *
 * @return The average. 
 * \endenglish
 */
double average( const double value1, const double value2 );

}// namespace japa

#endif
