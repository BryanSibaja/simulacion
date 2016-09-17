#include "Simulacion.h"

Simulacion::Simulacion():
eventos(tiempo)
{
    //ctor
}

Simulacion::~Simulacion()
{
    //dtor
}

void Simulacion::iniciarSim()
{
    int e = elejirEvento();
    switch(e){
        case ARRIBOMSJC1:
            eventos.arriboMsjC1();
            break;
        case ARRIBOPAQC1:
            eventos.arriboPaqC1();
            break;
        case LIBSERVC1:
            eventos.libServC1(true);
            break;
        case LIBSERVC2:
            eventos.libServC2();
            break;
        case LIBSERVC3:
            eventos.libServC3();
            break;
        case LLEGAACK:
            eventos.llegaAck();
            break;
        case LLEGAMSJC2:
            eventos.llegaMsjC2();
            break;
        case LLEGAPAQC3:
            eventos.llegaPaqC3();
            break;
        case DEVOLMSJC1:
            eventos.devolMsjC1();
            break;
        case TEMP:
            eventos.temp();
            break;
    }
}

int Simulacion::elejirEvento()
{
    int e = 0;
    for(int i =0; i < 11; i++){
        if (tiempo[e] > tiempo[i])
            e = i;
    }
    return e;
}
