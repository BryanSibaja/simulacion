#ifndef SIMULACION_H
#define SIMULACION_H
#include <iostream>
#include "Eventos.h"
#include <unistd.h>
#include <queue>
#include <thread> //sleep _for
#include <chrono> // crono segundos
using namespace std;

class Simulacion
{
    public:
        Simulacion();
        virtual ~Simulacion();
        void iniciarSim(float duracion, bool lento, int t);
        void imprFinal();
        Eventos eventos;
    private:
        priority_queue<Event> tiempo;

        float reloj;
        float tiemp = 20;


};

#endif // SIMULACION_H
