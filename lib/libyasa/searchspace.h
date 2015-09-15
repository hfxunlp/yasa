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

#ifndef JAPA_SEARCH_SPACE_H
#define JAPA_SEARCH_SPACE_H

#include <memory>


namespace japa
{

class SearchSpaceIterator;

/**
 * \french
 * Un espace de recherche pour limiter le nombre de solutions possibles d'un 
 * probl�me.
 * 
 * Cette classe est une interface pour un espace de recherche bidimensionnel.
 * \endfrench
 *
 * \english
 * A search space that helps to generate an optimal solution.
 * 
 * This class is an interface for a bidimensional search space. 
 * \endenglish
 * 
 *
 * @version 1.1
 */
class SearchSpace
{
public :
    class Iterator; 
        
    /**
     * \french
     * Ajoute une possibilit� dans l'espace de recherche.
     *
     * @param x La coordonn�e en x de la possibilit�.
     * @param y La coordonn�e en y de la possibilit�.
     *
     * @return <code>true</code> si la possibilit� a pu �tre ajout�e,
     *         <code>false</code> sinon.
     * \endfrench
     *
     * \english
     * Add a possibility in the search space.
     *
     * @param x The possibility's x coordinate.
     * @param y The possibility's y coordinate.
     *
     * @return <code>true</code> if the possibility has been added, 
     *         <code>false</code> otherwise. 
     * \endenglish
     */
    virtual bool addPossibility( const int x, const int y ) = 0;

    /**
     * \french
     * V�rifie si une possibilit� existe.
     * 
     * @param x La coordonn�e en x de la possibilit�.
     * @param y La coordonn�e en y de la possibilit�.
     *
     * @return <code>true</code> si la possibilit� existe, 
     *         <code>false</code> sinon.
     * \endfrench
     *
     * \english
     * Checks for the existence of a possibility.
     *
     * @param x The possibility's x coordinate.
     * @param y The possibility's y coordinate.
     * 
     * @return <code>true</code> if the possibility exists,
     *         <code>false</code> otherwise. 
     * \endenglish
     */
    virtual bool isPossibility( const int x, const int y ) const = 0;

    /**
     * \french
     * Retourne un it�rateur sur l'espace de recherche.
     * 
     * @return Un it�rateur sur les solutions de tous l'espace.
     * \endfrench
     *
     * \english
     * Gets an iterator on the possibilities of the search space.
     *
     * @return The iterator.
     * \endenglish
     */
    virtual SearchSpace::Iterator getIterator() const = 0;

    /**
     * \french
     * Retourne un it�rateur sur les possibilit�s de l'espace de recherche
     * dont la coordonn�e en y est fix�e.
     * 
     * @param y La coordonn�e en y fix�e.
     *
     * @return Un it�rateur sur les possibilit�s de l'espace.
     * \endfrench
     *
     * \english
     * Gets an iterator on the search space's possibilities for a certain y
     * coordinate.
     *
     * @param y The fixed y coordinate
     *
     * @return An iterator on the search space's possibilities.
     * \endenglish
     */
    virtual SearchSpace::Iterator getIterator( const int y ) const = 0;
    
    /**
     * \french
     * Retourne la coordonn�e en x de la borne inf�rieure de l'espace de
     * recherche.
     * 
     * @return La coordonn�e en x.
     * \endfrench
     *
     * \english
     * Gets the x coordinate of the search space's lower bound.
     *
     * @return The x coordinate.
     * \endenglish
     */
    virtual int getLowerBoundX() const = 0;

    /**
     * \french
     * Retourne la coordonn�e en y de la borne inf�rieure de l'espace de
     * recherche.
     * 
     * @return La coordonn�e en y.
     * \endfrench
     *
     * \english
     * Gets the y coordinate of the search space's lower bound.
     *
     * @return The y coordinate.
     * \endenglish
     */
    virtual int getLowerBoundY() const = 0;

    /**
     * \french
     * Retourne la coordonn�e en x de la borne sup�rieure de l'espace de
     * recherche.
     * 
     * @return La coordonn�e en x.
     * \endfrench
     *
     * \english
     * Gets the x coordinate of the search space's upper bound.
     *
     * @return The x coordinate.
     * \endenglish
     */
    virtual int getUpperBoundX() const = 0;

    /**
     * \french
     * Retourne la coordonn�e en y de la borne sup�rieure de l'espace de
     * recherche.
     * 
     * @return La coordonn�e en y.
     * \endfrench
     *
     * \english
     * Gets the y coordinate of the search space's upper bound.
     *
     * @return The y coordinate.
     * \endenglish
     */
    virtual int getUpperBoundY() const = 0;
    
    /**
     * \french
     * Permet de parcourir les possibilit�s de l'espace de recherche.
     *
     * Cette classe n'est qu'une enveloppe de <code>SearchSpaceIterator</code>.
     * 
     * @note Le constructeur prend en param�tre un pointeur vers un 
     *       it�rateur qui doit �tre lib�r� par l'objet 
     *       <code>SearchSpace::Iterator</code>.  La raison pour laquelle cette
     *       fa�on de faire a �t� adopt� est qu'une classe ne peut contenir 
     *       qu'une r�f�rence ou un pointeur vers un objet abstrait.
     * \endfrench
     *
     * \english
     * An iterator on the search space's possibilities.
     *
     * This class is a wrapper of <code>SearchSpaceIterator</code>.
     *
     * @note The class' constructor takes a pointer to an iterator which will
     *       be freed by <code>SearchSpace::Iterator</code>, the current
     *       class.  This is done this way because C++ allows only references
     *       or pointers on abstract objects.
     * \endenglish
     * 
     *
     * @version 1.1
     * @see ::SearchSpaceIterator
     */
    class Iterator
    {
    public :
        /**
         * \french
         * Constructeur.
         *
         * @param iterator L'it�rateur original.
         * \endfrench
         *
         * \english
         * Constructor.
         *
         * @param iterator The wrapped iterator. 
         * \endenglish
         */
        Iterator( SearchSpaceIterator* iterator );

