#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo t;

    v = ordenarViaje(v);
    t = obtenerTiempo(v[v.size()-1]) - obtenerTiempo(v[0]);

    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    distancia d;

    v = ordenarViaje(v);
    for (int i = 0; i < v.size() - 1; i++){
        gps pos1 = obtenerPosicion(v[i]);
        gps pos2 = obtenerPosicion(v[i+1]);
        double distActual = distEnKM(pos1,pos2);
        d = d + distActual;
    }

    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    bool resp = false;

    v = ordenarViaje(v);
    for (int i = 0; i < v.size() - 1; i++){
        double velocidadAct = velocidad(v[i], v[i+1]);
        resp = (velocidadAct > 80);
    }

    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;

    for (int i = 0; i < r.size(); i++){
        gps puntoDelRecorrido = r[i];
        if (!puntoCubierto(puntoDelRecorrido, v, u)){
            resp.push_back(puntoDelRecorrido);
        }
    }

    return resp;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;

    for (int i = 0; i < f.size(); i++){
        viaje v = f[i];
        if (viajeEnFranja(v,t0,tf)){
            resp++;
        }
    }

    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    // codigo

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp;
    // codigo

    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig

    return;
}