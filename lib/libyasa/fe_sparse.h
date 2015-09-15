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
/* ===========================================================================
   MODULE:

   fe_sparse.h -- Just a template to deal with sparse matrices (not
   optimal, but it works). A sparse matrix is just a two-dimension
   matrix, which elements are of any type specified during the template 
   instanciation.


   PROGRAMMER: 
   felipe
   
   COMMENTS: 
   To create a sparse matrix of float: SparseMatrix<float> MaMatrice;

   felipe@RALI, Copyright (C) 2001
   
   ====================================================================== */

#ifndef __FE_SPARSE_MATRIX
#define __FE_SPARSE_MATRIX


// Référence : http://gcc.gnu.org/onlinedocs/libstdc++/faq/index.html#5_4
#ifdef __GNUC__
    #if __GNUC__ < 3
        #include <hash_map.h>
        namespace Sgi { using ::hash_map; }; // inherit globals
    #elif __GNUC__ == 3
        #include <ext/hash_map>
        #if __GNUC_MINOR__ == 0
            namespace Sgi = std;               // GCC 3.0
        #else
            namespace Sgi = ::__gnu_cxx;       // GCC 3.1 and later 3.x
        #endif
    #else
        #include <ext/hash_map>
        namespace Sgi = ::__gnu_cxx;
    #endif
#else      // ...  there are other compilers, right?
namespace Sgi = std;
#endif

#include <algorithm>
#include <cstdio>
#include <stack>
#include <string>
#include <vector>

/* ---------------------------------------------------------
   A sparse matrix relying on map of maps
   The key is always an int (I could have parametrize that too), 
   the info part could be anything you want, therefore the 
   templetization of this class, T being the type
   of the information to be stored. 
   --------------------------------------------------------- */

/**
 * En fait un <b>template</b> qui permet de spécifier le type
 * <code>T</code> de l'info d'une cellule de la matrice.  Une
 * <code>SparseMatrix</code> est une matrice à deux dimensions a
 * priori creuse, indicée par deux entiers.
 * 
 * Cette implémentation est loin d'être optimale, mais sert les
 * besoins que j'en ai. C'est codé par une <code>hash_map</code> de
 * <code>map</code>, avec mes connaissances de l'époque de STL 
 * 
 * felipe @ 2001
 */

template <class T>
class SparseMatrix {

 public:

  /**
   * Une ligne de la matrice
   */
  typedef typename Sgi::hash_map<int, T> infoMap;

 private:

  /**
   * Le type de la matrice creuse
   */
   typedef typename Sgi::hash_map<int, infoMap> SMatrix;

   
  /**
   * Contient l'environnement liée à une recherche itérée.
   */
  typedef typename std::pair<int, 
      std::pair<typename infoMap::const_iterator,
                typename infoMap::const_iterator> > LoopContext;
   
  /**
   * Structure qui sert à stocker l'environnement lié à une recherche itérée
   * C'est une pile, ce qui permet d'empiler autant d'environnement que souhaité 
   * Voici ce qu'est ici un environnement:
   * <nbNext, <itLoop,endLoop>>
   */
  typedef typename std::stack< LoopContext > HLoop;

   /**
    * La matrice creuse
    */
   SMatrix *table;

   infoMap nopair; 
   HLoop lookBack; // for multiple sequence lookup

   typename SMatrix::iterator it;
   typename infoMap::iterator iit;
   typename infoMap::const_iterator itLoop,endLoop; // to deal with sequences
   int nb; // nb d'elements
   int nbNext;
   int maxI,minI; 

   inline void takeMinMax(int i) {
     if (nb == 0) maxI = minI = i;
     else {
       if (maxI < i) maxI = i;
       if (minI > i) minI = i;           
     }
   }

 public:

   /**
    * Crée une matrice creuse avec <code>size</code> lignes.
    * Les colonnes n'existent encore pas
    */

  SparseMatrix(const int size=500) {    
    table = new SMatrix(size);
    nb = 0;
  }
  
  ~SparseMatrix() {delete table;}

  /**
   * @param i L'indice de la ligne (0-indicée)
   * @param j L'indice de la colonne (0-indicée)
   * @param info L'information à ranger en case <code>[i,j]</code>
   * @return <code>true</code> si la case <code>[i,j]</code> est nouvelle
   *
   * Ajoute <code>info</code> dans la case <code>[i,j]</code>. Si la
   * case n'existe encore pas, elle est automatiquement créée et prend
   * la valeur <code>info</code>.
   *
   * <b>Note:</b> L'addition est effectuée avec l'opérateur
   * <code>+</code>. Si cet opérateur n'est pas défini pour le type
   * <code>T</code>, votre programme ne compilera pas.
   */
  inline bool add(const int i, const int j, const T info) {
    
    it = table->find(i);
    if (it == table->end()) {
      takeMinMax(i);
      infoMap boot;
      boot.insert(make_pair(j,info));
      table->insert(make_pair(i,boot));
      nb++;
      return true;
    }
   
    // i exists , let's check j
    iit = it->second.find(j);
    if (iit == it->second.end()) { // new j
      it->second.insert(make_pair(j,info));
      nb++;
      return true;
    }

    // i j existent
    iit->second += info;
    return false;
  }

