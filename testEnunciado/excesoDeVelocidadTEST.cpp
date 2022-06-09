#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33, -34);
const double unaHora = 3600;

TEST(excesoDeVelocidadTEST, noSuperaLaVelocidad){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 1000, 0)),
               medicion(unaHora*2, desviarPunto(P, 2000, 0))}; // 1 KM por hora.

    EXPECT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, superaLaVelocidad){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 100000, 0)),
               medicion(unaHora*2, desviarPunto(P, 200000, 0))}; // 100 KM por hora.

    EXPECT_TRUE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, igualAlLimite){
    viaje v ={medicion(0.0, P),
              medicion(unaHora, desviarPunto(P,79999, 0)),
              medicion(unaHora*2, P)};
//el desvío son 7999 ya que si fuesen 80000 estariamos despreciando la curvatura de la tierra
    EXPECT_FALSE(excesoDeVelocidad(v));
}
