#ifndef SIMULACION_H
#define SIMULACION_H

#include "Eventos.h"
#include <limits>

using namespace std;

class Simulacion
{
    public:
        Simulacion();
        virtual ~Simulacion();
        void iniciarSim();

    private:
        float tiempo[11];
        Eventos eventos;
        float reloj;
        int elejirEvento();
};

#endif // SIMULACION_H
