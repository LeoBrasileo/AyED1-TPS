#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

viaje res = {medicion(0,puntoGps(37.521638000000003,15.091198)),
             medicion(20,puntoGps(37.519536,15.091445)),
             medicion(40,puntoGps(37.517434,15.091692)),
             medicion(60,puntoGps(37.51755783440725, 15.09236712340997)),
             medicion(80,puntoGps(37.517686247530115, 15.093549797421298)),
             medicion(100,puntoGps(37.51793750238392, 15.095359003276231)),
             medicion(120,puntoGps(37.51837862596844, 15.098780281298234)),
             medicion(140,puntoGps(37.519154735664706, 15.099822149322792)),
             medicion(160,puntoGps(37.52032168862003, 15.101342737019516)),
             medicion(180,puntoGps(37.5213322828623, 15.102645077225796)),
             medicion(200,puntoGps(37.52230378202455, 15.10385590024824)),
             medicion(220,puntoGps(37.52312451366252, 15.104918919875717)),
             medicion(240,puntoGps(37.5239564069064, 15.105981915209615)),
             medicion(260,puntoGps(37.52478830015028, 15.107044910543511)),
             medicion(280,puntoGps(37.52567042072074, 15.10814309946924))};

TEST(corregirViajeGrupoTEST, faltaElPrimero){
    viaje v = {medicion(0,puntoGps(0,0)),
               medicion(20,puntoGps(37.519536,15.091445)),
               medicion(40,puntoGps(37.517434,15.091692)),
               medicion(60,puntoGps(37.51755783440725, 15.09236712340997)),
               medicion(80,puntoGps(37.517686247530115, 15.093549797421298)),
               medicion(100,puntoGps(37.51793750238392, 15.095359003276231)),
               medicion(120,puntoGps(37.51837862596844, 15.098780281298234)),
               medicion(140,puntoGps(37.519154735664706, 15.099822149322792)),
               medicion(160,puntoGps(37.52032168862003, 15.101342737019516)),
               medicion(180,puntoGps(37.5213322828623, 15.102645077225796)),
               medicion(200,puntoGps(37.52230378202455, 15.10385590024824)),
               medicion(220,puntoGps(37.52312451366252, 15.104918919875717)),
               medicion(240,puntoGps(37.5239564069064, 15.105981915209615)),
               medicion(260,puntoGps(37.52478830015028, 15.107044910543511)),
               medicion(280,puntoGps(37.52567042072074, 15.10814309946924))};

    vector<tiempo> errores = {0};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeGrupoTEST, sinErrores){
    viaje v = {medicion(0,puntoGps(37.521638000000003,15.091198)),
               medicion(20,puntoGps(37.519536,15.091445)),
               medicion(40,puntoGps(37.517434,15.091692)),
               medicion(60,puntoGps(37.51755783440725, 15.09236712340997)),
               medicion(80,puntoGps(37.517686247530115, 15.093549797421298)),
               medicion(100,puntoGps(37.51793750238392, 15.095359003276231)),
               medicion(120,puntoGps(37.51837862596844, 15.098780281298234)),
               medicion(140,puntoGps(37.519154735664706, 15.099822149322792)),
               medicion(160,puntoGps(37.52032168862003, 15.101342737019516)),
               medicion(180,puntoGps(37.5213322828623, 15.102645077225796)),
               medicion(200,puntoGps(37.52230378202455, 15.10385590024824)),
               medicion(220,puntoGps(37.52312451366252, 15.104918919875717)),
               medicion(240,puntoGps(37.5239564069064, 15.105981915209615)),
               medicion(260,puntoGps(37.52478830015028, 15.107044910543511)),
               medicion(280,puntoGps(37.52567042072074, 15.10814309946924))};
    vector<tiempo> errores = {};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.000001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.000001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeGrupoTEST, faltaUno){
    viaje v = {medicion(0,puntoGps(37.521638000000003,15.091198)),
               medicion(20,puntoGps(0,0)),
               medicion(40,puntoGps(37.517434,15.091692)),
               medicion(60,puntoGps(37.51755783440725, 15.09236712340997)),
               medicion(80,puntoGps(37.517686247530115, 15.093549797421298)),
               medicion(100,puntoGps(37.51793750238392, 15.095359003276231)),
               medicion(120,puntoGps(37.51837862596844, 15.098780281298234)),
               medicion(140,puntoGps(37.519154735664706, 15.099822149322792)),
               medicion(160,puntoGps(37.52032168862003, 15.101342737019516)),
               medicion(180,puntoGps(37.5213322828623, 15.102645077225796)),
               medicion(200,puntoGps(37.52230378202455, 15.10385590024824)),
               medicion(220,puntoGps(37.52312451366252, 15.104918919875717)),
               medicion(240,puntoGps(37.5239564069064, 15.105981915209615)),
               medicion(260,puntoGps(37.52478830015028, 15.107044910543511)),
               medicion(280,puntoGps(37.52567042072074, 15.10814309946924))};
    vector<tiempo> errores = {20};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.000001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.000001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeGrupoTEST, faltaUnoDesordenado){
    viaje v = {medicion(0,puntoGps(37.521638000000003,15.091198)),
               medicion(240,puntoGps(37.5239564069064, 15.105981915209615)),
               medicion(40,puntoGps(37.517434,15.091692)),
               medicion(60,puntoGps(37.51755783440725, 15.09236712340997)),
               medicion(100,puntoGps(37.51793750238392, 15.095359003276231)),
               medicion(160,puntoGps(37.52032168862003, 15.101342737019516)),
               medicion(120,puntoGps(37.51837862596844, 15.098780281298234)),
               medicion(140,puntoGps(37.519154735664706, 15.099822149322792)),
               medicion(180,puntoGps(37.5213322828623, 15.102645077225796)),
               medicion(200,puntoGps(37.52230378202455, 15.10385590024824)),
               medicion(20,puntoGps(0,0)),
               medicion(220,puntoGps(37.52312451366252, 15.104918919875717)),
               medicion(260,puntoGps(37.52478830015028, 15.107044910543511)),
               medicion(80,puntoGps(37.517686247530115, 15.093549797421298)),
               medicion(280,puntoGps(37.52567042072074, 15.10814309946924))};
    vector<tiempo> errores = {20};

    corregirViaje(v, errores);
    ordenarViaje(v); //Se vuelve a ordenar para que coincida en orden con res
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.000001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.000001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}

TEST(corregirViajeGrupoTEST, falta2Seguidos){
    viaje v = {medicion(0,puntoGps(37.521638000000003,15.091198)),
               medicion(20,puntoGps(37.519536,15.091445)),
               medicion(40,puntoGps(37.517434,15.091692)),
               medicion(60,puntoGps(37.51755783440725, 15.09236712340997)),
               medicion(80,puntoGps(37.517686247530115, 15.093549797421298)),
               medicion(100,puntoGps(37.51793750238392, 15.095359003276231)),
               medicion(120,puntoGps(37.51837862596844, 15.098780281298234)),
               medicion(140,puntoGps(37.519154735664706, 15.099822149322792)),
               medicion(160,puntoGps(37.52032168862003, 15.101342737019516)),
               medicion(180,puntoGps(37.5213322828623, 15.102645077225796)),
               medicion(200,puntoGps(37.52230378202455, 15.10385590024824)),
               medicion(220,puntoGps(0, 0)),
               medicion(240,puntoGps(0, 0)),
               medicion(260,puntoGps(37.52478830015028, 15.107044910543511)),
               medicion(280,puntoGps(37.52567042072074, 15.10814309946924))};
    vector<tiempo> errores = {220, 240};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}