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

#ifndef JAPA_SPARSE_DT_H
#define JAPA_SPARSE_DT_H

#include "dynamictable.h"
#include "searchspace.h"
#include "scorefunction.h"
#include "fe_sparse.h"
#include "iostream"

using namespace std;

namespace japa
{

/**
 * \french
 * Une table dynamique dont les solutions ne sont pas toutes consid�r�es.
 *
 * Les solutions � consid�rer sont ceux sp�cifi�s par l'espace de recherche.
 * 
 * @note Pour pouvoir retracer la meilleure solution, la case 
 *       <code>( UpperBoundX, UpperBoundY )</code> doit faire partie de l'espace
 *       de recherche.
 *
 * @param T Le type de donn�e du score.
 * 
 * \endfrench
 *
 * \english
 * A dynamic table where not all solitions are computed.
 *
 * The solutions to compute are specified by a search space.
 * 
 * @note In order to track the optimal solution, the 
 *       <code>(UpperBoundX, UpperBoundY)</code> must be in the search space.
 *
 * @param T The score's data type.
 * \endenglish
 *
 *
 * @version 1.1
 */
template< class T >
class SparseDT : public DynamicTable< T >
{
protected :
    class Cell;

    class Iterator;
    
    /** 
     * \french
     * Le type de la structure de donn�e repr�sentant la table. 
     * \endfrench
     *
     * \english
     * Dynamic table's data type. 
     * \endenglish
     */
    typedef SparseMatrix< Cell > Table;

public :
    /**
     * \french
     * Constructeur.
     *
     * @note Seulement des r�f�rences de l'espace de recherche et de la fonction
     *       de score sont stock�es dans l'objet, donc ils ne doivent pas �tre d�truit
     *       avant celui-ci.
     *
     * @param searchSpace L'espace de recherche � consid�rer.      
     * @param score Le fonctor utilis� pour calculer le score d'une cellule.
     * \endfrench
     *
     * \english
     * Constructor.
     *
     * @note Only references on the search space and the score function are
     *       kept, so these objects should not be destructed before the
     *       instance of the current class.
     *
     * @param searchSpace A reference to the search space to consider.
     * @param score A reference to the dynamic table's score function.
     * \endenglish
     */
    SparseDT( const SearchSpace& searchSpace, ScoreFunction< T >& score );
    
    /**
     * \french
     * Destructeur.
     * \endfrench
     *
     * \english
     * Destructor. 
     * \endenglish
     */
    virtual ~SparseDT();
    
    void solve();

    bool getScore( const int i, const int j, T& score ) const;

    typename DynamicTable< T >::Iterator getIterator() const;
    
private :
    /** 
     * \french
     * R�f�rence vers l'espace de recherche. 
     * \endfrench
     *
     * \english
     * A reference to the search space. 
     * \endenglish
     */
    const SearchSpace& m_searchSpace;

    /** 
     * \french
     * La fonction de score 
     * \endfrench
     *
     * \english
     * A reference to the score function. 
     * \endenglish
     */
    ScoreFunction< T >& m_score;

    /** 
     * \french
     * La matrice creuse utilis�e pour stocker les r�sultats de la table. 
     * \endfrench
     *
     * \english
     * The sparse matrix where the results are stocked. 
     * \endenglish
     */
    Table m_table;

protected :
    /**
     * \french
     * Contient les informations sur une cellule de la table dynamique.
     * \endfrench
     *
     * \english
     * Contains the information on a cell of a dynamic table.  
     * \endenglish
     *
     *
     * @version 1.1
     */
    class Cell
    {
    public :
        /**
         * \french
         * Constructeur.
         * \endfrench
         *
         * \english
         * Constructor. 
         * \endenglish
         */
        Cell();
        
        /**
         * \french
         * Constructeur.
         *
         * @param score Le score associ� � la cellule.
         * @param pi La colonne de la cellule pr�c�dente.
         * @param pj La ligne de la cellule pr�c�dente.
         * \endfrench
         *
         * \english
         * Constructor.
         *
         * @param score The cell's score.
         * @param pi The preceding cell's column.
         * @param pj The preceding cell's row. 
         * \endenglish
         */
        Cell( const T score, const int pi, const int pj );

        /**
         * \french
         * Ajuste le score de la cellule.
         *
         * @param score Le nouveau score de la cellule.
         * \endfrench
         *
         * \english
         * Sets the cell's score.
         * 
         * @param score The new cell's score. 
         * \endenglish
         */
        void setScore( const T& score );
        
        /**
         * \french
         * Retourne le score de la cellule.
         * 
         * @return Le score de la cellule.
         * \endfrench
         *
         * \english
         * Gets the cell's score.
         *
         * @return The cell's score.
         * \endenglish
         */
        T getScore() const;

