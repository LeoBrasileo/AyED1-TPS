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

    ordenarViaje(v);
    t = obtenerTiempo(v[v.size()-1]) - obtenerTiempo(v[0]);

    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    distancia d;

    ordenarViaje(v);
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

    ordenarViaje(v);
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
    double longCelda = abs((obtenerLongitud(esq1) - obtenerLongitud(esq2))/n);
    double latCelda = abs((obtenerLatitud(esq2) - obtenerLatitud(esq1))/m);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            gps nuevaEsq1 = {obtenerLatitud(esq1) + (i * latCelda), obtenerLongitud(esq1) + (j * longCelda)};
            gps nuevaEsq2 = {obtenerLatitud(esq1) + latCelda, obtenerLongitud(esq1) + longCelda};
            nuevaEsq2 = {obtenerLatitud(nuevaEsq2) + (i * latCelda), obtenerLongitud(nuevaEsq2) + (j * longCelda)};
            nombre nuevoNombre = {i+1,j+1};
            celda c = {nuevaEsq1, nuevaEsq2, nuevoNombre};
            resp.push_back(c);
        }
    }

    guardarGrillaEnArchivo(resp, "prueba.csv");
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