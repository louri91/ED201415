#include "gs1Set.h"
#include <string>
 
using namespace std;
 
 
gs1Set::gs1Set (){
  pair<string,int> aux("gs1",0);
  arbol = tree<pair<string,int>>(aux);
  tama = 0;
}
 
gs1Set::gs1Set (const gs1Set  & x){
  arbol = x.arbol;
  tama = x.tama;
}
 
 
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
      if(aux.first[0] == '(')
         aux.second = -1;
      else
         aux.second = 1;
      h= arbol.insert_left(n,aux);
      Q.push(h);
      cout << "Hermano Dhc de " << (*h).first<< "/ si no tiene hermano "<< endl;
      cin >> aux.first;
      while (aux.first != "/") {
         if(aux.first[0] == '(')
            aux.second = -1;
         else
            aux.second = 1;
         h= arbol.insert_right_sibling(h,aux);
         Q.push(h);
         cout << "Hermano Dhc de " << (*h).first<< "/ si no tiene hermano"<< endl;
         cin >> aux.first;
      }
    }
   
  }
}
 
gs1Set & gs1Set::operator = (const gs1Set & org){
 
  if(this != &org){
    arbol = org.arbol;
    tama = org.tama;
  }
 
  return *this;
}
 
string gs1Set::find_sub(string::const_iterator it) {
 
   string code;
 
   if(*it == '('){
      for(it; *it != ')'; it++){
         code.push_back(*it);
      }
      code.push_back(')');
   }
 
   else
      code = "";
 
   return code;
}
 
pair<string, int> gs1Set::siguiente_dato(string::const_iterator & it) {
 
  pair<string, int> dato;
 
  if(*it == '(') {
    dato.first = find_sub(it);
    dato.second = -1;
    it += 4;
  }
  else {
    dato.first = *it;
    dato.second = 1;
    it++;
  }
 
  return dato;
}
 
int gs1Set::contador_subcodigo(string s){
 
  int total = 0;
  string::const_iterator it;
 
  it = s.begin();
 
  while(it != s.end()){
    if(find_sub(it) != "")
      it+=4;
    else
      ++it;
    ++total;
  }
 
  return total;
}
 
bool gs1Set ::insert(const string& s){
 
   tree<pair<string,int> >::node n, aux, siguiente;
   string::const_iterator it(s.begin()), it_ultimo(s.end()-1);
   bool enc, insertado;
   pair<string,int> dato;
   //string info;
   //int tipo; // Tipo de nodo
   
   n = arbol.root();
   //insertado = (find(s) != end());
   insertado = true;
   //if(!insertado){
 
      while(it != s.end()){
 
         aux = n.left(); // aux es el primer hijo del nodo raiz actual
         enc = false;
         //Si es el último dato del código, el entero asociado es el total de subcódigos
         if(it == it_ultimo){
          dato.first = *it;
          dato.second = contador_subcodigo(s);
          ++it;
         }
         else
          dato = siguiente_dato(it); //guardamos los datos del siguiente nodo
 
         //Si el árbol está vacío o el nodo va antes que el actual
         if(aux.null() || (*aux).first > dato.first) {
            n = arbol.insert_left(n, dato);
            insertado = false;
         }
         //Si no está vacío
         else {
            while(!enc) {
 
               if(dato.first == (*aux).first) {
                  // El nodo ya existe
                  n = aux;
                  enc = true;
               }
               else {
                  siguiente = aux.next_sibling();
                  if(siguiente.null() || dato.first < (*siguiente).first) {
                     // Fin del árbol o el siguiente es mayor
                     n = arbol.insert_right_sibling(aux, dato);
                     insertado = false;
                     enc = true;
                  }
                  else {
                     // Continúo buscando
                     aux = siguiente;
                  }
               }
            }
         }
      }
   //}
  tama++;
 
  return !insertado;
}
 
int gs1Set::erase(const string & s){
 
   tree<pair<string,int> >::node n, aux;
   string::const_iterator it_s;
   int borrados = 0;
   pair<string,int> aux2;
   bool enc = false;
   bool es_prefijo;
 
   //Comprobamos si un prefijo o un código
   if(s.length() == 4)
      es_prefijo = true;
   else
      es_prefijo = false;
   
   if(!es_prefijo && (find(s)) != end()){
 
      n = aux;
      while(n != arbol.root()){
         n = aux.parent();
         aux.remove();
         aux = n;
      }
 
      borrados = 1;
   }
 
   else if (es_prefijo){
      //Buscamos en que nodo esta el prefijo
      n = arbol.root();
      aux = n.left();
 
      while(!aux.null() && !enc){
         if(s == (*aux).first)
            enc = true;
         else
            aux = aux.next_sibling();
      }
 
      //Si el subcódigo está
      if(enc){
         //Creamos un subarbol
         tree<pair<string,int>> arbol_aux;
         arbol_aux.assign_subtree(arbol,aux);
         borrados = arbol_aux.size();
 
         //Podamos el árbol
         arbol.prune_left(aux,arbol_aux);
      }
   }
   
   tama -= borrados;
   return borrados;
}
 
