#ifndef VARALEATORIAS_H
#define VARALEATORIAS_H

#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;

/* Generador de numeros aleatorios basado en distrubuciones de
   variables aleadorias*/
class VarAleatorias
{
    public:
        VarAleatorias();
        virtual ~VarAleatorias();
        float genNormal(float media, float desviacion);
        float genExp(float lamda);
        int genUnifor(int minim, int maxim);
        bool porcentaje(int porcet);
    private:
};

#endif // VARALEATORIAS_H
