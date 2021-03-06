#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(construirGrillaGrupoTEST, verificarGrilla){

    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(120,0);
    gps esq2 = puntoGps(0,180);

    grilla gres = {make_tuple(puntoGps(120,0), puntoGps(60,60), make_tuple(1,1)),
                   make_tuple(puntoGps(120,60), puntoGps(60,120), make_tuple(1,2)),
                   make_tuple(puntoGps(120,120), puntoGps(60,180), make_tuple(1,3)),
                   make_tuple(puntoGps(60,0), puntoGps(0,60), make_tuple(2,1)),
                   make_tuple(puntoGps(60,60), puntoGps(0,120), make_tuple(2,2)),
                   make_tuple(puntoGps(60,120), puntoGps(0,180), make_tuple(2,3))
    };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_TRUE(sonGrillasIguales(g, gres));
}
