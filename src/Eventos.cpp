#include "Eventos.h"
#include "VarAleatorias.h"
#include <chrono>   // para generar aleatorios
#include <random> // para generar aleatorios
Eventos::Eventos(float t[])
{
    tiempo = t;
}

Eventos::~Eventos()
{
    //dtor
}

void Eventos::arriboPaqC1()
{
    if(Comp1.contadorDePaq > 100)
    {
        Comp1.contadorDePaq =1;
    }
    colaPaq.push_back(Comp1.contadorDePaq);
    if(colaPaq.size()<4)
    {
        if((Comp1.proc1 == false || Comp1.proc2 == false))
        {
            libServC1(true);
            ++Comp1.contadorDePaq;
        }
    }
}

void Eventos::arriboMsjC1()
{

}

void Eventos::libServC1(bool tipo)
{
    //false= mensaje  true = paquete
    if(tipo==false)
    {

    }
    else
    {
        float t=2;
        t= t+aleatorio.genExp(0.5);
        tiempo[LLEGAPAQC3]+=t;
       // se debe modificar el tiempo en llamar a llegaPaqC3();



    }
}

void Eventos::llegaAck()
{

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

{     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generador(seed);
        std::uniform_int_distribution<int> dst_uniforme(0, 99);
        int in = dst_uniforme(generador);
        // en in hay un numero alearorio entre 1 y 100
    if(in>5){
    colaPaqcmp3.push_back(colaPaq[Comp1.ventanaPaq]);
    }
    if(Comp1.ventanaPaq < 3)
        ++Comp1.ventanaPaq;
    else
        Comp1.ventanaPaq = 0;

}

void Eventos::libServC3()
{
    if(colaPaqcmp3.size() > 0)
    {
        if(colaPaqcmp3[Comp3.paqAProcesar]== Comp3.NumSecuencia) //si esta en la secuencia correcta
        {
            //se envia el ack y se almacena en disco
            //se debe calcular el tiempo en que llega un ack


        }

    }
}

void Eventos::temp()
{

}
