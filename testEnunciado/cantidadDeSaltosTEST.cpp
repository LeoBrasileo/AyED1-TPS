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

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    guardarViajeEnArchivo(v, "viajeSaltos.csv");

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosTEST, recorridoEnBordes){
    grilla g = construirGrilla(puntoGps(40,120),puntoGps(30,160), 6, 3);

    gps p1 = puntoGps(40,146.66666666666666);
    gps p2 = puntoGps(38.333333333333336,120);
    gps p3 = puntoGps(33.333333333333336,146.66666666666666);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}
