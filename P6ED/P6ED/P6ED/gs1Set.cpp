#include "gs1Set.h"
#include <vector>

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

bool gs1Set ::insert(const string& s){
    tree<pair<string,int> >::node n = arbol.root();
    string::const_iterator it, it_aux;
    pair<string,int> par;
    string cadena_actual = "";
    bool insertar = false;
    
    
    if(find(s) == end()){
        for (it = s.begin(); it!=s.end(); ++it) {
            it_aux = it;
            ++it_aux;
            
            if((*it) == '('){
                string cod = "";
                while((*it) != ')'){
                    cod.push_back(*it);
                    ++it;
                }
                cod.push_back(*it);
                cadena_actual += cod;

                if(find(cadena_actual) == end()){
                    par.first = cod;
                    par.second = -1;
                    if(!n.left().null())
                        n = arbol.insert_right_sibling(n,par);
                    else
                        n = arbol.insert_left(n,par);
                    
                    tama++;
                }
            }
            else if((*it_aux) == '('){
                cadena_actual += string(1,*it);
                if(find(cadena_actual) == end()){
                    par.first = string(1,*it);
                    par.second = 1;
                    n = arbol.insert_left(n,par);
                    tama++;
                }
            }
            else if((*it) >= '0' && (*it) <= '9'){
                cadena_actual += string(1,*it);
                if(find(cadena_actual) == end()){
                    par.first = string(1,*it);
                    if(it == s.end() -1)
                        par.second = 1;
                    else
                        par.second = 0;
                    n = arbol.insert_left(n,par);
                    tama++;
                }
            }
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
        cout << (*itn).first << " --- " << (*itn).second << endl;
    
}


/**
 @todo implementar este metodo correctamente
 OJO ESTE METODO OS SIRVE PARA PODER CONSTRUIR UN ARBOL
 NO TIENE EN CUENTA EL INVARIANTE DE LA REPRESENTACION
 AL NO CONSIDERAR EL CAMPO INT DEL NODO!!!!!
 DEBEIS MODIFICARLO PARA QUE LO HAGA DE FORMA CORRECTA
 */

void gs1Set ::reading_gs1Set ( ) {
    
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


/** @brief busca un codigo
 @param[in] s nombre del codigo a buscar
 @return un iterador que apunta al codigo o end() si el codigo no existe.
 */
gs1Set ::const_iterator gs1Set ::find(const string & s){
    
    string s_aux = s;
    tree<pair<string,int> >::node n = arbol.root();
    string::const_iterator it = s.begin();
    gs1Set::const_iterator iterador_code = begin();
    bool encontrado = true;
    bool avanzar = false;
    
    if(!n.left().null())
        n = n.left();
    
    while((!n.null() && encontrado) && it != s.end()){
        string cod = "";
        if((*it) == '('){
            while((*it) != ')'){
                cod.push_back(*it);
                ++it;
            }
            cod.push_back(*it);
        }
        else
            cod = (*it);
        
        avanzar = false;
        if(!n.null()){
            if(cod == (*n).first){
                avanzar = true;
                ++it;
                if(!n.left().null())
                    n = n.left();
            }
        }

        while(!avanzar){
            cout << "Compara " << (*n).first << " con " << cod  << endl;
            if(n.next_sibling().null()){
                encontrado = false;
                avanzar = true;
            }
            else{
                n = n.next_sibling();
                if(cod == (*n).first){
                    avanzar = true;
                    ++it;
                    n = n.left();
                }
            }
        }
    }
    
    if(encontrado)
        iterador_code.act = n;
    else
        iterador_code = end();
    
    
    return iterador_code;
    
}

gs1Set::size_type gs1Set::size() const{
    return tama;
}

bool gs1Set::empty() const{
    
    bool vacio = true;
    
    if(size() != 0)
        vacio = false;
    
    return vacio;
    
}

gs1Set::const_iterator gs1Set::begin() const{
    
    tree<pair<string,int> >::node n = arbol.root();
    gs1Set::const_iterator it;
    
    while(!n.left().null())
        n = n.left();
    
    it.act = n;
    it.ptr = this;
    
    return it;
    
}

gs1Set::const_iterator gs1Set::end() const{
    
    tree<pair<string,int> >::node n = arbol.root();
    gs1Set::const_iterator it;
    
    while(!n.next_sibling().null() || !n.left().null()){
        if(!n.next_sibling().null())
            n = n.next_sibling();
        else if(!n.left().null())
            n = n.left();
    }
    
    it.act = n;
    it.ptr = this;
    
    return it;
}


//Constructor por defecto
gs1Set::const_iterator::const_iterator(){
    
}

//Constructor de copia
gs1Set::const_iterator::const_iterator(const const_iterator & it){
    if(this != &it){
        act = it.act;
        ptr = it.ptr;
    }
}

string  gs1Set::const_iterator::operator*(){
    
    string cod = "";
    
    while(act != (*ptr).arbol.root()){
        cod.insert(0, (*act).first);
        act = act.parent();
    }
    
    return cod;
}

gs1Set::const_iterator & gs1Set::const_iterator::operator++(){
    
    tree<pair<string,int> >::node n = act;
    bool parar = false;
    
    while(!parar){
        if(!n.left().null() && !n.left().next_sibling().null())
            parar = true;
        else if(!n.left().null()){
            act = n.left();
            n = n.left();
        }
        else
            parar = true;
    }
    
    return *this;
}

gs1Set::const_iterator gs1Set::const_iterator::operator++(int){
    
    tree<pair<string,int> >::node n = act;
    bool parar = false;
    
    while(!parar){
        if(!n.left().null() && !n.left().next_sibling().null())
            parar = true;
        else if(!n.left().null()){
            act = n.left();
            n = n.left();
        }
        else
            parar = true;
    }
    
    return *this;
}

gs1Set::const_iterator & gs1Set::const_iterator::upper_IA(){
    
    tree<pair<string,int> >::node n = act;
    
    if((*act).second == -1)
        n = n.parent();
    if(n != (*ptr).arbol.root()){
        while((*n).second != -1){
            n = n.parent();
        }
        act = n;
    }
    else
        act = n.left();
    
    
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
    
    bool res = false;
    
    if((act == it.act) && (ptr == it.ptr))
        res = true;
    
    return res;
}

bool gs1Set::const_iterator::operator!=(const const_iterator & it) const{
    
    bool res = true;
    
    if((*this == it))
        res = false;
    
    return res;
}