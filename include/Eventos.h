#ifndef EVENTOS_H
#define EVENTOS_H
#include <iostream>
#include "VarAleatorias.h"
#include <deque>
#include <limits>
using namespace std;
enum EVENTOS{ARRIBOMSJC1,ARRIBOPAQC1, LIBSERV1C1, LIBSERV2C1,LIBSERVC2, LIBSERVC3, LLEGAACK, LLEGAMSJC2
, LLEGAPAQC3, DEVOLMSJC1, TEMP};


class Eventos
{
    public:
        Eventos(float t[], float* r);
        virtual ~Eventos();
        void arriboPaqC1();
        void arriboMsjC1();
        void libServ1C1();
        void libServ2C1();
        void llegaAck();
        void devolMsjC1();
        void llegaMsjC2();
        void libServC2();
        void llegaPaqC3();
        void libServC3();
        void temp();
        void imprInfo();
    private:
	VarAleatorias aleatorio;
        float *tiempo;
        float *reloj;
        struct VarC1{
            bool Ser1 = true;
            bool Ser2 = true;
            int conPaq = 0;
            int conMsj = 0;
            int evnPaq = 0;
            bool msj = true;
            deque<int> colPaq;
            deque<int> colMsj;
            int ultimoAck=0;
        }Comp1;

         struct varC2{
            deque<int> msj;
            bool serv = true;
        }Comp2;

         struct varC3{
            deque<int> paq;
            int ack=0;
            bool serv = true;
            deque<int> paqRecibidosBien;
        }Comp3;
};

#endif // EVENTOS_H
