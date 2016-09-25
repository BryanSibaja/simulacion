#include "Simulacion.h"

Simulacion::Simulacion():
    eventos(tiempo, &reloj)
{
    reloj = 0;
    for(int i = 0; i < 11; i++)
        tiempo[i] = numeric_limits<float>::infinity();
    tiempo[ARRIBOPAQC1] = 4;
    tiempo[ARRIBOMSJC1] = 5;
    tiempo[TEMP] = 20;
}

Simulacion::~Simulacion()
{
    //dtor
}

void Simulacion::iniciarSim(float duracion, bool lento)
{
    while( reloj < duracion)
    {
        int e = elejirEvento();
        reloj = tiempo[e];
        switch(e)
        {
        case ARRIBOMSJC1:

            eventos.arriboMsjC1();
            break;
        case ARRIBOPAQC1:

            eventos.arriboPaqC1();
            break;
        case LIBSERV1C1:

            eventos.libServ1C1();
            break;
        case LIBSERV2C1:

            eventos.libServ2C1();
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
        if(lento){
            usleep(2000000);
        }
    }
}

int Simulacion::elejirEvento()
{
    int e = 0;
    for(int i =0; i < 11; i++)
    {
        if (tiempo[e] > tiempo[i])
            e = i;
    }
    return e;
}
