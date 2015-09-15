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

#include "cognatessf.h"
#include "linearssf.h"
#include "mapsetsearchspace.h"
#include "sparsedt.h"
#include "iostream"

using namespace std;

namespace japa
{

// ------------------------------------------------------------------------ //
CognateSSF::CognateSSF( Text& source, Text& target, 
                        SolutionMarker& solMarker,
                        const int returnCount, const double returnCost,
                        const size_t radius, const size_t maxFrequency )
        : m_source( source ), m_target( target ), m_solMarker( solMarker ),
          m_returnCount( returnCount ), m_returnCost( returnCost ),
          m_radius( radius ), m_maxFrequency( maxFrequency )
{}


                        
// ------------------------------------------------------------------------ //
SearchSpace& CognateSSF::operator()( SearchSpace& s )
{
    MapSetSearchSpace wordSS( 0, 0, m_target.getWordCount() - 1,
                              m_source.getWordCount() - 1 );
    CognateSSValidator validator( m_maxFrequency );
    
    WordSSF wordSSF( m_source, m_target, validator, m_radius );
    WordScoreFunction wordSF( wordSS, m_returnCount, m_returnCost );
    SparseDT< double > wordDT( wordSS, wordSF );
    
    // N�cessaire pour une bonne initialisation.
    wordSS.addPossibility( wordSS.getLowerBoundX(), wordSS.getLowerBoundY() );

    // N�cessaire pour que la solution puisse �tre retrac�e.
    wordSS.addPossibility( wordSS.getUpperBoundX(), wordSS.getUpperBoundY() );

    wordSSF( wordSS );

    wordDT.solve();

    // Remplit l'espace de recherche pour l'alignement des phrases.
    fill( s, wordDT ); 

    return s;
}

// ------------------------------------------------------------------------ //
void CognateSSF::fill( SearchSpace& searchspace, 
                       DynamicTable< double >& wordDT ) const
{ 
    LinearSSF ssf( m_solMarker );
    DynamicTable< double >::Iterator optimalSol = wordDT.getIterator();
    // S'assure qu'il n'y ait pas de "trous" dans l'espace de recherche.

    ssf.addPassagePoint( searchspace.getLowerBoundX(), 
                         searchspace.getLowerBoundY() );
    
    //ssf.addPassagePoint( 0, 0 );
    
    ssf.addPassagePoint( searchspace.getUpperBoundX(), 
                         searchspace.getUpperBoundY() );

    // Trace le faisceau en tenant compte des cognates.
    //cout << "On va afficher les phrases de la solution optimale des cognates..!"<< endl;
    while( optimalSol.hasNext() )
    {
        optimalSol.next();
        ////////////////////////////nous affiche la solution optimale des cognates
        //cout  << optimalSol.j() << " " << optimalSol.i() << endl;

        ////////////////////////////nous affiche les phrases de la solution optimale des cognates
        //cout  << m_source.getSentenceIndice( optimalSol.j() ) << " " << m_target.getSentenceIndice( optimalSol.i() ) << endl;

        // Les coordonn�es en j repr�sentent des mots du texte source et les
        // coordonn�es en i des mots du texte cible
        ssf.addPassagePoint( m_source.getSentenceIndice( optimalSol.j() ), 
                             m_target.getSentenceIndice( optimalSol.i() ) );
    }

    ssf( searchspace );

    //ma partie

    //SearchSpace::Iterator it = searchspace.getIterator();
    //    while(it.hasNext())
    //    {
    //    	cout << "X: " << it.y() << "Y: " << it.x() << endl;
    //    	it.next();
    //    }

    //ma partie

}

}// namespace japa
