#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(cantidadDeSaltosGrupoTEST, 2Saltos){
    grilla g = construirGrilla(puntoGps(30.626755,114.240196),puntoGps(30.590118,114.294416), 6, 3);

    gps p1 = puntoGps(30.626755 - 0.003,114.240196 + 0.005);
    gps p2 = puntoGps(30.626755 - 0.003,114.240196 - 0.005 + 0.018073333333333608 * 3);
    gps p3 = puntoGps(30.626755 - 0.003 - 0.0061061666666664864 * 4,114.240196 + 0.005);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosGrupoTEST, recorridoEnBordes){
    grilla g = construirGrilla(puntoGps(40,120),puntoGps(30,160), 6, 3);

    gps p1 = puntoGps(40,146.66666666666666);
    gps p2 = puntoGps(38.333333333333336,120);
    gps p3 = puntoGps(33.333333333333336,146.66666666666666);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),1);
}

TEST(cantidadDeSaltosGrupoTEST, viajeVacio){
    grilla g = construirGrilla(puntoGps(40,120),puntoGps(30,160), 6, 3);

    viaje v = {};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}

TEST(cantidadDeSaltosGrupoTEST, grillaVacia){
    grilla g = {};

    gps p1 = puntoGps(40,146.66666666666666);
    gps p2 = puntoGps(38.333333333333336,120);
    gps p3 = puntoGps(33.333333333333336,146.66666666666666);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}

TEST(cantidadDeSaltosGrupoTEST, todosSaltosOrdenados){
    grilla g = construirGrilla(puntoGps(-26.789251,-65.243994),puntoGps(-26.835703,-65.180891), 10, 6);

    gps p1 = puntoGps(-26.824763,-65.183793);
    gps p2 = desviarPunto(p1, -150, 0);
    gps p3 = desviarPunto(p2, -150, 0);

    viaje v = {medicion(20, p1),
               medicion(50, p2),
               medicion(70, p3)};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}

TEST(cantidadDeSaltosGrupoTEST, algunosSaltosDesordenados){
    grilla g = construirGrilla(puntoGps(-26.789251,-65.243994),puntoGps(-26.835703,-65.180891), 10, 6);

    gps p1 = puntoGps(-26.808544,-65.223783);
    gps p2 = desviarPunto(p1, 0, 200);
    gps p3 = desviarPunto(p2, 0, 200);
    gps p4 = desviarPunto(p3, 0, 200);

    viaje v = {medicion(20, p1),
               medicion(70, p3),
               medicion(50, p2),
               medicion(90, p4)};

    EXPECT_EQ(cantidadDeSaltos(g,v),0);
}
