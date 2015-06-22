/*
 * principal.ccp
 *
 * Copyright  (C) Amanda Fernandez Piedra
 *
 *
 *
 *
 ===================================================================================
 Clase principal encargada de cargar el archivo meteorites_all.csv a un diccionario.
 =====================================================================================
 =====================================================================================
 */
#include "diccionario.h"
#include "meteorito.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
 
/** @brief Load
 
 Carga el archivo meteorites_all.csv en el diccionario d en el mismo orden en que los lee.
 En este algoritmo de lectura de archivo utilizamos getline para poder tratar cada línea del fichero por separado. Seguidamente descartamos la línea que contiene los nombres de los campos que se incluyen en el archivo .csv y recorremos línea a línea buscando un separador, que en nuestro caso es ';'
 Para terminar, almacenamos las subcadenas obtenidas en variables del tipo que precisen los objetos que vamos a crear posteriormente.
 Una vez almacenadas todas las cadenas en sus respectivas variables creamos el objeto DefM y junto con la clave nombreM lo insertamos en nuestro diccionario d.
 
 @param[in] string & s ruta del archivo meteorites_all.csv
 @param[in] diccionario & d en el que vamos a copiar los elementos del archivo .csv
 @post  Se modifica el diccionario.
 */
void load(diccionario & d, const string & s){
    string value;
    ifstream fe(s);
    ifstream configFile;
    configFile.exceptions(ifstream::badbit);
    try{
        configFile.open(s.c_str(),ifstream::in);
        //if(configFile.is_open()){
        string line;
            while(getline(configFile,line)){
                if(line=="name;recclass;mass;fall;year;reclat;reclong"){
                }
                else{
                //auxi.push_back(line);
                int nivel=0;
                int inf=0;
                string nombre;
                string code;
                double mas;
                bool fall=false;
                string year;
                double latitud;
                double longitud;
                
                for (int sup=0;sup<line.size();sup++){
                    if (line[sup]==',') {
                        line[sup]='.';
                    }else if(line[sup]==';' || sup==line.size()-1) {
                        if(nivel==0){
                            if(sup-inf==1){
                                nombre = "";
                                inf=sup;

                            }
                            else{
                                nombre = line.substr(inf,sup-inf);
                                inf=sup;
                            }
                            
                            //primero hago substring
                            //segundo guardar la info del sub en nombre
                            //actualizar inferior
                        }
                        if (nivel==1) {
                            if(sup-inf==1){
                                code = "";
                                inf=sup;

                            }
                            else{
                                code = line.substr(inf+1,sup-inf-1);
                                inf=sup;
                            }
                            //guardamos code
                           
                        }
                        if(nivel==2){
                            if(sup-inf==1){
                                mas = 0;
                                inf=sup;

                            }
                            else{
                                string masa;
                                masa = line.substr(inf+1,sup-inf-1);
                                mas = stod(masa);
                                inf=sup;
                            }
                            
                        }
                        if(nivel==3){
                            if(sup-inf==1){
                                fall = false;
                                inf=sup;

                            }
                            else{
                                if(line.substr(inf+1,sup-inf-1)=="Fell"){
                                    fall=true;
                                    inf = sup;
                                }
                                else{
                                    fall=false;
                                    inf = sup;
                                }
                            }
                            
                            
                        }
                        if(nivel==4){
                            if(sup-inf==1){
                                year = "";
                                inf=sup;

                            }
                            else{
                                year = line.substr(inf+1,sup-inf-1);
                                inf = sup;
                            }
                 
                            
                        }
                        if(nivel==5){
                            if(sup-inf==1){
                                latitud = 0;
                                inf=sup;

                            }
                            else{
                                string lati;
                                lati = line.substr(inf+1,sup-inf-1);
                                latitud = stod(lati);
                                inf=sup;
                            }
                            
                        }
                        if(nivel==6){
                            if(sup-inf==1){
                                longitud=0;
                                //inf=sup;

                            }
                            else{
                                string lon;
                                lon = line.substr(inf+1,line.size()-1);
                                longitud = stod(lon);
                                //inf=sup;
                            }
                            
                        }
                        
                        nivel++;

                        
                    }
                }

                    nombreM miNombre = nombre;
                    defM miDef;
                    miDef.setCode(code);
                    miDef.setMas(mas);
                    miDef.setFall(fall);
                    miDef.setYear(year);
                    miDef.setLat(latitud);
                    miDef.setLong(longitud);
                    
                    
                    
                d.insert(make_pair(miNombre, miDef));
                }
            }
            configFile.close();
        }
        
    
    catch(ifstream::failure e){
        throw e;
    }
    

    

}

int main()
{
    clock_t t_inicio, t_final;
    double secs;
    diccionario lectura;
    load(lectura, "/Users/Louri/Desktop/PRACTICASUGR/ED/P2EDFINAL/P2EDFINAL/meteorites_all.csv");
    diccionario Meteoritos(lectura);

    
    pair<diccionario::entrada, bool> meteoritoBusqueda;
    t_inicio=clock();
    meteoritoBusqueda = lectura.find("Zubkovsky");
    t_final=clock();
    secs = (double)(t_final-t_inicio)/CLOCKS_PER_SEC;
    //secs = secs*1000;
    cout << secs;


   return 0;
}
