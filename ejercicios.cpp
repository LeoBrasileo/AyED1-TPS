#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
//tiempoTotal es O(n) porque tiene solo un ciclo y en el peor caso la ejecucion va hacer un polinomio lineal de operaciones elementales
tiempo tiempoTotal(viaje v) {
    tiempo t;
    tiempo maxTiempo = 0;
    tiempo minTiempo = obtenerTiempo(v[0]);

    for (int i = 0; i < v.size(); i++){
        tiempo actual = obtenerTiempo(v[i]);
        maxTiempo = actual > maxTiempo ? actual : maxTiempo;
        minTiempo = actual < minTiempo ? actual : minTiempo;
    }

    t = maxTiempo - minTiempo;

    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
//distanciaTotal es O(n^2) porque tiene 2 ciclos anidados (uno adentro del otro) en ordenarViaje(v) y despues hace un ciclo mas
//por lo que la complejitud en el peor caso seria O(n^2 + n) que es lo mismo que O(n^2)
distancia distanciaTotal(viaje v) {
    distancia d = 0;

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
    for (int i = 0; i < v.size() - 1 && !resp; i++){
        double velocidadAct = velocidad(v[i], v[i+1]);
        resp = (velocidadAct > 80);
    }

    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
//recorridoNoCubierto es O(n * m) porque el algoritmo hace una iteracion de r y por cada elemento de r una iteracion de v en puntoCubierto(p,v,u)
//por lo que hay m * n iteraciones totales en el peor caso O(n * m)
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
    double anchoCelda = abs((obtenerLongitud(esq2) - obtenerLongitud(esq1))/m);
    double altoCelda = abs((obtenerLatitud(esq1) - obtenerLatitud(esq2))/n);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            gps nuevaEsq1 = {obtenerLatitud(esq1) - (i * altoCelda), obtenerLongitud(esq1) + j * anchoCelda};
            gps nuevaEsq2 = {(obtenerLatitud(esq1) - altoCelda) - i * altoCelda, (obtenerLongitud(esq1) + anchoCelda) + j * anchoCelda};
            nombre nuevoNombre = {i+1,j+1};
            celda c = {nuevaEsq1, nuevaEsq2, nuevoNombre};
            resp.push_back(c);
        }
    }

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp = 0;
    ordenarViaje(v);

    vector<nombre> nombresViaje = puntosDeViajeEnGrilla(v,g);
    int cantNombres = nombresViaje.size();
    for (int i = 0; i < (cantNombres - 1); i++){
        nombre n1 = nombresViaje[i];
        nombre n2 = nombresViaje[i+1];
        if(distanciaEntreViajes(n1, n2) > 1){
            resp++;
        }
    }
    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    for (int i = 0; i < v.size(); i++){
        tiempo puntoT = obtenerTiempo(v[i]);
        if (puntoEnErrores(puntoT, errores)){
            //en el punto i de viaje hay un error
            vector<int> puntosCercanosValidos = obtenerPuntosCercanosValidos(v, i, errores);
            int n = puntosCercanosValidos[0], m = puntosCercanosValidos[1];

            tiempo tRecta = obtenerTiempo(v[m]) - obtenerTiempo(v[n]);
            double rectaLat = obtenerLatitud(obtenerPosicion(v[m])) - obtenerLatitud(obtenerPosicion(v[n]));
            double rectaLon = obtenerLongitud(obtenerPosicion(v[m])) - obtenerLongitud(obtenerPosicion(v[n]));
            double velLat = rectaLat / tRecta; //velocidad de latitud por seg en los puntos validos
            double velLon = rectaLon / tRecta;

            tiempo tdif = obtenerTiempo(v[i]) - obtenerTiempo(v[n]);
            double latCorregido = obtenerLatitud(obtenerPosicion(v[n])) + (velLat * tdif);
            double longCorregido = obtenerLongitud(obtenerPosicion(v[n])) + (velLon * tdif);
            gps corregido = puntoGps(latCorregido, longCorregido);

            get<1>(v[i]) = corregido;
        }
    }

    return;
}