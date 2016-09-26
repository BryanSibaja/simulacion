#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Simulacion.h"
using namespace std;

int main()
{
    cout << "Ingrese la cantidad de veces que desea correr la simulación" << endl;
    int corridas=0;
   cin>>corridas;
    cout << "Ingrese el tiempo total en segundos para correr la simulación" << endl;
    int tiempo=0;
    cin>>tiempo;
    cout << "Desea ver la simulación correr en modo lento o no? s/n" << endl;
    char modo=' ';
    cin>>modo;


    for(int i=0;i<corridas; ++i){
    Simulacion sim;
    if(modo=='s')
        sim.iniciarSim(tiempo,true);
    else
        sim.iniciarSim(tiempo,false);
    }


    cout << "Simulacion" << endl;
    return 0;
}
