#ifndef EVENTOS_H
#define EVENTOS_H
#include <iostream>
#include <deque>
#include <queue>
#include "Event.h"
#include "VarAleatorias.h"
#include <thread> //sleep _for
#include <chrono> // crono segundos
using namespace std;
enum EVENTOS{ARRIBOMSJC1,ARRIBOPAQC1, LIBSERV1C1, LIBSERV2C1,LIBSERVC2, LIBSERVC3, LLEGAACK, LLEGAMSJC2
, LLEGAPAQC3, DEVOLMSJC1, TEMP};

class Eventos
{
    public:
        Eventos(priority_queue<Event>* t, float* r, float* tp);
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
        void imprFinal();

        float promCpaq=0;
        float promCmsj=0;
        float promCven=0;
        float permaPaq=0;
        float permaMsj=0;
        float promTrans=0;
        float tiemServ=0;
        float eficiencia=0;

    private:
	VarAleatorias aleatorio;
        priority_queue<Event> *tiempo;
        float *reloj;
        float *tiemp;

        struct VarC1{
            bool Ser1 = true;
            bool Ser2 = true;
            int conPaq = 0;
            int conMsj = 0;
            int evnPaq = 0;
            bool msj = true;
            deque<int> colPaq;
            deque<int> colMsj;
            deque<int> ack;
            deque<int> msjmalos;
            int ultimoAck=0;
        }Comp1;

         struct varC2{
            deque<int> msj;
            deque<int> trans;
            bool serv = true;
        }Comp2;

         struct varC3{
            deque<int> paq;
            deque<int> trans;
            int molestar = 0;
            int ack=0;
            bool serv = true;
            deque<int> paqRecibidosBien;
        }Comp3;

        //calculo del promedio de las colas
        int tamProColaPaqC1=0;
        int contPa=0;
        int tamProColaMsjC1=0;
        int contMsj=0;
        int tamPRoVentanaC1=0;
        int contVent=0;
        // calculo del promedio de un paq en el sistema
        deque<float> paqEnSist;
        float promPaqEnSist=0;
        float contPa2;

        deque<float> msjEnSist;
        float promMsjEnSist=0;

        float tiemTransmision=0;
        float contTransmisiones=0;

};

#endif // EVENTOS_H