  /**
   * @param i L'indice de la ligne (0-indicée) 
   * @param j L'indice de la colonne (0-indicée) 
   * @param info L'information à ranger en case <code>[i,j]</code> 
   *
   * @return une copie de l'élément ajouté à la case
   * <code>[i,j]</code>. Si la case n'existe pas, la multiplication
   * n'est pas effectuée et la méthode retourne <code>(T)0</code> (qui
   * doit prendre un sens pour le type <code>T</code>).
   *
   * Multiplie <code>info</code> au contenu de la case <code>[i,j]</code>. 
   *
   * <b>Note:</b> Cette méthode présuppose l'existence pour le type
   * <code>T</code> de l'opérateur <code>*=</code> 
   */

  inline T times(const int i, const int j, const T info) {

    it = table->find(i);
    if (it == table->end()) return (T)0;
   
    // i exists , let's check j
    iit = it->second.find(j);
    if (iit == it->second.end()) return (T) 0;

    // i j existent
    iit->second *= info;
    return iit->second;    
  }

  /**
   * @param i L'indice de la ligne (0-indicée)
   * @param j L'indice de la colonne (0-indicée)
   * @param info L'information à ranger en case <code>[i,j]</code>
   * @return <code>true</code> si la case <code>[i,j]</code> est nouvelle
   *
   * Range <code>info</code> dans la case <code>[i,j]</code>. Si la
   * case n'existe encore pas, elle est automatiquement créée et prend
   * la valeur <code>info</code>
   */
  inline bool set(const int i, const int j, const T info) {

    it = table->find(i);
    if (it == table->end()) {
      takeMinMax(i);
      infoMap boot;
      boot.insert(std::make_pair(j,info));
      table->insert(std::make_pair(i,boot));
      nb++;
      return true;
    }
   
    // i exists , let's check j
    iit = it->second.find(j);
    if (iit == it->second.end()) { // new j
      it->second.insert(std::make_pair(j,info));
      nb++;
      return true;
    }

    // i j existent
    iit->second = info;
    return false;
  }

  /**
   * @param i L'indice de la ligne (0-indicée)
   * @param j L'indice de la colonne (0-indicée)
   * @param info Référence sur l'information à récupérer en case <code>[i,j]</code>
   * @return <code>false</code> si la case <code>[i,j]</code> n'existe pas et dans ce cas, 
   * la valeur de <code>info</code> n'est pas pertinente
   */
  inline bool get(const int i, const int j, T& info) const {
    typename SMatrix::iterator it;
    typename infoMap::iterator iit;
    
    it = table->find(i);
    if (it == table->end()) return false;
   
    // i exists
    iit = it->second.find(j);
    if (iit == it->second.end()) return false;

    // i et j exist
    info = iit->second;
    return true;
  }

  /**
   * @name size
   * @public
   * @return Le nombre de cellules dans la matrice
   */
  inline int size() const {return nb;}

  /**
   * Vide la table (sans libérer la mémoire)
   */
  inline void clear() {table->clear();}
  
  /*
   * @param i le numero de la ligne
   * @return la somme des valeurs des colonnes sur la ligne i
   *         ou 0 si la ligne n'existe pas
   */
  inline T sum( const int i) {
    it = table->find(i);
    if (it != table->end()) {
      T sum = (T)0;
      
      typename infoMap::iterator eLoop = it->second.end();
      typename infoMap::iterator iLoop = it->second.begin();
      while (iLoop != eLoop) {
	sum += iLoop->second;
	iLoop++;
      }
      return sum;
    } // si ligne existe
    return (T) 0;
  }

  /**
   * Normalise à 1 la ligne <code>i</code>. Il faut bien sûr que cela
   * présente un intérêt particulier dans votre problème ...  
   * ET que la matrice abrite des flottants ...
   */

  inline void normalize( const int i) {
    it = table->find(i);
    if (it != table->end()) {
      T sum= (T) 0;
      
      typename infoMap::iterator eLoop = it->second.end();
      typename infoMap::iterator iLoop = it->second.begin();
      while (iLoop != eLoop) {
	sum += iLoop->second;
	iLoop++;
      }
      if (sum != (T)0) { // the comparison may be improper (use a small epsilon if require)
	eLoop = it->second.end();
	iLoop = it->second.begin();
	while (iLoop != eLoop)  {
	  iLoop->second /= sum;
	  iLoop++;
	}
      }      
    } // si ligne existe
  }