        /**
         * \french
         * Constructeur de copie.
         *
         * @param copy L'objet � copier.
         * \endfrench
         *
         * \english
         * Copy contructor.
         *
         * @param copy The object to be copied. 
         * \endenglish
         */
        Iterator( const Iterator& copy );
        
        /**
         * \french
         * Destructeur.
         * \endfrench
         *
         * \english
         * Destructor. 
         * \endenglish
         */
        virtual ~Iterator();
        
        /**
         * \french
         * Indique s'il reste des possibilit�s � �num�rer.
         *
         * @return <code>true</code> s'il y a encore des possibilit�s.
         * \endfrench
         *
         * \english
         * Checks if the iterator points on the last possibility.
         *
         * @return <code>true</code> if the iterator does not point on the last 
         *         possibility.
         * \endenglish
         */
        bool hasNext() const;
           
        /**
         * \french
         * Positionne l'it�rateur sur la prochaine possibilit�.
         * \endfrench
         *
         * \english
         * Place the iterator on the next possibility. 
         * \endenglish
         */
        void next();

        /**
         * \french
         * Retourne la position en y de la possibilit� courante.
         * 
         * @return La position en y.
         * \endfrench
         *
         * \english
         * Gets the current possibility's y coordinate.
         *
         * @return The y coordinate.
         * \endenglish
         */
        int x() const;

        /**
         * \french
         * Retourne la position en y de la possibilit� courante.
         * 
         * @return La position en y.
         * \endfrench
         *
         * \english
         * Gets the current possibility's y coordinate.
         *
         * @return The y coordinate.
         * \endenglish
         */
        int y() const; 

    private :
        /** 
         * \french
         * L'it�rateur emball�.
         * \endfrench
         *
         * \english
         * The wrapped iterator. 
         * \endenglish
         */  
  
        std::auto_ptr< SearchSpaceIterator > m_iterator;

    };   


};

/**
 * \french
 * It�rateur d'espace de recherche.
 *
 * Permet de parcourir les possibilit�s d'un espace de recherche.  
 *
 * @note Cette classe a �t� fait pour contourner le fait qu'une fonction ne 
 *       peut retourner un objet abstrait.  Les objets descendants servent �
 *       construire un <code>SearchSpace::Iterator</code>.
 *
 * Contraintes sur l'it�rateur:
 * <ul>
 * <li> Les solutions doivent �tre donn�es dans l'ordre des ( x, y ).
 *
 * <li> Lors de l'initialisation, l'it�rateur pointe sur la possibilit� avant la
 *      premi�re. ie Une appelle � next doit �tre faite avant d'avoir acc�s �
 *      la premi�re solution.
 * </ul>
 * \endfrench
 *
 * \english
 * Iterator on the search space's possibilities.
 *
 * @note This class was made because C++ allows only references or pointers on
 *       abstract objects.  The children of this class have for purpose to
 *       construct objects of type <code>SearchSpace::Iterator</code>.
 *
 * Constraints :
 * <ul>
 * <li> The solutions are in the ( x, y ) order.
 * <li> On initialization, the iterator points on the possibility before the
 *      first one. ie <code>next</code> must be called prior to access the
 *      first possibility.
 * </ul>
 * \endenglish
 * 
 *
 * @version 1.1
 */
class SearchSpaceIterator
{
    // Pour donner acc�s � clone
    friend class SearchSpace::Iterator;
    
public :    
     
    /**
     * \french
     * Indique s'il reste des possibilit�s � �num�rer.
     *
     * @return <code>true</code> s'il y a encore des possibilit�s.
     * \endfrench
     *
     * \english
     * Checks if the iterator points on the last possibility.
     *
     * @return <code>true</code> if the iterator does not point on the last 
     *         possibility.
     * \endenglish
     */
    virtual bool hasNext() const = 0;

    /**
     * \french
     * Positionne l'it�rateur sur la prochaine possibilit�.
     * \endfrench
     *
     * \english
     * Place the iterator on the next possibility. 
     * \endenglish
     */
    virtual void next() = 0;

    /**
     * \french
     * Retourne la position en y de la possibilit� courante.
     * 
     * @return La position en y.
     * \endfrench
     *
     * \english
     * Gets the current possibility's y coordinate.
     *
     * @return The y coordinate.
     * \endenglish
     */
    virtual int x() const = 0;

    /**
     * \french
     * Retourne la position en y de la possibilit� courante.
     * 
     * @return La position en y.
     * \endfrench
     *
     * \english
     * Gets the current possibility's y coordinate.
     *
     * @return The y coordinate.
     * \endenglish
     */
    virtual int y() const = 0;

protected :
    /** 
     * \french
     * Clone l'it�rateur.
     * 
     * @return Un pointeur vers une copie de l'it�rateur.  Cette copie sera
     *         d�truite par <code>SearchSpace::Iterator</code>.
     * \endfrench
     *
     * \english
     * Clone the iterator. 
     *
     * @return A pointer on a copy of the iterator.  This copy will be
     *         freed by <code>SearchSpace::Iterator</code>.
     * \endenglish
     */
    virtual SearchSpaceIterator* clone() const = 0;
};

}// namespace japa

#endif
