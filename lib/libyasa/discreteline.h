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


#ifndef JAPA_DISCRETELINE_H
#define JAPA_DISCRETELINE_H


namespace japa
{

/**
 * \french
 * Interpolle les points sur une ligne dans un espace discret.
 *
 * Le syst�me de coordonn�e utilis� est entier, la ligne est donc une 
 * approximation de la vraie ligne dans un syst�me continue.  Cette classe
 * peut �tre utile pour par example, dessiner une ligne sur un �cran de
 * pixels ou bien trouver une approximation d'une diagonale dans une matrice
 * qui n'est pas n�cessairement carr�e.
 *
 * La classe est un it�rateur sur la ligne, donc les points sont donn�es dans
 * l'ordre en commen�ant par le premier bout et en finissant par le deuxi�me.
 *
 * Si le premier et le deuxi�me point sont �gaux, aucune ligne n'existe, donc
 * la ligne est vide.
 * 
 * @note Lorsque l'objet vient d'�tre construit, <code>next</code> doit �tre 
 *       appel� avant qu'il pointe sur le premier point.
 *
 * \endfrench
 *
 * \english
 * Interpollate a line in a discrete environment. 
 *
 * Because the coordinate system uses integer values, the interpollation is
 * only an approximation of the real line.  This class may be used, for
 * example, to draw a line on a screen or to find the diagonal of a matrix.
 *
 * This class creates iterators on the points of the line.
 *
 * If the starting and ending points are the same, no line exists between
 * them, so no point are given.
 *
 * @note When the object is created, <code>next</code> must be called once
 *       before accessing the first point of the line.
 * \endenglish
 * 
 *
 * @version 1.1
 */
class DiscreteLine
{
    // 
    // L'algorithme utilis� ici est celui du point milieu de Bresenham.  Un
    // algorithme classique en infographie.
    // 
    
public :
    /**
     * \french
     * Constructeur
     *
     * @param x0 La coordonn�e en x du premier bout de la ligne.
     * @param y0 La coordonn�e en y du premier bout de la ligne.
     * @param x1 La coordonn�e en x du deuxi�me bout de la ligne.
     * @param y1 La coordonn�e en y du deuxi�me bout de la ligne.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param x0 The first point x coordinate.
     * @param y0 The first point y coordinate.
     * @param x1 The second point x coordinate.
     * @param y1 The second point y coordinate.
     * \endenglish
     */
    DiscreteLine( const int x0, const int y0, const int x1, const int y1 );

    /**
     * \french
     * Destructeur
     * \endfrench
     *
     * \english
     * Destructor.
     * \endenglish
     */
    virtual ~DiscreteLine();
    
    /**
     * \french
     * V�rifie s'il reste des points de la ligne � �num�rer.
     * 
     * @return <code>false</code> s'il n'y a plus de point � �num�rer.
     * \endfrench
     *
     * \english
     * Checks if there's still points on the line to enumerate.
     *
     * @return <code>false</code> when there's no more points.
     * \endenglish
     */
    bool hasNext() const;
    
    /**
     * \french
     * Avance sur la ligne.
     * \endfrench
     *
     * \english
     * Fetch the next point.
     * \endenglish
     */
    void next();
    
    /**
     * \french
     * Retourne la coordonn�e en x du point courant.
     * 
     * @return La coordonn�e en x.
     * \endfrench
     *
     * \english
     * Gets the x coordinate of the current point.
     *
     * @return x coordinate.
     * \endenglish
     */
    int x() const;

    /**
     * \french
     * Retourne la coordonn�e en y du point courant.
     * 
     * @return La coordonn�e en y.
     * \endfrench
     *
     * \english
     * Gets the y coordinate of the current point.
     *
     * @return y coordinate.
     * \endenglish
     */
    int y() const;

private :

    /**
     * \french
     * Initialise les variables utilis�es dans le calcul.
     *
     * @param x0 La coordonn�e en x du premier bout de la ligne.
     * @param y0 La coordonn�e en y du premier bout de la ligne.
     * @param x1 La coordonn�e en x du deuxi�me bout de la ligne.
     * @param y1 La coordonn�e en y du deuxi�me bout de la ligne.
     * \endfrench
     *
     * \english
     * Initialize the object.
     *
     * @param x0 The first point x coordinate.
     * @param y0 The first point y coordinate.
     * @param x1 The second point x coordinate.
     * @param y1 The second point y coordinate.
     * \endenglish
     */
    void init( const int x0, const int y0, const int x1, const int y1 );
    
    /** 
     * \french
     * La coordonn�e courante en x.
     * \endfrench
     *
     * \english
     * The current x coordinate.
     * \endenglish
     */
    int m_currentX;

    /** 
     * \french
     * La coordonn�e courante en y.
     * \endfrench
     *
     * \english
     * The current y coordinate.
     * \endenglish
     */
    int m_currentY;

    /** 
     * \french
     * Variable de d�cision .
     * \endfrench
     *
     * \english
     * Decision variable.
     * \endenglish
     */
    int m_decision;

    /** 
     * \french
     * La variable ind�pendante 
     * \endfrench
     *
     * \english
     * The independent variable.
     * \endenglish
     */
    int* m_independant;

    /** 
     * \french
     * La variable d�pendante.
     * \endfrench
     *
     * \english
     * The dependent variable.
     * \endenglish
     */
    int* m_dependant;
    
    /** 
     * \french
     * Incr�ment de la variable ind�pendante 
     * \endfrench
     *
     * \english
     * independent variable's increment.
     * \endenglish
     */
    int m_incrIndependent;

    /** 
     * \french
     * Incr�ment de la variable d�pendante.
     * \endfrench
     *
     * \english
     * Dependent variable's increment.
     * \endenglish
     */
    int m_incrDependent;
    
    /** 
     * \french
     * Incr�ment de la variable de d�cision vers l'est.
     * \endfrench
     *
     * \english
     * East increment of the decision variable.
     * \endenglish
     */
    int m_incrE;

    /** 
     * \french
     * Incr�ment de la variable de d�cision vers le nord-est.
     * \endfrench
     *
     * \english
     * North-East increment of the decision variable.
     * \endenglish
     */
    int m_incrNE;

    /** 
     * \french
     * Coordonn�e maximum de la variable ind�pendante.
     * \endfrench
     *
     * \english
     * Maximum coordinate of the independent variable.
     * \endenglish
     */
    int m_maxIndependent;

    /** 
     * \french
     * Est � <code>true</code> si c'est le premier appel � <code>next</code> 
     * \endfrench
     *
     * \english
     * Is set to <code>true</code> if next has never been called before.
     * \endenglish
     */
    bool m_first;
};

}// namespace japa

#endif
