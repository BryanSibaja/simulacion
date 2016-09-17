#ifndef EVENTOS_H
#define EVENTOS_H

#include "VarAleatorias.h"
enum EVENTOS{ARRIBOPAQC1, ARRIBOMSJC1, LIBSERVC1, LLEGAACK, DEVOLMSJC1, LLEGAMSJC2,
             LIBSERVC2, LLEGAPAQC3, LIBSERVC3, TEMP};
#include <vector>

class Eventos
{
    public:
        Eventos(float t[]);
        virtual ~Eventos();
        void arriboPaqC1();
        void arriboMsjC1();
        void libServC1(bool tipo); // dos eventos  false= mensaje  true = paquete
        void llegaAck();
        void devolMsjC1();
        void llegaMsjC2();
        void libServC2();
        void llegaPaqC3();
        void libServC3();
        void temp();

    private:
	VarAleatorias aleatorio;
        float *tiempo;

        struct ProcesosC1{
            bool proc1 = false;
            bool proc2 = false;
            bool SerMsj = false;
            bool SerPaq = false;
            float timer = 0;
            int contadorDePaq = 1;
            int ventanaPaq=0;
        }Comp1;

        std::vector<int> colaPaq;

};

#endif // EVENTOS_H
