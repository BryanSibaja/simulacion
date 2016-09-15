#ifndef VARALEATORIAS_H
#define VARALEATORIAS_H

#include <random>
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
        float genUnifor(float minim, float maxim);
        float porcentaje(float porcet);
    private:
        uniform_real_distribution<float> aleatorio;
        default_random_engine generador;
};

#endif // VARALEATORIAS_H
