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

#ifndef JAPA_POINT_2D_H
#define JAPA_POINT_2D_H

namespace japa
{

/**
 * \french
 * Repr�sentation d'un point dans un espace bidimensionnel.
 *
 * @param T Le type de donn�e des coordonn�es.
 * \endfrench
 *
 * \english
 * A point represention in a bi-dimensional space.
 *
 * @param T coordinate's data type.
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class Point2D
{
public :
    /**
     * \french
     * Constructeur par d�faut.
     * \endfrench
     *
     * \english
     * Default constructor. 
     * \endenglish
     */
    Point2D();
    
    /**
     * \french
     * Constructeur.
     *
     * @param x La coordonn�e en x du point.
     * @param y La coordonn�e en y du point.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @param x Point's x coordinate.
     * @param y Point's y coordinate. 
     * \endenglish
     */
    Point2D( const T& x, const T& y );
       
    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~Point2D();

    /**
     * \french
     * Ajuste la valeur du point.
     *
     * @param x Coordonn�e en x du point.
     * @param y Coordonn�e en y du point.
     * \endfrench
     *
     * \english
     * Sets the point's position.
     *
     * @param x Point's x coordinate.
     * @param y Point's y coordinate. 
     * \endenglish
     */
    void set( const T& x, const T& y );

    /**
     * \french
     * Retourne la coordonn�e en x du point.
     * 
     * @return La coordonn�e en x du point.
     * \endfrench
     *
     * \english
     * Gets the point's x coordinate.
     *
     * @return The point's x coordinate.
     * \endenglish
     */
    T x() const;

    /**
     * \french
     * Retourne la coordonn�e en y du point.
     * 
     * @return La coordonn�e en y du point.
     * \endfrench
     *
     * \english
     * Gets the point's y coordinate.
     *
     * @return The point's y coordinate.
     * \endenglish
     */
    T y() const;

    /**
     * \french
     * V�rifie l'�galit�e de deux points.
     *
     * @note Le type g�n�rique doit supporter l'op�ration <code>==</code>.
     * 
     * @param point Le point avec lequel comparer le point courant.
     * 
     * @return <code>true</code> si les deux points sont �gaux.
     * \endfrench
     *
     * \english
     * Checks for equality between two points.
     *
     * @note <code>==</code> oprator must be supported by <code>T</code>.
     *
     * @param point The point that will be compared with the current point.
     *
     * @return <code>true</code> if the two points are equal.
     * \endenglish
     */
    bool operator==( const Point2D& point ) const;
    
    /**
     * \french
     * V�rifie l'in�galit�e de deux points.
     *
     * @note Le type g�n�rique doit supporter l'op�ration <code>!=</code>.
     * 
     * @param point Le point avec lequel comparer le point courant.
     * 
     * @return <code>true</code> si les deux points sont diff�rents.
     * \endfrench
     *
     * \english
     * Checks for inequality between two points.
     *
     * @note <code>!=</code> oprator must be supported by <code>T</code>.
     * 
     * @param point The point that will be compared with the current point.
     *
     * @return <code>true</code> if the two points are not equals. 
     * \endenglish
     */
    bool operator!=( const Point2D& point ) const;

    
private :
    /** 
     * \french
     * La coordonn�e en x du point 
     * \endfrench
     *
     * \english
     * Point's x coordinate. 
     * \endenglish
     */
    T m_x;

    /** 
     * \french
     * La coordonn�e en y du point 
     * \endfrench
     *
     * \english
     * Point's y coordinate. 
     * \endenglish
     */
    T m_y;
};

// ------------------------------------------------------------------------ //
template< class T >
Point2D< T >::Point2D()
{}

// ------------------------------------------------------------------------ //
template< class T >
Point2D< T >::Point2D( const T& x, const T& y ) : m_x( x ), m_y( y )
{
}

// ------------------------------------------------------------------------ //
template< class T >
Point2D< T >::~Point2D()
{}

// ------------------------------------------------------------------------ //
template< class T >
void Point2D< T >::set( const T& x, const T& y )
{
    m_x = x;
    m_y = y;
}

// ------------------------------------------------------------------------ //
template< class T >
T Point2D< T >::x() const
{
    return m_x;
}

// ------------------------------------------------------------------------ //
template< class T >
T Point2D< T >::y() const
{
    return m_y;
}

// ------------------------------------------------------------------------ //
template< class T >
bool Point2D< T >::operator==( const Point2D& point ) const
{
    return x() == point.x() && y() == point.y();
}

// ------------------------------------------------------------------------ //
template< class T >
bool Point2D< T >::operator!=( const Point2D& point ) const
{
    return x() != point.x() || y() != point.y();
}

}// namespace japa

#endif
