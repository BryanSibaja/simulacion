#include <iostream>
#include "Eventos.h"
#include "VarAleatorias.h"
#include <vector>
#include <chrono>
#include <random>

using namespace std;

int main()
{   std::vector<int> first;                                // empty vector of ints
  std::vector<int> second (4,100);                       // four ints with value 100
  std::vector<int> third (second.begin(),second.end());  // iterating through second
  std::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

   // cout << fifth.size()<< endl;
fifth.erase(fifth.begin());
cout << fifth[0]<< endl;
//fifth.clear();
   // cout << fifth.size()<< endl;

VarAleatorias a;
float x= a.genNormal(0.5,0.01)+2;
cout << x << endl;




    cout << "Simulacion" << endl;
    return 0;
}