        /**
         * \french
         * Ajuste le nouvel indice de la colonne de la cellule pr�c�dente.
         *
         * @param pi Le nouvel indice de la colonne de la cellule pr�c�dente.
         * \endfrench
         *
         * \english
         * Sets the column number of the preceding cell.
         *
         * @param pi The new preceding cell's column. 
         * \endenglish
         */
        void setPreviousI( const int pi );
        
        /**
         * \french
         * Retourne la colonne de la cellule pr�c�dente.
         * 
         * @return La colonne de la cellule pr�c�dente.
         * \endfrench
         *
         * \english
         * Gets the row number of the preceding cell.
         *
         * @return The preceding cell's row.
         * \endenglish
         */
        int getPreviousI() const;
        
        /**
         * \french
         * Ajuste l'indice de la rang�e de la cellule pr�c�dente.
         *
         * @param pj Le nouvel indice de la rang�e pr�c�dente.
         * \endfrench
         *
         * \english
         * Sets the column number of the preceding cell.
         * 
         * @param pj The new preceding cell's row.
         * \endenglish
         */
        void setPreviousJ( const int pj );

        /**
         * \french
         * Retourne l'indice de la rang�e de la cellule pr�c�dente.
         * 
         * @return L'indice de la rang�e de la cellule pr�c�dente.
         * \endfrench
         *
         * \english
         * Gets the row number of the preceding row.
         *
         * @return The preceding cell's row.
         * \endenglish
         */
        int getPreviousJ() const;

    private :
        /** 
         * \french
         * Le score de la cellule. 
         * \endfrench
         *
         * \english
         * The cell's score. 
         * \endenglish
         */
        T m_score;

        /** 
         * \french
         * La colonne de la cellule pr�c�dente. 
         * \endfrench
         *
         * \english
         * The column number of the preceding cell. 
         * \endenglish
         */
        int m_pi;

        /** 
         * \french
         * La ligne de la cellule pr�c�dente. 
         * \endfrench
         *
         * \english
         * The row number of the preceding cell. 
         * \endenglish
         */
        int m_pj;
    };
    
    /**
     * \french
     * It�rateur sur la solution optimale d'une table dynamique.
     * \endfrench
     *
     * \english
     * Iterator on the optimal solution of a dynamic table. 
     * \endenglish
     *
     *
     * @version 1.1
     */
    class Iterator : public DynamicTableIterator< T >
    {
    public :
        /**
         * \french
         * Constructeur.
         *
         * @param table La table.
         * @param i L'indice de la colonne de la cellule o� l'�num�ration
         *          commence.
         * @param j L'indice de la rang�e de la cellule o� l'�num�ration 
         *          commence.
         * \endfrench
         *
         * \english
         * Constructor.
         *
         * @param table The table.
         * @param i The column number of the beginning cell.
         * @param j The row number of the beginning cell. 
         * \endenglish
         */
        Iterator( const Table& table, const int i, const int j );
        
        bool hasNext() const;

        void next();

        int i() const;

        int j() const;

        T score() const;

    protected :
        DynamicTableIterator< T >* clone() const;

    private :
        /** 
         * \french
         * La table 
         * \endfrench
         *
         * \english
         * The table. 
         * \endenglish
         */
        const Table& m_table;

        /** 
         * \french
         * La cellule courante.
         * \endfrench
         *
         * \english
         * The current cell. 
         * \endenglish
         */
        Cell m_cell;

        /** 
         * \french
         * L'indice de la colonne de la cellule courante. 
         * \endfrench
         *
         * \english
         * The current column number. 
         * \endenglish
         */
        int m_i;

