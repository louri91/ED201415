/*
 * meteorito.h
 *
 * Copyright  (C) Amanda Fernández Piedra
 *
 * defM:: defM, setCode, setMas, setFall, setYear, setLat, setLong, getCodes, getMas, getFall, getYear, getLat, getLong
 * tipos defM::nombreM, defM::meteorito
 *
 */
#ifndef __METEORITO_H
#define __METEORITO_H

#include <string>
#include <iostream>

//! Clase defM, asociada a la definición de un meteorito
/*! defM::defM .....
 * Descripción contiene toda la información asociada a un meteorito.
 
 @todo Implementa esta clase, junto con su documentación asociada
 
 */
using namespace std;

class defM {
    
public:

    defM();
    defM(const defM & x);
    void setCode(const string & s);
    void setMas(const double &  m);
    void setFall(bool f);
    void setYear(const string & y);
    void setLat(double & lat);
    void setLong(double & lon);
    vector<string> getCodes( );
    double getMas( );
    bool getFall( );
    string getYear( );
    double getLat( );
    double getLong( );
private:
    friend  ostream& operator<< ( ostream& , const defM & );
    string code;
    double mas;
    bool fall;
    string year;
    double latitud;
    double longitud;
    vector<string> codigos;
};


typedef string nombreM;

typedef pair<nombreM,defM> meteorito;

ostream & operator<< ( ostream& , const meteorito & );

#include "meteorito.hxx"
#endif
