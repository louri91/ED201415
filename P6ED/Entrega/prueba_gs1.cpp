#include <iostream>
#include <set>
#include <unordered_set>
#include <iostream>
#include "gs1Set.h"
#include <fstream>

/** @brief Carga el fichero en memoria
 * @param contenedor contenedor de salida
 * @param s nombre del fichero 
 * @pre T debe tener el método insert(const string &)
 */
template <typename T>
void load(T  &  contenedor, const string & s) {
 ifstream fe;
 string cadena;
 cout << "Abrimos "<< s << endl;
 fe.open(s.c_str(), ifstream::in);
 if (fe.fail())    
 {
   cerr << "Error al abrir el fichero " << s << endl;
 } else {

    while ( !fe.eof() )
      { getline(fe,cadena,'\n');
       	if (!fe.eof()) {
	   cout << "leo:: "<< cadena << endl;
	   
	   contenedor.insert(cadena);
         }
     }
   
    } // else
  fe.close();
 }
 
 
 int main(int argc, char *argv[]){
  
   if (argc !=2) {
     cout << "formato: nombre_ejecutable datos.txt" << endl;
     exit(1);
   }
   
   string nfichero = string(argv[1]);
   set<string> s;
   unordered_set<string> us_codigo;
   gs1Set gs1;
   /* Insercion de elementos en los tres ficheros */
   
   load(us_codigo,nfichero);
   load(s,nfichero);
   load(gs1,nfichero);
   
   gs1.print();
   
 }
   