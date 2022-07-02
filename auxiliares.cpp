#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}
double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo){
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < g.size(); i++){
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo){
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < recorridos.size(); i++){
        for(int k = 0; k < recorridos[i].size(); k++){
            lat= get<0>(recorridos[i][k]);
            lng= get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}

void ordenarViaje(viaje &v) {
    int n = v.size();

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (obtenerTiempo(v[j]) > obtenerTiempo(v[j+1])){
                swap(v[j], v[j + 1]);
            }
        }
    }
}

bool puntoCubierto(gps p, viaje v, distancia u) {
    bool res = false;
    for (int i = 0; i < v.size() && !res; i++){
        gps puntoDelViaje = obtenerPosicion(v[i]);
        double dist = distEnKM(puntoDelViaje, p);
        res = dist < u;
    }
    return res;
}

double velocidad(tuple<tiempo, gps> p1, tuple<tiempo, gps> p2){
    double dist = distEnKM(obtenerPosicion(p1), obtenerPosicion(p2));
    double tiempoOcurrido = obtenerTiempo(p2) - obtenerTiempo(p1);
    float res = dist / (tiempoOcurrido/3600); //guardamos en float asi no tenemos errores con decimales no deseados
    return res;
}

bool viajeEnFranja(viaje v, double t0, double tf){
    bool franja = false;
    bool min = false;
    bool max = false;
    for(int i = 0; i < v.size(); i++){
        double ti = obtenerTiempo(v[i]);
        if (t0 <= ti && tf >= ti){
            franja = true;
        }
        if (ti <= t0){
            min = true;
        }
        if (ti >= tf){
            max = true;
        }
    }

    bool res = (franja || (max && min));
    return res;
}

vector<nombre> puntosDeViajeEnGrilla(viaje v, grilla g){
    vector<nombre> ptsViajeGrilla;
    for(int i = 0; i < v.size(); i++){
        bool enRangoDeLong = false;
        bool enRangoDeLat = false;
        double latPunto = obtenerLatitud(obtenerPosicion(v[i]));
        double longPunto = obtenerLongitud(obtenerPosicion(v[i]));
        for(int j = 0; j < g.size() && !(enRangoDeLong && enRangoDeLat); j++){
            double latCelda0 = obtenerLatitud(get<0>(g[j]));
            double latCelda1 = obtenerLatitud(get<1>(g[j]));
            double lonCelda0 = obtenerLongitud(get<0>(g[j]));
            double lonCelda1 = obtenerLongitud(get<1>(g[j]));
            enRangoDeLat = (latPunto <= latCelda0 && latPunto > latCelda1);
            enRangoDeLong = (longPunto >= lonCelda0 && longPunto < lonCelda1);
            if(enRangoDeLat && enRangoDeLong){
                ptsViajeGrilla.push_back(get<2>(g[j]));
            }
        }
    }
    return ptsViajeGrilla;
}

int distanciaEntreViajes(nombre n1, nombre n2){
    int nombre1Lat = get<0>(n1);
    int nombre1Lon = get<1>(n1);
    int nombre2Lat = get<0>(n2);
    int nombre2Lon = get<1>(n2);
    int cuentaLat = pow((nombre1Lat - nombre2Lat),2);
    int cuentaLon = pow((nombre1Lon - nombre2Lon),2);
    int res = sqrt(cuentaLat + cuentaLon);
    return res;
}

bool puntoEnErrores (tiempo t, vector<tiempo> errores){
    int i = 0;
    while (i < errores.size() && errores[i] != t){ //busqueda lineal
        i++;
    }

    return i < errores.size();
}
bool indiceEnCercanos (int indice, vector<int> s){
    int i = 0;
    while (i < s.size() && s[i] != indice){
        i++;
    }

    return i < s.size();
}

tiempo maxTiempo (viaje v){
    tiempo res = obtenerTiempo(v[0]);
    for (int i = 1; i < v.size(); i++){
        if ((obtenerTiempo(v[i]) > res)){
            res = obtenerTiempo(v[i]);
        }
    }
    return res;
}

//esto siempre va a devolver los 2 indices de los puntos correctos mas cercanos
vector<int> obtenerPuntosCercanosValidos(viaje v, int inicial, vector<tiempo> errores) {
    vector<int> res = {};
    tiempo ttemp;
    int temp, j;
    while (res.size() < 2){
        int k = inicial;
        tiempo tdif = maxTiempo(v);
        tiempo tactual = obtenerTiempo(v[inicial]);
        for (int i = 0; i < v.size(); i++){
            tiempo ti = obtenerTiempo(v[i]);
            double tdifAct = abs(tactual - ti);
            if (tdifAct < tdif && !puntoEnErrores(ti, errores) && !indiceEnCercanos(i, res)){
                tdif = tdifAct;
                k = i;
            }
        }
        res.push_back(k);
    }
    //ordenar por tiempo (adelante los puntos que ocurrieron antes)
    for(int i = 1; i < res.size(); i++) {
        ttemp = obtenerTiempo(v[res[i]]);
        temp = res[i];
        j = i;
        while(j > 0 && obtenerTiempo(v[res[j-1]]) > ttemp) {
            res[j] = res[j-1];
            j--;
        }
        res[j] = temp;
    }
    return res;
}

void guardarViajeEnArchivo(viaje v, string nombreArchivo){
    recorrido r = {};
    ordenarViaje(v);
    for(int i = 0; i < v.size(); i++){
        gps punto = obtenerPosicion(v[i]);
        r.push_back(punto);
    }

    guardarRecorridosEnArchivo({r}, nombreArchivo);
}

bool sonGrillasIguales(grilla g0, grilla g1){
    bool res = true;
    if (g0.size() == g1.size()){
        tuple<gps, gps, nombre> temp;
        for (int i = 0; i < g0.size() && res; i++){
            temp = g0[i];

            int k = 0;
            while (k < g1.size() && g1[k] != temp){
                k++;
            }
            res = k < g1.size();
        }
    } else{
        res = false;
    }

    return res;
}