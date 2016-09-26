#include "VarAleatorias.h"

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
        aux += (float)rand() / (float)RAND_MAX;

    return desviacion * (aux-6) + media;
}

float VarAleatorias::genExp(float lamda)
{
    return -(1/lamda) * log(1-(float)rand() / (float)RAND_MAX);
}

bool VarAleatorias::porcentaje(int porcet)
{

    float unif = rand()%100;
    return unif < porcet;
}

float VarAleatorias::genUnifor(float minim, float maxim)
{
    return ((float) rand() / (RAND_MAX)) * (maxim-minim) + minim;
}

float VarAleatorias::distrubucion()
{
    return sqrt(((float)rand() / (float)RAND_MAX)*3 + 1);
}
