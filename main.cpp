#include <iostream>
#include "Eventos.h"
#include "VarAleatorias.h"
#include <vector>
#include <chrono>
#include <random>
#include "Simulacion.h"
using namespace std;

int main()
{
    cout << "Ingrese la cantidad de veces que desea correr la simulaci�n" << endl;
    int corridas=0;
    cin>>corridas;
    cout << "Ingrese el tiempo total en segundos para correr la simulaci�n" << endl;
    int tiempo=0;
    cin>>tiempo;
    cout << "Desea ver la simulaci�n correr en modo lento o no? s/n" << endl;
    char modo=' ';
    cin>>modo;

    Simulacion sim();







    cout << "Simulacion" << endl;
    return 0;
}
