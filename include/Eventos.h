#ifndef EVENTOS_H
#define EVENTOS_H


class Eventos
{
    public:
        Eventos();
        virtual ~Eventos();
        void arriboPaqC1();
        void arriboMsjC1();
        void libServC1(); // dos eventos
        void llegaAck();
        void devolMsjC1();
        void llegaMsjC2();
        void libServC2();
        void llegaPaqC3();
        void libServC3();
        void temp();

    private:
};

#endif // EVENTOS_H
