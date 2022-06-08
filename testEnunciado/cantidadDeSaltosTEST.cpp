#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(cantidadDeSaltosTEST, todosSaltosOrdenados){
    grilla g = construirGrilla(puntoGps(30.626755,114.240196),puntoGps(30.590118,114.294416), 6, 3);
    guardarGrillaEnArchivo(g,"pruebas.csv");

    gps p1 = puntoGps(30.626755 - 0.003,114.240196 + 0.005);
    gps p2 = puntoGps(30.626755 - 0.003,114.240196 - 0.005 + 0.018073333333333608 * 3);
    gps p3 = puntoGps(30.626755 - 0.003 - 0.0061061666666664864 * 4,114.240196 + 0.005);

    recorrido r = {p1,p2,p3};
    guardarRecorridosEnArchivo({r}, "recorridos.csv");

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

