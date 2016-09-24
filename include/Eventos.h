#ifndef EVENTOS_H
#define EVENTOS_H

#include "VarAleatorias.h"
enum EVENTOS{ARRIBOPAQC1, ARRIBOMSJC1, LIBSERVC1, LLEGAACK, DEVOLMSJC1, LLEGAMSJC2,
             LIBSERVC2, LLEGAPAQC3, LIBSERVC3, TEMP};
#include <vector>

class Eventos
{
    public:
        Eventos(float t[], float* r);
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
        float *reloj;
        struct ProcesosC1{
            int procesos = 0; // procesos que envian paquetes de la c1 a la c2 o c3

            bool SerMsj = false;   //servidores que reciben paquetes o msjs
            bool SerPaq = false;
            float timer = 0;
            int contadorDePaq = 1;   // para enumerar los paquetes
            int ventanaPaq=0; //posicion de la ventana para eniviar de 0-3
        }Comp1;

        struct ProcesosC3{
         int NumSecuencia = 1; // lleva el contro del paquete que le toca ser procesado
         bool servidor = false; // si el servidor de que atiende paquetes esta ocupado
         int paqAProcesar=0; //para saber que paquete que esta en la cola de la c3 le tocas e procesado
        }Comp3;


        std::vector<int> colaPaq;
        std::vector<int> colaPaqcmp3;

};

#endif // EVENTOS_H