        /** 
         * \french
         * L'indice de la rang�e de la cellule courante. 
         * \endfrench
         *
         * \english
         * The current row number. 
         * \endenglish
         */
        int m_j;
    };
};

// ------------------------------------------------------------------------ //
template< class T >
SparseDT< T >::SparseDT( const SearchSpace& searchSpace, 
                         ScoreFunction< T >& score ) 
        : m_searchSpace( searchSpace ),
          m_score( score )
{}

// ------------------------------------------------------------------------ //
template< class T >
SparseDT< T >::~SparseDT()
{}

// ------------------------------------------------------------------------ //
template< class T >
void SparseDT< T >::solve()
{
    int pi;     // La colonne de la case pr�c�dente
    int pj;     // La rang�e de la case pr�c�dente
    Cell cell;  // La cellule courante
    double score;
    
    SearchSpace::Iterator iter = m_searchSpace.getIterator();    

    // Pour chaque case de l'espace solution
    while( iter.hasNext() )
    {
        iter.next();
        //cout << iter.y() << "  " << iter.x() << endl;

        // Par convention, si une cellule n'a pas de pr�c�dente, elle pointe
        // vers elle-m�me

        pi = iter.x();
        pj = iter.y();
        //cout << "On est avec la MC X et Y � traiter: " << iter.y() << " " << iter.x()  << endl;
        score =  m_score( *this, iter.x(), iter.y(), pi, pj );
        //cout << "On est avec la MC le score final de X,Y: " << iter.y() << " " << iter.x()  << " est: " << score << endl;

        cell.setScore( score );
        cell.setPreviousI( pi );
        cell.setPreviousJ( pj );
        
        m_table.set( iter.x(), iter.y(), cell );
    }
}

// ------------------------------------------------------------------------ //
template< class T >
bool SparseDT< T >::getScore( const int i, const int j, T& score ) const
{
    bool ret = false;
    Cell cell;

    if( m_table.get( i, j, cell ) )
    {
        score = cell.getScore();
        ret = true;
    }

    return ret;
}

// ------------------------------------------------------------------------ //
template< class T >
typename DynamicTable< T >::Iterator SparseDT< T >::getIterator() const
{
    // L'it�rateur s'occupera lui-m�me de la destruction de l'objet 
    // nouvellement cr��.
    return typename DynamicTable< T >::Iterator( 
            new typename SparseDT< T >::Iterator( m_table, 
                                         m_searchSpace.getUpperBoundX(),
                                         m_searchSpace.getUpperBoundY() ) );
}


// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //
template< class T >
SparseDT< T >::Cell::Cell() : m_pi( 0 ), m_pj( 0 )
{}

// ------------------------------------------------------------------------ //
template< class T >
SparseDT< T >::Cell::Cell( const T score, 
                           const int pi, const int pj ) : m_score( score ),
                                                          m_pi( pi ), 
                                                          m_pj( pj )
{}

// ------------------------------------------------------------------------ //
template< class T >
void SparseDT< T >::Cell::setScore( const T& score )
{
    m_score = score;
}

// ------------------------------------------------------------------------ //
template< class T >
void SparseDT< T >::Cell::setPreviousI( const int pi )
{
    m_pi = pi;
}

// ------------------------------------------------------------------------ //
template< class T >
void SparseDT< T >::Cell::setPreviousJ( const int pj )
{
    m_pj = pj;
}

// ------------------------------------------------------------------------ //
template< class T >
T SparseDT< T >::Cell::getScore() const
{
    return m_score;
}

// ------------------------------------------------------------------------ //
template< class T >
int SparseDT< T >::Cell::getPreviousI() const
{
    return m_pi;
}

// ------------------------------------------------------------------------ //
template< class T >
int SparseDT< T >::Cell::getPreviousJ() const
{
    return m_pj;
}

// ------------------------------------------------------------------------ //
// ------------------------------------------------------------------------ //
template< class T >
SparseDT< T >::Iterator::Iterator( const Table& table, const int i, 
                                   const int j ) : m_table( table ),
                                                   m_cell( T(), i, j )
{
    Cell c;
    
    if( !m_table.get( i, j, c ) )
    {
        // La solution est vide, donc hasNext doit �tre faux
        m_i = i;
        m_j = j;
    }
    else
    {
        // le prochain hasNext doit retourn� vrai, donc l'important c'est que
        // m_i et m_j soient diff�rentes de i et j.  La bonne valeur sera mise
        // � jour au prochain next.  C'est laid, mais c'est la vie.
        m_i = i + 1;
        m_j = j + 1;
    }
}

// ------------------------------------------------------------------------ //
template< class T >
bool SparseDT< T >::Iterator::hasNext() const
{
    // Par convention, une cellule terminale pointe sur elle m�me
    return !( m_cell.getPreviousI() == i() && m_cell.getPreviousJ() == j() );
}

// ------------------------------------------------------------------------ //
template< class T >
void SparseDT< T >::Iterator::next()
{
    m_i = m_cell.getPreviousI();
    m_j = m_cell.getPreviousJ();

    m_table.get( m_i, m_j, m_cell );
}

// ------------------------------------------------------------------------ //
template< class T >
int SparseDT< T >::Iterator::i() const
{
    return m_i;
}

// ------------------------------------------------------------------------ //
template< class T >
int SparseDT< T >::Iterator::j() const
{
    return m_j;
}

// ------------------------------------------------------------------------ //
template< class T >
T SparseDT< T >::Iterator::score() const
{
    return m_cell.getScore();
}

// ------------------------------------------------------------------------ //
template< class T >
DynamicTableIterator< T >* SparseDT< T >::Iterator::clone() const
{
    DynamicTableIterator< T >* ptr;

    ptr = new Iterator( m_table, m_cell.getPreviousI(), m_cell.getPreviousJ() );

    return ptr;
}

}// namespace japa

#endif
