#include "VarAleatorias.h"

VarAleatorias::VarAleatorias()
:aleatorio(0,1)
{
    //ctor
}

VarAleatorias::~VarAleatorias()
{
    //dtor
}

float VarAleatorias::genNormal(float media, float desviacion)
{
    float aux = 0;
    for (int i = 0; i < 12; i++)
        aux += aleatorio(generador);
    return desviacion * (aux-6) + media;

}

float VarAleatorias::genExp(float lamda)
{
    return -(1/lamda) + log(1-aleatorio(generador));
}


float VarAleatorias::porcentaje(float porcet)
{

    float unif = aleatorio(generador);
    return unif < porcet/100;
}
