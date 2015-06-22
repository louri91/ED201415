#include "gs1Set.h"

using namespace std;


gs1Set ::gs1Set (){
  pair<string,int> aux("gs1",0);
  arbol = tree<pair<string,int> >(aux);
  tama = 0;
}

gs1Set ::gs1Set (const gs1Set  & x){
  arbol = x.arbol;
  tama = x.tama;
}

/** @brief insercion del string, cada caracter en una posicion independiente
@todo implementar este metodo correctamente
OJO ESTE METODO SOLO SIRVE PARA DAR UNA IDEA DEL PROCESO DE INSERCION,
HAY QUE IMPLEMENTARLO CORRECTAMENTE
*/
bool gs1Set ::insert(const string& s){ 
tree<pair<string,int> >::node n, aux;
string::const_iterator it;
pair<string,int> par;
bool enc;

  n = arbol.root();
  for (it = s.begin(); it!=s.end(); ++it) { // Para cada caracter del string
   aux = n.left(); // aux es el primer hijo
   enc = false;
   while ( (!aux.null()) && !enc ){ // buscamos el caracter dentro de la lista de hijos
     if ( (*aux).first[0] == (*it) ) { 
       enc = true;
       n = aux; // si lo encuentra, desciende al siguiente nivel
     } else aux = aux.next_sibling();
   }
   if (aux.null()) { // Si no lo ha encontrado, lo inserta
     par.first = string(1,*it);
     par.second = 0;
     n= arbol.insert_left(n,par); // y desciende al siguiente nivel
   }
  }
}


void gs1Set ::print( ) const {
  tree<pair<string,int> >::const_preorderiterator it;
  tree<pair<string,int> >::const_leveliterator itn;
   cout << "preorden " << endl;
   
  for (it= arbol.beginPreorder(); it!= arbol.endPreorder();++it)
    cout << (*it).first << endl;

   cout << "Nivel " << endl;
  for (itn= arbol.beginlevel(); itn!= arbol.endlevel();++itn)
    cout << (*itn).first << endl;
  
}


/**
@todo implementar este metodo correctamente
OJO ESTE METODO OS SIRVE PARA PODER CONSTRUIR UN ARBOL
NO TIENE EN CUENTA EL INVARIANTE DE LA REPRESENTACION
AL NO CONSIDERAR EL CAMPO INT DEL NODO!!!!!
DEBEIS MODIFICARLO PARA QUE LO HAGA DE FORMA CORRECTA
*/      
  
void gs1Set::reading_gs1Set ( ) {

  tree<pair<string,int> >::node n, h;
  queue< tree<pair<string,int> >::node > Q;
   
  pair<string,int> aux;

  n = arbol.root();
  Q.push(n);
  while (!Q.empty() ){
    n = Q.front(); 
    Q.pop();
    cout << "Hijo Izq de " << (*n).first << "/ si no tiene hijos "<< endl;
    cin >> aux.first;
    if (aux.first != "/") { 
      h= arbol.insert_left(n,aux);
      Q.push(h);
      cout << "Hermano Dhc de " << (*h).first<< "/ si no tiene hermano "<< endl;
      cin >> aux.first;
      while (aux.first != "/") {
	h= arbol.insert_right_sibling(h,aux);
	Q.push(h);
	cout << "Hermano Dhc de " << (*h).first<< "/ si no tiene hermano"<< endl;
        cin >> aux.first;
      } 
    }
    
  }
}
      
 
