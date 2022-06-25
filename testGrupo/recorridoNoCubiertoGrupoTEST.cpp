#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

template<typename T>
bool included(T elem, vector<T> container){
    for (int i = 0; i < container.size(); ++i) {
        if (container[i] == elem){return true;}
    }
    return false;
}

template<typename T>
void ASSERT_ELEMENTS(vector<T> container, vector<T> elems) {
    for(int i = 0; i < elems.size(); i++ ) {
        ASSERT_TRUE(included(elems[i], container));
    }

}

using namespace std;

const gps P = puntoGps(-31.465027, -64.212973);
const recorrido R = {P,
                     desviarPunto(P, 1000, 0),
                     desviarPunto(P, 2000, 0),
                     desviarPunto(P, 3000, 0),
                     desviarPunto(P, 4000, 0),
                     desviarPunto(P, 5000, 0),
                     desviarPunto(P, 6000, 0),
                     desviarPunto(P, 7000, 0),
                     desviarPunto(P, 8000, 0),
                     desviarPunto(P, 9000, 0),
                      };

const recorrido RRulos = {P,
                     desviarPunto(P, 1000, 0),
                     desviarPunto(P, 2000, 0),
                     desviarPunto(P, 3000, 0),
                     desviarPunto(P, 4000, 0),
                     desviarPunto(P, 5000, 0),
                     desviarPunto(P, 5000, 100),
                     desviarPunto(P, 4000, 100),
                     desviarPunto(P, 3000, 100),
                     desviarPunto(P, 2000, 100),
                     desviarPunto(P, 1000, 100),
                     desviarPunto(P, 0, 0)
};

TEST (recorridoNoCubiertoGrupoTEST, todosAfuera){
    gps p = puntoGps(33,49);
    recorrido r = {p,
                   desviarPunto(p,0,50),
                   desviarPunto(p,0, 100),
                   desviarPunto(p,150, 0),
                   desviarPunto(p, 181, 75)
                   };
    viaje v = {medicion(3, desviarPunto(p,-250,50)),
               medicion(4.7, desviarPunto(p, -250, 100)),
               medicion(6,desviarPunto(p,-250, -200)),
               medicion(8.24,desviarPunto(p,-300, -180))
    };
    EXPECT_EQ(recorridoNoCubierto(v, r, 0.2), r);
}
