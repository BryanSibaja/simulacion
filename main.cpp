#include <iostream>
#include "Eventos.h"
#include "VarAleatorias.h"
#include <vector>
#include <chrono>
#include <random>

using namespace std;

int main()
{
VarAleatorias a;
for (int i = 0;i < 100; i++)
cout << a.genNormal(4, 0.01) << endl;




    cout << "Simulacion" << endl;
    return 0;
}
