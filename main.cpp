#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "Simulacion.h"
#include "Event.h"
using namespace std;

void validarInt(int &x)
{
    bool continuar;
    int cont=0;
    do
    {
        continuar= false;
        if(cont>0)cin.ignore(1024,'\n');
        cin>>x;
        ++cont;
        if(cin.fail())
        {
            cout<<"No ingreso un numero\n";
            continuar= true;
        }
        cin.clear();
    }
    while (continuar);
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

float promCpaq=0;
float promCmsj=0;
float promCven=0;
float permaPaq=0;
float permaMsj=0;
float promTrans=0;
float tiemServ=0;
float eficiencia=0;
float varMuestralPorStu=0;
deque<int> ColaPermPaq;
float media=0;

 void intervCon(int &corridas){
    //permaPaq contiene la suma total de los promedios de permanencia de cada corrida
    media = permaPaq/corridas;
    for(int i=0; i<corridas;++i){
        varMuestralPorStu+= (ColaPermPaq[i]-media)*(ColaPermPaq[i]-media); // (Xi-media)^2
    }
    varMuestralPorStu= varMuestralPorStu/(corridas-1);
    varMuestralPorStu= varMuestralPorStu*2.26;

}
void imprFinal(int corridas)
{
    cout<<"\n\nCalculando los promedios finales..\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout<<"\n\nDatos al TERMINAR TODAS las corridas: \n";
    cout<<"Tamaño promedio de las colas en Serv. No.1:\n";
    cout<<"Tamaño promedio de la cola de Paquetes: "<<promCpaq/corridas<<endl;
    cout<<"Tamaño promedio de la Ventana de Paquetes: "<<promCmsj/corridas<<endl;
    cout<<"Tamaño promedio de la cola de Mensajes: "<<promCven/corridas<<endl;
    cout<<"Tiempo promedio de permanencia de un paquete en el sistema: "<<permaPaq/corridas<<endl;
    cout<<"Tiempo promedio de permanencia de un mensaje en el sistema: "<<permaMsj/corridas<<endl;
    cout<<"Promedio del tiempo de transmision para un paquete(se pueden enviar varias veces el mismo paq): "<<promTrans/corridas<<endl;
    cout<<"Tiempo promedio de servicio (para un paquete): "<<tiemServ/corridas<<endl;
    cout<<"Eficiencia: "<<eficiencia/corridas<<endl;
    intervCon(corridas);

    cout<<"El intervalo de confianza es: ("<<media- varMuestralPorStu<<", "<<media+varMuestralPorStu<<")\n";

}
void llenarPromedios(Eventos e)
{
    promCpaq+=e.promCpaq;
    promCmsj+=e.promCmsj;
    promCven+=e.promCven;
    permaPaq+= e.permaPaq;
    ColaPermPaq.push_back(e.permaPaq);
    permaMsj+= e.permaMsj;
    promTrans+= e.promTrans;
    tiemServ+= e.tiemServ;
    eficiencia+= e.eficiencia;

}
int main()
{

    cout << "Ingrese la cantidad de veces que desea correr la simulacion" << endl;
    int corridas=0;
    validarInt(corridas);

    cout << "Ingrese el tiempo total en segundos para correr la simulacion" << endl;
    int tiempo=0;
    validarInt(tiempo);

    cout << "Desea ver la simulacion correr en modo lento o no? s/n" << endl;
    char modo=' ';
    cin>>modo;


    for(int i=0; i<corridas; ++i)
    {
        int t=0;
        Simulacion sim;
        if(modo=='s')
        {
            cout << "Ingrese la cantidad del segundos del delay: " << endl;
            validarInt(t);
            sim.iniciarSim(tiempo,true,t);
            llenarPromedios(sim.eventos);
        }
        else
        {
            sim.iniciarSim(tiempo,false,t);
            llenarPromedios(sim.eventos);
        }
    }

    imprFinal(corridas);

    cin>>modo;// solo para q se espere al final
    cout << "Simulacion" << endl;
    return 0;
}
