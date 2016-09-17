#ifndef SIMULACION_H
#define SIMULACION_H

#include "Eventos.h"

class Simulacion
{
    public:
        Simulacion();
        virtual ~Simulacion();
        void iniciarSim();

    private:
        float tiempo[11];
        Eventos eventos;
        int elejirEvento();
};

#endif // SIMULACION_H
