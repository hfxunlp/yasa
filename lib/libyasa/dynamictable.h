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

#ifndef JAPA_DYNAMIC_TABLE_H
#define JAPA_DYNAMIC_TABLE_H

#include <memory>



namespace japa
{

template< class T > class DynamicTableIterator;

/**
 * \french
 * Permet de r�soudre un probl�me avec une approche de programmation
 * dynamique.
 *
 * Cette classe est abstraite, car diff�rents type de probl�mes demandent
 * diff�rentes stuctures de donn�es pour �tre r�solus optimalement.
 * 
 * @param T Le type utilis� pour noter le score.
 * \endfrench
 *
 * \english
 * Dynamic programming problem solving framework.
 *
 * This is an abstract class because different type of problems need
 * different data structures to be best resolved.
 *
 * @param T The score's data type.
 * \endenglish
 * 
 *
 * @version 1.1
 */
template< class T >
class DynamicTable
{
public :
    /**
     * \french
     * R�soud un probl�me par programmation dynamique.
     * \endfrench
     *
     * \english
     * Solve a problem using dynamic programming.
     * \endenglish
     */
    virtual void solve() = 0;

    /**
     * \french
     * Trouve le score associ� � une cellule.
     *
     * @param i La coordonn�e en i de la cellule.
     * @param j La coordonn�e en j de la cellule.
     * @param score ( out )Le score associ� � la cellule.
     * 
     * @return <code>true</code> si un score est associ� � la cellule, 
     *         <code>false</code> sinon.  Dans un tel cas, la valeur de 
     *         <code>score</code> est ind�termin�e.
     * \endfrench
     *
     * \english
     * Gets a cell's score.
     *
     * @param i Cell's i coordinate.
     * @param j Cell's j coordinate
     * @param score A reference to the variable which will contain the score.
     *
     * @return <code>true</code> if the cell's score is defined.
     *         <code>false</code> if the cell's score is undefined, which will
     *         yield no coherent value to <code>score</code> variable.
     * \endenglish
     */
    virtual bool getScore( const int i, const int j, T& score ) const = 0;
    
    /**
     * \french
     * Permet de retracer la solution optimale.
     * \endfrench
     *
     * \english
     * Iterator over the optimal solution.
     * \endenglish
     *
     *
     * @version 1.1
     */
    class Iterator
    {
    public :
        /**
         * \french
         * Constructeur.
         *
         * @param iter L'it�rateur envelopp�.
         * \endfrench
         *
         * \english
         * Constructor.
         *
         * @param iter Wrapped iterator.
         * \endenglish
         */
        Iterator( DynamicTableIterator< T >* iter );
        
        /**
         * \french
         * Constructeur de copie.
         *
         * @param copy L'objet � copier.
         * \endfrench
         *
         * \english
         * Copy constructor.
         *
         * @param copy The copied object.
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
         * Indique s'il reste des cellules � visiter.
         * 
         * @return <code>false</code> si l'it�rateur a fini d'�num�rer les 
         *         cellules.
         * \endfrench
         *
         * \english
         * Indicates if there are more cells to visit.
         *
         * @return <code>false</code> if there is no more cell.
         * \endenglish
         */
        bool hasNext() const;
    
        /**
         * \french
         * Positionne l'it�rateur sur la prochaine cellule.
         * \endfrench
         *
         * \english
         * Point the iterator on the next cell.
         * \endenglish
         */
        void next();

        /**
         * \french
         * Donne acc�s � la position en i de la cellule courante.
         * 
         * @return La position en i de la cellule courante.
         * \endfrench
         *
         * \english
         * Gets the current cell's i coordinate.
         *
         * @return The current cell's i coordinate.
         * \endenglish
         */
        int i() const;

        /**
         * \french
         * Donne acc�s � la position en j de la cellule courante.
         * 
         * @return La position en j de la cellule courante.
         * \endfrench
         * \english
         * Gets the current cell's j coordinate.
         *
         * @return The current cell's j coordinate.
         * \endenglish
         */
        int j() const; 

        /**
         * \french
         * Donne acc�s au score de la cellule courante.
         * 
         * @return Le score associ� � la cellule courante.
         * \endfrench
         *
         * \english
         * Gets the current cell's score.
         *
         * @return The current cell's score.
         * \endenglish
         */
        T score() const;

