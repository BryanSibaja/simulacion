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
            cout<<"Tipo de evento que se esta corriendo: Arribo de msj C1"<<endl;
            eventos.arriboMsjC1();
            break;
        case ARRIBOPAQC1:
            cout<<"Tipo de evento que se esta corriendo: Arribo de paq C1"<<endl;
            eventos.arriboPaqC1();
            break;
        case LIBSERV1C1:
            cout<<"Tipo de evento que se esta corriendo: Libera serv1 C1 "<<endl;
            eventos.libServ1C1();
            break;
        case LIBSERV2C1:
            cout<<"Tipo de evento que se esta corriendo: Libera serv2 C1"<<endl;
            eventos.libServ2C1();
            break;
        case LIBSERVC2:
            cout<<"Tipo de evento que se esta corriendo: Libera serv C2"<<endl;
            eventos.libServC2();
            break;
        case LIBSERVC3:
            cout<<"Tipo de evento que se esta corriendo: Libera serv C3"<<endl;
            eventos.libServC3();
            break;
        case LLEGAACK:
            cout<<"Tipo de evento que se esta corriendo: LLega ACK a la C1"<<endl;
            eventos.llegaAck();
            break;
        case LLEGAMSJC2:
            cout<<"Tipo de evento que se esta corriendo: LLega msj a la C2"<<endl;
            eventos.llegaMsjC2();
            break;
        case LLEGAPAQC3:
            cout<<"Tipo de evento que se esta corriendo: LLega paq a la C3"<<endl;
            eventos.llegaPaqC3();
            break;
        case DEVOLMSJC1:
            cout<<"Tipo de evento que se esta corriendo: Se devuelve msj a la C1"<<endl;
            eventos.devolMsjC1();
            break;
        case TEMP:
            cout<<"Tipo de evento que se esta corriendo: Se vencio el Timer, Enviar Ventana"<<endl;
            eventos.temp();
            break;
        }
        eventos.imprInfo();
        if(lento)
        {
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
