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
    Comp1.colMsj.push_back(Comp1.conMsj);
    ++Comp1.conMsj;
    if(Comp1.Ser1)
        tiempo[LIBSERV1C1] = *reloj;
    if(Comp1.Ser2)
        tiempo[LIBSERV2C1] = *reloj;
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
            cola = true ; // se elige paq
        else if(!Comp1.colMsj.empty())
        {
            cola = false; // se elige msj
        }
    }

    if ( !Comp1.colPaq.empty() || !Comp1.colMsj.empty())
    {
        if (cola)
        {
            Comp1.evnPaq++;
            if(aleatorio.porcentaje(95))
            {
                float duracion = aleatorio.genExp(0.5);
                tiempo[LLEGAPAQC3] = *reloj + duracion + 2;
                tiempo[LIBSERV1C1] = *reloj + duracion;
            }
        }
        else
        {
            // mensajes
            tiempo[LIBSERV1C1] = *reloj + 1;
            tiempo[LLEGAMSJC2]= *reloj+4; // 3 del tiempo de propagacion y 1 de distribución de probabilidad cuya
                                            // función de densidad es: f(x) = 2x/3 con x entre 1 y 2 segundos.
        }
    }
    else
    {
        tiempo[LIBSERV1C1] = *reloj + 2;
    }
}


void Eventos::llegaAck()
{
    if( Comp3.ack == Comp1.colPaq[Comp1.evnPaq])
    {
        for(int i = 0; i < Comp1.evnPaq; i++)
            Comp1.colPaq.pop_front();
    }
    Comp1.evnPaq = 0;
}

void Eventos::devolMsjC1()
{
    Comp1.colMsj.push_back(Comp2.msj.front());
    Comp2.msj.pop_front();
    tiempo[DEVOLMSJC1] = numeric_limits<float>::infinity();

}

void Eventos::llegaMsjC2()
{
    Comp2.msj.push_back(Comp1.colMsj.front());
    Comp1.colMsj.pop_front();
    if(!Comp2.msj.empty() && Comp3.serv )
    {
        tiempo[LIBSERVC2] = *reloj;
    }
    tiempo[LLEGAMSJC2]= numeric_limits<float>::infinity();
}

void Eventos::libServC2()
{
    if (!Comp2.msj.empty())
    {
        if(aleatorio.porcentaje(80))
        {
            Comp2.msj.pop_front();
            tiempo[LIBSERVC2] = *reloj+aleatorio.genExp(1);
        }
        else
        {
           float duracion = aleatorio.genExp(1);
           tiempo[DEVOLMSJC1] = *reloj+ duracion+3;
            tiempo[LIBSERVC2] = *reloj+duracion;

        }

    }
    else
    {
        tiempo[LIBSERVC2]= numeric_limits<float>::infinity();
    }
}

void Eventos::llegaPaqC3()
{
    tiempo[TEMP] = *reloj + 20;
    Comp3.paq.push_back(Comp1.colPaq[Comp1.evnPaq]);
    if(Comp3.serv)
    {
        tiempo[LIBSERVC3] = *reloj;
    }
    tiempo[LLEGAPAQC3]= numeric_limits<float>::infinity();
}

void Eventos::libServC3()
{
    if(Comp3.ack == Comp3.paq.front())
    {
        Comp3.ack++;
        Comp3.paq.pop_front();
        tiempo[LIBSERVC3]= *reloj+ aleatorio.genNormal(1.5, 0.01);
    }
    else
    {
        while(!Comp3.paq.empty())
        {
            Comp3.paq.pop_front();
        }
        tiempo[LIBSERVC3] = numeric_limits<float>::infinity();
    }
    tiempo[LLEGAACK] = *reloj + 2;
}

void Eventos::temp()
{
    tiempo[LLEGAACK] = *reloj + 2;
    tiempo[TEMP] = *reloj + 20;
}

void Eventos::libServ2C1()
{
    bool cola = false;
    if ( !Comp1.colPaq.empty() && Comp1.evnPaq < 4 && !Comp1.colMsj.empty())
    {
        cola = aleatorio.porcentaje(50);
    }
    else
    {
        if (!Comp1.colPaq.empty() && Comp1.evnPaq < 4)
            cola = true ; // se elige paq
        else if(!Comp1.colMsj.empty())
        {
            cola = false; // se elige msj
        }
    }

    if ( !Comp1.colPaq.empty() || !Comp1.colMsj.empty())
    {
        if (cola)
        {
            Comp1.evnPaq++;
            if(aleatorio.porcentaje(95))
            {
                float duracion = aleatorio.genExp(0.5);
                tiempo[LLEGAPAQC3] = *reloj + duracion + 2;
                tiempo[LIBSERV1C1] = *reloj + duracion;
            }
        }
        else
        {
            // mensajes
            tiempo[LIBSERV1C1] = *reloj + 1;
            tiempo[LLEGAMSJC2]= *reloj+4; // 3 del tiempo de propagacion y 1 de distribución de probabilidad cuya
                                            // función de densidad es: f(x) = 2x/3 con x entre 1 y 2 segundos.
        }
    }
    else
    {
        tiempo[LIBSERV1C1] = *reloj + 2;
    }
}
