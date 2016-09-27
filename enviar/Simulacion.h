#ifndef SIMULACION_H
#define SIMULACION_H
#include <iostream>
#include "Eventos.h"
#include <limits>
#include <unistd.h>

using namespace std;

class Simulacion
{
    public:
        Simulacion();
        virtual ~Simulacion();
        void iniciarSim(float duracion, bool lento);

    private:
        float tiempo[11];
        Eventos eventos;
        float reloj;
        int elejirEvento();
};

#endif // SIMULACION_H
