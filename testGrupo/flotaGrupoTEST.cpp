#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

vector<viaje> s = {{
                   medicion(1.5,puntoGps(2.5, 2.89996)),
                   medicion(1.7,puntoGps(2.5, 2.89997)),
                   medicion(1.9,puntoGps(2.5, 2.89998))},
                   {
                    medicion(2.5,puntoGps(2.5, 2.89996)),
                    medicion(2.6,puntoGps(2.5, 2.89997)),
                    medicion(2.7,puntoGps(2.5, 2.89998))},
                   {
                    medicion(0.5,puntoGps(2.5, 2.89996)),
                    medicion(0.6,puntoGps(2.5, 2.89997)),
                    medicion(0.7,puntoGps(2.5, 2.89998))},
                   };

TEST(flotaTotalGrupoTEST, todosDespues){
    EXPECT_EQ(flota(s, 2.8,4.55),0);
}

TEST(flotaTotalGrupoTEST, primeroAdentroPorBordes){
    EXPECT_EQ(flota(s, 0.1,0.5),1);
}

TEST(flotaTotalGrupoTEST, ultimoAdentroPorBordes){
    EXPECT_EQ(flota(s, 2.7,2.9),1);
}
