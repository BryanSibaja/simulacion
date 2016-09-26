#ifndef SIMULACION_H
#define SIMULACION_H
#include <iostream>
#include "Eventos.h"
#include <unistd.h>
#include <queue>

using namespace std;

class Simulacion
{
    public:
        Simulacion();
        virtual ~Simulacion();
        void iniciarSim(float duracion, bool lento);

    private:
        priority_queue<Event> tiempo;
        Eventos eventos;
        float reloj;
        float tiemp = 20;
        int elejirEvento();
};

#endif // SIMULACION_H