  /**
   * @param i L'indice de la ligne (0-indicée)
   * @param info La valeur à mettre dans la ligne <code>i</code>
   *
   * Met toutes les cases <code>[i,j]</code> existantes (pour la ligne
   * <code>i</code> spécifiée en argument) à la valeur <code>info</code>
   */

  inline void init (const int i, const T info) {
    it = table->find(i);
    if (it != table->end()) {
      
      typename infoMap::iterator eLoop = it->second.end();
      typename infoMap::iterator iLoop = it->second.begin();

      while (iLoop != eLoop)  {
	iLoop->second = info;
	iLoop++;
      }      
    } // si ligne existe
  }

  /**
   * @param i valeur de la ligne
   * @return true si cette ligne existe dans la matrice
   *
   * Permet de démarrer une itération sur toutes les colonnes d'une
   * ligne dont l'indice est passé en argument.  
   */
  inline bool begin(const int i) {
    itLoop = endLoop = nopair.end();
    it = table->find(i);
    nbNext = 0;

    if (it != table->end()) {
      endLoop = it->second.end();
      itLoop = it->second.begin();
      nbNext = it->second.size();
      return true;
    }
    return false;
  }

  /**
   * @return <code>true</code> s'il reste des colonnes à parcourir
   * dans l'itération lancée par le dernier appel à <code>begin()</code>
   *  
   * <b>Note:</b> Ca serait une erreur d'appeler cette méthode sans
   * appeler auparavent <code>begin()</code>
   */
  inline bool hasMore() const {return itLoop != endLoop;}


  /**
   * @return Un itérateur sur la prochaine cellule non encore retournée dans l'itération
   *         iterator->first est l'indice de la colonne
   *         iterator->second est l'information de la cellule 
   */
  inline typename infoMap::const_iterator getNext() {return itLoop++;}


  /**
   * @return Le nombre de cellule encore à visiter
   */
  inline int howManyNext() const {return nbNext;}  // this one should be called only after a begin
  
  /**
   * Permet d'empiler le contexte de recherche actuel pour 
   * préparer une nouvelle recherche
   */
  inline void storeLoop() {
    lookBack.push(make_pair(nbNext, make_pair(itLoop,endLoop)));
  }
  
  /**
   * Dépile le dernier contexte de l'itération. Cette méthode de
   * devrait jamais être appelée plus de fois que la méthode
   * <code>storeLoop</code> 
   */
  inline void restoreLoop() {
      if (lookBack.empty() == false) {
          LoopContext& ref = lookBack.top();
	  nbNext = ref.first;
	  itLoop = ref.second.first;
	  endLoop = ref.second.second;
	  lookBack.pop();
      }
  }

  /**
   * @param i L'indice de la ligne
   * @param ok Est mis à <code>true</code> si la ligne <code>i</code> existe dans la matrice
   * @return La première cellule de la ligne 
   *         <code>it->first</code> représente l'indice de la colonne, 
   *         <code>it->second</code> représente  l'information 
   */

   inline typename infoMap::const_iterator first( const int i, bool& ok) {
      it = table->find(i);
      if (it != table->end()) {
	 ok = it->second.size();
	 return it->second.begin();
      }
      ok = false; // no special return
   }

  /**
   * @param i L'indice de la ligne
   * @param ok Est mis à <code>true</code> si la ligne <code>i</code> existe dans la matrice
   * @return La dernière cellule de la ligne 
   *         <code>it->first</code> représente l'indice de la colonne, 
   *         <code>it->second</code> représente  l'information 
   */
   inline typename infoMap::const_iterator last( const int i, bool& ok) {
      it = table->find(i);
      if (it != table->end()) {
	 ok = it->second.size();
	 iit = it->second.end();
	 return --iit; 
      }
      ok = false; // return unspecified
   }
   
   /**
    * @return l'indice maximal d'une ligne
    */
   inline int getMaxIndexLine() const {return maxI;}

   /**
    * @return l'indice minimal d'une ligne
    */
   inline int getMinIndexLine() const {return minI;}

   /* 
    * ******************************************
    * j'aimerais virer les methodes qui suivent
    * mais de memoire, elles servent a certains
    * endroits. A verifier lors de la prochaine 
    * phase de purge
    * ******************************************
    */


   /**
    * Permet de dumper la matrice dans un fichier. C'est à votre
    * charge de définir cette méthode, si vous en avez besoin. Car
    * après tout, je ne connais rien du type <code>T</code> que vous
    * allez choisir.  
    */
  inline void Save(FILE *file);

  /**
    * Permet de lire une matrice depuis un fichier. C'est à votre
    * charge de définir cette méthode, si vous en avez besoin. Car
    * après tout, je ne connais rien du type <code>T</code> que vous
    * allez choisir.  
    */

  inline void Read(FILE *file);

};


#endif // __FE_SPARSE_MATRIX
