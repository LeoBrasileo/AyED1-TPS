#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(distanciaTotalGrupoTEST, viajeQuieto){
    gps p1 = puntoGps(-33,-33);

    viaje v = {medicion(5, p1),
               medicion(6.4, p1),
               medicion(7, p1),
               medicion(8.1, p1)};
    EXPECT_EQ(distanciaTotal(v),0);
}

