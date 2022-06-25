#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33, -34);
const double unaHora = 3600;

TEST(excesoDeVelocidadGrupoTEST, superaLaVelocidad){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 100000, 0)),
               medicion(unaHora*2, desviarPunto(P, 200000, 0))}; // 100 KM por hora.

    EXPECT_TRUE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadGrupoTEST, justo80Km){
    viaje v ={medicion(0.0, P),
              medicion(unaHora, desviarPunto(P,80000, 0)),
              medicion(unaHora*2, P)};
    EXPECT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadGrupoTEST, excesoEn79Km){
    viaje v ={medicion(0.0, P),
              medicion(unaHora, desviarPunto(P,79990, 0)),
              medicion(unaHora*2, P)};
    EXPECT_FALSE(excesoDeVelocidad(v));
}
