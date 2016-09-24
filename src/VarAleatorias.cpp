#include "VarAleatorias.h"
using namespace std;
#include <iostream>
VarAleatorias::VarAleatorias()
{
    srand(time(0));
}

VarAleatorias::~VarAleatorias()
{
    //dtor
}

float VarAleatorias::genNormal(float media, float desviacion)
{
    float aux = 0;
    for (int i = 0; i < 12; i++)
        aux += (double)rand() / (double)RAND_MAX;

    return desviacion * (aux-6) + media;

}

float VarAleatorias::genExp(float lamda)
{
    return -(1/lamda) * log(1-(double)rand() / (double)RAND_MAX);
}

bool VarAleatorias::porcentaje(int porcet)
{

    float unif = rand()%100;
    return unif < porcet;
}
