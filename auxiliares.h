#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"

double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);
void ordenarInts (vector<int> &t);
void ordenarViaje(viaje &v);
double velocidad(tuple<tiempo, gps>, tuple<tiempo, gps>);
bool puntoCubierto(gps p, viaje v, distancia u);
bool viajeEnFranja(viaje v, double t0, double tf);
double distanciaEntreViajes(nombre n1, nombre n2);
vector<nombre> puntosDeViajeEnGrilla(viaje v, grilla g);
bool puntoEnErrores (tiempo t, vector<tiempo> errores);
vector<int> obtenerPuntosCercanosValidos(viaje v, int inicial, vector<tiempo> errores);

void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);

#endif //TRANSPORTEURBANO_AUXILIARES_H
