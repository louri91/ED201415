/*
 * diccionarioV2.hxx
 *
 * Copyright  (C) Amanda Fernández Piedra
 *
 * diccionario:: diccionario, end, find, operator[], size, max_element
 * tipos diccionario::entrada, diccionario::size_type
 *
 *
 ===================================================================================
 Funcion de Abstraccion:
 DiccionarioV2.hxx
 =====================================================================================
 Invariante de la Representación:
 
 DiccionarioV2.hxx
 =====================================================================================
 */
#include <assert.h>
#include "diccionario.h"
#include <vector>
#include <utility>
#include "meteorito.h"
#include <time.h>

using namespace std;



/** @brief Método constructor por defecto
 Se crea un diccionario vacío.
 @post Se modifica el diccionario
 */

template <typename clave, typename definicion>

diccionario<clave,definicion>::diccionario(){
    dic.clear();
}

/** @brief Método constructor

 Crea una copia del diccionario que nos facilitan ordenándolo de menor a mayor mediante el método de ordenación por burbuja.
 @param[in] diccionario & d referencia a un diccionario
 @post Se modifica el diccionario
 
 */

template <typename clave, typename definicion>

diccionario<clave,definicion>::diccionario (const diccionario<clave,definicion> & d){
    dic = d.dic;
    for(int i=0;i<dic.size()-1;i++){
        for (int j=i+1;j<dic.size(); j++) {
         
            if(dic[i].first>(dic[j].first)){
                swap(dic[i], dic[j]);
            }
        }
        
    }
    
}

/** @brief Método buscar
 Busca un meteorito en el diccionario
 @param[in] const nombreM & s referencia a una cadena constante a buscar
 @return una copia de la entrada en el diccionario en caso de encontrarla. En caso de no encontrarla, devuelve la entrada con la definición por defecto.
 @post no modifica el diccionario
 */
template <typename clave, typename definicion>

/* pair<diccionario::entrada,bool> diccionario<clave,definicion>::find( const clave & s) const{
*/
pair<pair<clave,definicion>,bool> diccionario <clave,definicion>::find( const clave & s) const{
    pair <diccionario::entrada,bool> encontrado,noencontrado;
    pair <clave,definicion> pepe;
    int central;
    int b=0;
    int alto =dic.size()-1;
    clave valorCentral;
    
    
    while (b<=alto){
        central = (b+alto)/2;
        valorCentral = dic[central].first;
        if(s == valorCentral){
            encontrado.first = dic[central];
            encontrado.second = true;
            return encontrado;
            cout << "ENCONTRADO";
        }
        else if(s <valorCentral){
            alto = central-1;
        }
        else{
            b = central+1;
        }
        
    }
    noencontrado.first = pepe;
    noencontrado.second = false;
    return noencontrado;
    cout << "NO ENCONTRADO";
}

/** @brief Consulta/Inserta una entrada en el diccionario
 
 Busca la cadena s en el diccionario, si la encuentra devuelve una referencia a la definición de la misma. En caso contrario, la inserta, con una definición por defecto, devolviendo la referencia a este valor.
 @param[in] const nombreM & s referencia a una cadena constante a consultar
 @param[out] defM & referencia a la definición asociada a la entrada, nos permite modificar la definición.
 @post si s no está en el diccionario el size() se incrementa en 1.
 
 */
template <typename clave, typename definicion>

definicion & diccionario<clave,definicion>::operator[](const clave & s) {
    pair<diccionario::entrada,bool> encontrado1;
    encontrado1 = find(s);
    
    if(encontrado1.second==true){
        return encontrado1.first.second;
    }
    else{
        pair<nombreM,defM> aux;
        defM pepito1;
        aux = make_pair(s, pepito1);
        dic.push_back(aux);
        return aux.second;
    }
}


/** @brief Consulta una entrada en el diccionario
 
 Busca la cadena s en el diccionario, si la encuentra devuelve una referencia constante a la definición de la misma. En caso contrario, lanza un mensaje de error.
 @param[in] const nombreM & s referencia a una cadena constante a consultar
 @param[out] int & referencia constante a la definición asociada a la entrada.
 @post no se modifica el diccionario
 */

template <typename clave, typename definicion>

const definicion & diccionario<clave,definicion>::operator[](const clave & s) const{
    
    pair<diccionario::entrada,bool> encontrado,pepe;
    encontrado = find(s);
    
    if(encontrado.second==true){
        return encontrado.first.second;
    }
    else{
        cout << "ERROR: Meteorito no encontrado";
        pepe.second = false;
        return pepe.second;
    }
}


/** @brief Inserta una entrada en el diccionario
 Para insertar una entrada en nuestro diccionario de meteoritos primero llama a la función buscar para que, en caso de que ya se encuentre un meteorito con la misma clave, no lo inserte sino que lo descarte.
 @param e entrada a insertar
 @return true si la entrada se ha podido insertar con éxito, esto es, no existe un meteorito con igual nombre en el diccionario. False en caso contrario
 @post 	 Si e no esta en el diccionario, el size() sera incrementado en 1.
 */

template <typename clave, typename definicion>

bool diccionario<clave,definicion>::insert(const diccionario::entrada & e){
    if(find(e.first).second==true){
        return false;
    }
    else{
        dic.push_back(e);
        return true;
    }
}

/** @brief operador de asignación
 @param[in] org diccionario  a copiar.
 Crea un diccionario duplicado exacto de org.
 */

template <typename clave, typename definicion>

diccionario<clave,definicion> & diccionario<clave,definicion>::operator=( const diccionario & org){
    
    diccionario aux;
    aux.dic = org.dic;
    return aux;
}

/** @brief numero de entradas en el diccionario
 @post  No se modifica el diccionario.
 */

template <typename clave, typename definicion>

int diccionario<clave,definicion>::size() const {
    return dic.size();
}

/** @brief vacia
 Chequea si el diccionario esta vacio (size()==0)
 */

template <typename clave, typename definicion>

bool diccionario<clave,definicion>::empty() const{
    if(dic.size()==0) return true;
    else return false;
}


/** @brief Chequea el Invariante de la representacion
 @return true si el invariante es correcto, falso en caso contrario
 */

template <typename clave, typename definicion>

bool diccionario<clave,definicion>::cheq_rep( ) const {
    for(int i=0;i<dic.size();i++){
        for(int j=i+1;j<dic.size();j++){
            if(dic[i].first==dic[j].first) return false;
        }
    }
    return true;
}

/**
 @todo implementa esta función
 */
template <typename clave, typename definicion>

ostream &  operator << ( ostream & sal, const diccionario<clave,definicion> & D){
    
}

