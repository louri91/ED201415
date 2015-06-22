/*
 * meteorito.hxx
 *
 * Copyright  (C) Amanda Fernández Piedra
 *
 * defM:: defM, setCode, setMas, setFall, setYear, setLat, setLong, getCodes, getMas, getFall, getYear, getLat, getLong
 * tipos defM::nombreM, defM::meteorito
 *
 */

#include <string>
#include <iostream>
#include "meteorito.h"


//! Clase defM, asociada a la definición de un meteorito
/*! defM::defM .....
 * Descripción contiene toda la información asociada a un meteorito.

 */
using namespace std;


/** 
 @brief constructor primitivo.
 @post definición por defecto.
	*/
    defM::defM(){
    
    }
/**
 @brief constructor de copia
 @param[in] x definición a copiar.
 */
    defM::defM(const defM & x){
        code = x.code;
        mas = x.mas;
        fall = x.fall;
        year = x.year;
        latitud = x.latitud;
        longitud = x.longitud;
        codigos = x.codigos;
    }
/**
 @brief Guarda el código de un meteorito
 @param[in] s cadena de caracteres
 */
void defM::setCode(const string & s){
        code = s;
    }
/**
 @brief Guarda la masa del meteorito
 @param[in] m double
 */
    void defM::setMas(const double &  m){
        mas = m;
    }
/**
 @brief Guarda si el meteorito ha caído o no
 @param[in] f bool
 */
    void defM::setFall(bool f){
        fall = f;
    }
/**
 @brief Guarda el año del meteorito
 @param[in] y string
 */
    void defM::setYear(const string & y){
        year = y;
    }
/**
 @brief Guarda la latitud del meteorito
 @param[in] lat double
 */
    void defM::setLat(double & lat){
        latitud = lat;
    }
/**
 @brief Guarda la longitud del meteorito
 @param[in] long double
 */
    void defM::setLong(double & lon){
        longitud = lon;
    }
/**
 @brief Proporciona los códigos de todos los meteoritos meteorito
 @param[out] vector<string> codigos
 */
    vector<string> defM::getCodes( ){
        return codigos;
    }
/**
 @brief Proporciona la masa del meteorito
 @param[out] mas double
 */
    double defM::getMas( ){
        return mas;
    }
/**
 @brief Proporciona si ha caído o no el meteorito
 @param[out] fall bool
 */
    bool defM::getFall( ){
        return fall;
    }
/**
 @brief Proporciona el año del meteorito
 @param[out] year string
 */
    string defM::getYear( ){
        return year;
    }
/**
 @brief Proporciona la latitud del meteorito
 @param[out] latitud double
 */
    double defM::getLat( ){
        return latitud;
    }
/**
 @brief Proporciona la longitud del meteorito
 @param[out] longitud double
 */
    double defM::getLong( ){
        return longitud;
    }
    /*friend  ostream& defM::operator<< ( ostream& , const defM & ){
        
    }*/

typedef string nombreM;

typedef pair<nombreM,defM> meteorito;

/*ostream & operator<< ( ostream& , const meteorito & ){
    
}*/