gs1Set::const_iterator gs1Set::find(const string & s){
 
  tree<pair<string,int> >::node n, aux, ant;
  string::const_iterator it_s(s.begin());
  gs1Set::const_iterator it;
  bool enc = true;
  bool coincide = false;
  //int tipo;
  //string info;
  pair<string,int> dato;
 
  n = arbol.root();
  aux = n.left(); // aux es el primer hijo
  ant = aux;
 
  while(it_s != s.end() && enc){  
      dato = siguiente_dato(it_s);
      while(!aux.null() && !coincide){
         if(dato.first == (*aux).first){
            n = aux; //Pasamos al siguiente nivel
            coincide = true;
         }
         else{
            aux = aux.next_sibling();
            if(!aux.null())
               ant = aux;
         }
      }
 
      if (!coincide)
         enc = false;
      else{
         aux = n.left();
         coincide = false;
      }
   }
 
   if(enc){
      it.act = ant.left();
      it.ptr = this;
   }
   else
      it = end();
   
  return it;
}
 
list<string> gs1Set::codesWithPrefix(const string & pr){
 
   list<string> salida;
   tree<pair<string,int> >::node n, aux, sig, raiz_codigo;
   string codigo, c_comun;
   
   bool enc = false;
   n = arbol.root();
   aux = n.left(); // aux es el primer hijo
 
  //Buscamos el subcódigo
  while(!aux.null() && !enc){
      if(pr==(*aux).first)
         enc = true;
      else
        aux = aux.next_sibling();
   }
 
   //Si está, buscamos los códigos
   if(enc){
      sig = aux.next_sibling();
      raiz_codigo = aux;
      tree<pair<string,int> >::const_preorderiterator it(raiz_codigo);
 
      c_comun+=pr;
 
      //Si aux no tiene hermanos, los codigos comparten ese digito
      while(!aux.next_sibling().null()){
        aux = aux.left(); //bajamos un nivel
        c_comun+=(*aux).first;
      }
 
      //Recorremos solo una rama, la que tiene como raíz el nodo del código
      while((*it) != (*sig)){
         //aux pasa a ser el siguiente hermano del hijo del subarbol a recorrer
         //mientras tenga hermanos
         if(!aux.next_sibling().null())
          aux = aux.next_sibling();
 
         //recorremos los nodos que cuelgan de los hijos
         for(it; (*it).second <=1; ++it)
            codigo+=(*it).first;
 
         //Añadimos el ultimo nodo del subcódigo
         codigo+=(*it).first;
         ++it;
 
         //insertamos el código en la lista
         salida.push_back(codigo);
 
         //Nos aseguramos de que el codigo comun permanece
         codigo=c_comun;
      }
   }
 
   return salida;
}
 
gs1Set::size_type gs1Set::size() const{
  return tama;
}
 
bool gs1Set::empty() const{
  return arbol.empty();
}
 
void gs1Set::print() const {
  tree<pair<string,int> >::const_preorderiterator it;
  tree<pair<string,int> >::const_leveliterator itn;
   cout << "preorden " << endl;
   
  for (it= arbol.beginPreorder(); it!= arbol.endPreorder();++it)
    cout << (*it).first << endl;
 
   cout << "Nivel " << endl;
  for (itn= arbol.beginlevel(); itn!= arbol.endlevel();++itn)
    cout << (*itn).first << endl;
 
}
 
gs1Set::const_iterator gs1Set::begin() const{
 
  gs1Set::const_iterator it;
 
  it.act = arbol.root();
  it.ptr = this;
 
  return it;
}
   
 
gs1Set::const_iterator gs1Set::end() const{
 
  gs1Set::const_iterator it;
  tree<pair<string,int> >::node n;
 
  it.act = n;
  it.ptr = this;
 
  return it;
}
 
gs1Set::const_iterator::const_iterator(){
 
  ptr = NULL;
}
 
gs1Set::const_iterator::const_iterator(const gs1Set::const_iterator & it){
 
  act = it.act;
  ptr = it.ptr;
}
 
string gs1Set::const_iterator::operator*(){
 
  //list<string> codes;
  string salida;
  tree<pair<string, int> >::node aux, n;
  n = (*ptr).arbol.root();
  aux = act;
 
  while(aux != n){
    salida = (*aux).first + salida;
    aux = aux.parent();
  }
  return salida;
}
 
gs1Set::const_iterator & gs1Set::const_iterator::operator++(){
 
  while((*act).second < 0){
 
    act = act.left();
  }
 
  return *this;
}
 
gs1Set::const_iterator gs1Set::const_iterator::operator++(int){
 
  gs1Set::const_iterator aux(*this);
 
  while((*act).second < 0){
 
    act = act.left();
  }
 
  return aux;
}
 
gs1Set::const_iterator & gs1Set::const_iterator::upper_IA(){
 
  while((*act).second > 0){
 
    act = act.parent();
  }
 
  return *this;
}  
 
gs1Set::const_iterator & gs1Set::const_iterator::operator=(const const_iterator & it){
 
  if(this != &it){
 
    act = it.act;
    ptr = it.ptr;
  }
 
  return *this;
}
 
bool gs1Set::const_iterator::operator==(const const_iterator & it) const{
 
  return ((act == it.act) && (ptr == it.ptr));
}
 
bool gs1Set::const_iterator::operator!=(const const_iterator & it) const{
 
  return !(*this == it);
}
 
bool gs1Set::cheq_rep(){
 
  tree<pair<string,int> >::preorderiterator it(arbol.root());
  ++it;
  for(it; it!= arbol.endPreorder();++it){
      if((((*it).first.at(0) == '(') && ((*it).second > 0)) || (((*it).first.at(0) != '(') && ((*it).second) < 0))
         return false;
  }
  return true;
}