#include "Eventos.h"
#include "VarAleatorias.h"

Eventos::Eventos(float t[])
{
    tiempo = t;
}

Eventos::~Eventos()
{
    //dtor
}

void Eventos::arriboPaqC1()
{   if(Comp1.contadorDePaq > 100){
            Comp1.contadorDePaq =1;
    }
    colaPaq.push_back(Comp1.contadorDePaq);
 if((Comp1.proc1 == false || Comp1.proc2 == false) && Comp1.ventanaPaq <4){
        libServC1(true);
        ++Comp1.contadorDePaq;
    }
}

void Eventos::arriboMsjC1()
{

}

void Eventos::libServC1(bool tipo)
{//false= mensaje  true = paquete
    if(tipo==false){


    }else{

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
{

}

void Eventos::libServC3()
{

}

void Eventos::temp()
{

}