        private :
            /** 
             * \french
             * L'it�rateur emball� 
             * \endfrench
             *
             * \english
             * The wrapped iterator.
             * \endenglish
             */  
  
            std::auto_ptr< DynamicTableIterator< T > > m_iterator;
    };

    /**
     * \french
     * Donne acc�s � un it�rateur sur la solution optimale.
     * 
     * @note Cette fonction doit �tre appel�e apr�s <code>solve</code> pour 
     *       retourner une valeur coh�rente.
     * 
     * @return Un it�rateur sur la solution optimale.  
     * \endfrench
     *
     * \english
     * Gets an iterator on the best solution.
     *
     * @note <code>solve</code> must be called before this function in order to
     *       have coherent results.
     *
     * @return An iterator on the best solution.
     * \endenglish
     *
     * @see solve()
     */
    virtual Iterator getIterator() const = 0;

};

/**
 * \french
 * It�rateur de solution optimale.
 *
 * Permet de parcourir la solution optimale d'une table dynamique.  
 *
 * @note Cette classe a �t� fait pour contourner le fait qu'une fonction ne 
 *       peut retourner un  objet abstrait.  Les objets descendants servent 
 *       � construire un  <code>DynamicTable::Iterator</code>.
 *
 * Contraintes sur l'it�rateur:
 *  
 *
 * @version 1.1
 * \endfrench
 *
 * \english
 * Iterator on a dynamic table's best solution.
 *
 * @note This class has for purpose to bypass the fact that a function can't
 *       return an abstract object.  So this class descendant's allow to build
 *       <code>DynamicTable::Iterator</code> objects.
 * \endenglish
 *
 * @param T The score's data type
 * 
 *
 * @version 1.1
 *
 * @see ::DynamicTable
 */
template< class T >
class DynamicTableIterator
{
    friend class DynamicTable< T >::Iterator;
    
public :
    /**
     * @copydoc DynamicTable::Iterator::hasNext()
     */
    
    virtual bool hasNext() const = 0;

    /**
     * @copydoc DynamicTable::Iterator::next()
     */
    virtual void next() = 0;

    /**
     * @copydoc DynamicTable::Iterator::i()
     */
    virtual int i() const = 0;

    /**
     * @copydoc DynamicTable::Iterator::j()
     */
    virtual int j() const = 0; 

    /**
     * @copydoc DynamicTable::Iterator::score()
     */
    virtual T score() const = 0;

protected :
    /** 
     * \french
     * Produit une copie de l'it�rateur.
     * 
     * @return Un pointeur vers une copie de l'it�rateur.  Cette copie sera
     *         d�truite par l'objet courant.
     * \endfrench
     *
     * \english
     * Copy the iterator.
     *
     * @return A pointer on the iterator's copy.  This copy will be deleted
     *         by the current object.
     * \endenglish
     */
    virtual DynamicTableIterator* clone() const = 0;

};

// ------------------------------------------------------------------------ //

template< class T >
DynamicTable< T >::Iterator::Iterator( DynamicTableIterator< T >* iter ) 
        : m_iterator( iter )
{}

// ------------------------------------------------------------------------ //
template< class T >
DynamicTable< T >::Iterator::Iterator( const Iterator& copy )
        : m_iterator( copy.m_iterator -> clone() )
{}

// ------------------------------------------------------------------------ //
template< class T >
DynamicTable< T >::Iterator::~Iterator()
{}

// ------------------------------------------------------------------------ //
template< class T >
bool DynamicTable< T >::Iterator::hasNext() const
{
    return m_iterator -> hasNext();
}

// ------------------------------------------------------------------------ //
template< class T >
void DynamicTable< T >::Iterator::next()
{
    m_iterator -> next();
}

// ------------------------------------------------------------------------ //
template< class T >
int DynamicTable< T >::Iterator::i() const
{
    return m_iterator -> i();
}

// ------------------------------------------------------------------------ //
template< class T >
int DynamicTable< T >::Iterator::j() const
{
    return m_iterator -> j();
}

// ------------------------------------------------------------------------ //
template< class T >
T DynamicTable< T >::Iterator::score() const
{
    return m_iterator -> score();
}

}// namespace japa

#endif
