#include <iostream>
#include "Eventos.h"
#include "VarAleatorias.h"


using namespace std;

int main()
{

VarAleatorias a;
float x= a.genNormal(0.5,0.01)+2;
cout << x << endl;



    cout << "Simulacion" << endl;
    return 0;
}
