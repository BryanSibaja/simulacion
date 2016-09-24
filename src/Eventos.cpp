#include "Eventos.h"
#include "VarAleatorias.h"
#include <chrono>   // para generar aleatorios
#include <random> // para generar aleatorios
Eventos::Eventos(float t[], float* r)
{
    tiempo = t;
    reloj = r;
}

Eventos::~Eventos()
{
    //dtor
}

void Eventos::arriboPaqC1()
{
    Comp1.colPaq.push_back(Comp1.conPaq);
    Comp1.conPaq = ++Comp1.conPaq % 100;
    if(Comp1.Ser1)
        tiempo[LIBSERV1C1] = *reloj;
    if(Comp1.Ser2)
        tiempo[LIBSERV2C1] = *reloj;

    tiempo[ARRIBOPAQC1] = *reloj + aleatorio.genUnifor(3,7);
}

void Eventos::arriboMsjC1()
{
    tiempo[ARRIBOMSJC1] = *reloj + aleatorio.genNormal(4, 0.01);
}

void Eventos::libServ1C1()
{
    bool cola = false;
    if ( !Comp1.colPaq.empty() && Comp1.evnPaq < 4 && !Comp1.colMsj.empty())
    {
        cola = aleatorio.porcentaje(50);
    }
    else
    {
        if (!Comp1.colPaq.empty() && Comp1.evnPaq < 4)
            cola = false; // se elige paq
        else
        {
            if(!Comp1.colMsj.empty())
                cola = true; // se elige msj
        }
    }
    if (cola)
    {
        Comp1.evnPaq++;
        if(aleatorio.porcentaje(95))
        {
            float duracion = aleatorio.genExp(0.5);
            tiempo[LLEGAPAQC3] = *reloj + duracion + 2;
            tiempo[LIBSERV1C1] = *reloj + duracion;
        }
    }else{
    }
}


void Eventos::llegaAck()
{
    if( Comp3.ack == Comp1.colPaq[Comp1.evnPaq]){
        for(int i = 0; i < Comp1.evnPaq; i++)
            Comp1.colPaq.pop_front();
    }
    Comp1.evnPaq = 0;
}

void Eventos::devolMsjC1()
{

}

void Eventos::llegaMsjC2()
{

}

void Eventos::libServC2()
{

}

void Eventos::llegaPaqC3()
{
    Comp3.paq.push_back(Comp1.colPaq[Comp1.evnPaq]);
    if(Comp3.serv)
        tiempo[LIBSERVC3] = *reloj;
}

void Eventos::libServC3()
{
    if(Comp3.ack == Comp3.paq.front()){
        Comp3.ack++;
        Comp3.paq.pop_front();
    }
    else{
        while(!Comp3.paq.empty()){
            Comp3.paq.pop_front();
        }
    }
    tiempo[LLEGAACK] = *reloj + 2;
}

void Eventos::temp()
{

}

void Eventos::libServ2C1()
{

}
