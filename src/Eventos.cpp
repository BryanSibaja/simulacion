#include "Eventos.h"
#include "VarAleatorias.h"

using namespace std;
Eventos::Eventos(priority_queue<Event>* t, float* r, float* tp)
{
    tiempo = t;
    reloj = r;
    tiemp = tp;
}

Eventos::~Eventos()
{
    //dtor
}

void Eventos::arriboPaqC1()
{
    // se guardan datos para las estadisticas
    Comp1.colPaq.push_back(Comp1.conPaq);
    paqEnSist.push_back(*reloj);
// es para el promedio del tamano de las colas
    tamProColaPaqC1+= Comp1.colPaq.size();
    ++contVent;
    if(Comp1.colPaq.size()<=4)
    {
        tamPRoVentanaC1+= Comp1.colPaq.size();
    }
    else
    {
        tamPRoVentanaC1+=4;
    }

    //inicia la logica
    Comp1.conPaq = (Comp1.conPaq + 1) % 100;
    if(Comp1.Ser1)
    {
        Comp1.Ser1=false;
        tiempo->push(Event(LIBSERV1C1, *reloj));
    }
    else if(Comp1.Ser2)
    {
        Comp1.Ser2=false;
        tiempo->push(Event(LIBSERV2C1,*reloj));
    }

    tiempo->push(Event(ARRIBOPAQC1,*reloj + aleatorio.genUnifor(3,7)));
}

void Eventos::arriboMsjC1()
{

    Comp1.colMsj.push_back(Comp1.conMsj);
    msjEnSist.push_back(*reloj);
    // se guardan datos para estadisticas
    ++contMsj;
    tamProColaMsjC1+= Comp1.colMsj.size();
    ++Comp1.conMsj;
    // inicia la logica
    if(Comp1.Ser1)
    {
        Comp1.Ser1 = false;
        tiempo->push(Event(LIBSERV1C1,*reloj));
    }
    else if(Comp1.Ser2)
    {
        Comp1.Ser2 = false;
        tiempo->push(Event(LIBSERV2C1,*reloj));
    }
    tiempo->push(Event(ARRIBOMSJC1,*reloj + aleatorio.genNormal(4, 0.01)));
}

void Eventos::libServ1C1()
{
    Comp1.Ser1 = false;
    if (!Comp1.colPaq.empty() && (Comp1.evnPaq < 4 && Comp1.evnPaq < Comp1.colPaq.size()))
    {
        Comp1.evnPaq++;
        float duracion = aleatorio.genExp(0.5);
        cout << "Enviando paquete " << Comp1.colPaq[Comp1.evnPaq -1] << endl;
        if(aleatorio.porcentaje(95))
        {
            Comp3.trans.push_back(Comp1.colPaq[Comp1.evnPaq-1]);
            tiempo->push(Event(LLEGAPAQC3,*reloj + duracion + 2));
            tiemTransmision+= duracion+2;
            ++contTransmisiones;
        }
        else
        {
            cout << "El paquete " << Comp1.colPaq[Comp1.evnPaq -1] << " se perdio"<< endl;
        }
        tiempo->push(Event(LIBSERV1C1,*reloj + duracion));
    }
    else
    {
        if(!Comp1.colMsj.empty())
        {
            cout << "Enviando mensaje " << Comp1.colMsj.front() << endl;
            Comp2.trans.push_back(Comp1.colMsj.front());
            Comp1.colMsj.pop_front();
            ++contMsj;
            tamProColaMsjC1+= Comp1.colMsj.size();
            tiempo->push(Event(LIBSERV1C1,*reloj + aleatorio.distrubucion()));
            tiempo->push(Event(LLEGAMSJC2,*reloj+4)); // 3 del tiempo de propagacion y 1 de distribución de probabilidad cuya
            // función de densidad es: f(x) = 2x/3 con x entre 1 y 2 segundos.
        }
        else
        {
            Comp1.Ser1=true;
        }
    }
}


void Eventos::llegaAck()
{
    // llega un ack a la computadora1
    Comp1.ultimoAck=Comp1.ack.front();
    if( Comp1.ultimoAck == (Comp1.colPaq[0] + 1)%100)
    {   promPaqEnSist+= *reloj-paqEnSist[0];
        paqEnSist.pop_front();
      // es para el promedio de permanencia
        Comp1.colPaq.pop_front();
        //se guardan datos para las estadisticas
        ++contPa;
        tamProColaPaqC1+= Comp1.colPaq.size();
        if(Comp1.colPaq.size()<=4)
        {
            tamPRoVentanaC1+= Comp1.colPaq.size();
        }
        else
        {
            tamPRoVentanaC1+=4;
        }
        Comp1.evnPaq--;
    }
    else
    {
        Comp1.evnPaq = 0;
    }
    Comp1.ack.pop_front();
}

void Eventos::devolMsjC1()
{
    ++contMsj;
    tamProColaMsjC1+= Comp1.colMsj.size();
    Comp1.colMsj.push_back(Comp1.msjmalos.front());
    Comp1.msjmalos.pop_front();
    if(Comp1.Ser1)
    {
        Comp1.Ser1 = false;
        tiempo->push(Event(LIBSERV1C1,*reloj));
    }
    else if(Comp1.Ser2)
    {
        Comp1.Ser2 = false;
        tiempo->push(Event(LIBSERV2C1,*reloj));
    }
}

void Eventos::llegaMsjC2()
{
    Comp2.msj.push_back(Comp2.trans.front());
    if(Comp2.serv )
    {
        Comp2.serv = false;
        tiempo->push(Event(LIBSERVC2, *reloj));
    }
    Comp2.trans.pop_front();
}

void Eventos::libServC2()
{
    if (!Comp2.msj.empty())
    {
        if(aleatorio.porcentaje(80))
        {
            promMsjEnSist+= *reloj-msjEnSist[Comp2.msj[0]];
            Comp2.msj.pop_front();
            tiempo->push(Event(LIBSERVC2, *reloj+aleatorio.genExp(1)));
        }
        else
        {
            cout << "Mesaje " << Comp2.msj.front() << " venia malo"<< endl;
            float duracion = aleatorio.genExp(1);
            Comp1.msjmalos.push_back(Comp2.msj.front());
            Comp2.msj.pop_back();
            tiempo->push(Event(DEVOLMSJC1, *reloj+ duracion+3));
            tiempo->push(Event(LIBSERVC2,*reloj+duracion));
        }
    }
    else
    {
        Comp2.serv = true;
    }
}

void Eventos::llegaPaqC3()
{
    Comp3.paq.push_back(Comp3.trans.front());
    cout << "Llego el paquete " << Comp3.trans.front() << endl;
    if(Comp3.serv)
    {
        tiempo->push(Event(LIBSERVC3,*reloj));
    }
    Comp3.trans.pop_front();
}

void Eventos::libServC3()
{
    if(!Comp3.paq.empty())
    {
        cout << "Se esperaba el paquete " << Comp3.ack << " recivido el " << Comp3.paq.front() << endl;
        if(Comp3.ack == Comp3.paq.front())
        {
            Comp3.ack = (Comp3.ack + 1) % 100;
            Comp3.paqRecibidosBien.push_front(Comp3.paq.front());
            Comp3.paq.pop_front();
            tiempo->push(Event(LIBSERVC3,*reloj+ aleatorio.genNormal(1.5, 0.01)));
            Comp1.ack.push_back(Comp3.ack);
            tiempo->push(Event(LLEGAACK, *reloj + 2));
            *tiemp = * reloj + 20;
            Comp3.molestar = true;
        }
        else
        {
            Comp3.paq.pop_front();
            if(Comp3.molestar)
            {
                *tiemp = * reloj + 20;
                Comp1.ack.push_back(Comp3.ack);
                tiempo->push(Event(LLEGAACK, *reloj + 2));
            }
            tiempo->push(Event(LIBSERVC3,*reloj));
            Comp3.molestar = false;
        }
    }
    else
    {
        Comp3.serv = true;
    }
}

void Eventos::temp()
{
    Comp1.ack.push_back(Comp3.ack);
    *tiemp = *reloj +20;
    tiempo->push(Event(LLEGAACK, *reloj + 2));
}

void Eventos::libServ2C1()
{
    Comp1.Ser2 = false;
    if(!Comp1.colMsj.empty())
    {
        cout << "Enviando mensaje " << Comp1.colMsj.front() << endl;
        Comp2.trans.push_back(Comp1.colMsj.front());
        ++contMsj;
        tamProColaMsjC1+= Comp1.colMsj.size();
        Comp1.colMsj.pop_front();
        tiempo->push(Event(LIBSERV2C1,*reloj + aleatorio.distrubucion()));
        tiempo->push(Event(LLEGAMSJC2,*reloj+3 + aleatorio.distrubucion())); // 3 del tiempo de propagacion y 1 de distribución de probabilidad cuya
        // función de densidad es: f(x) = 2x/3 con x entre 1 y 2 segundos.
    }
    else
    {
        if (!Comp1.colPaq.empty() && (Comp1.evnPaq < 4 && Comp1.evnPaq < Comp1.colPaq.size()))
        {
            Comp1.evnPaq++;
            float duracion = aleatorio.genExp(0.5);
            cout << "Enviando paquete " << Comp1.colPaq[Comp1.evnPaq -1] << endl;
            if(aleatorio.porcentaje(95))
            {
                Comp3.trans.push_back(Comp1.colPaq[Comp1.evnPaq-1]);
                tiempo->push(Event(LLEGAPAQC3,*reloj + duracion + 2));
                tiemTransmision+= duracion+2;
                ++contTransmisiones;
            }
            else
            {
                cout << "El paquete " << Comp1.colPaq[Comp1.evnPaq -1] << " se perdio"<< endl;
            }
            tiempo->push(Event(LIBSERV2C1,*reloj + duracion));
        }

        else
        {
            Comp1.Ser2=true;
        }
    }
}

void Eventos::imprInfo()
{
    cout<<"El reloj del sistema: "<< *reloj <<endl;
    cout<<"Longitud de la cola mensajes: "<< Comp1.colMsj.size()<<endl;
    cout<<"Longitud de la cola paquetes: "<< Comp1.colPaq.size() <<endl;
    cout<<"En ventana: ";
    if(Comp1.colPaq.size()>0)
    {
        for (unsigned int i=0; i< Comp1.colPaq.size(); i++)
        {
            cout<<Comp1.colPaq[i]<<", ";
            if (i == 3)
                break;
        }

        cout<<" el resto: ";
        for (unsigned int i=4; i<Comp1.colPaq.size(); i++)
            cout<<Comp1.colPaq[i]<<", ";
    }
    cout<<"Enviados " << Comp1.evnPaq;
    cout<<" \n Ultimo ACK recibido por Serv. No.1: "<< Comp1.ultimoAck-1<<endl;
    cout<<"Ultimo ACK enviado por Serv. No.3,: "<< Comp3.ack-1 <<endl;
    cout<<"Paquetes correctamente recibidos por Serv. No.3: "<< Comp3.paqRecibidosBien.size() <<endl;
    cout<<"Paquetes recibidos bien en la comp3: "<<endl;
    for (unsigned int i=0; i<Comp3.paqRecibidosBien.size(); i++)
        cout<<Comp3.paqRecibidosBien[i]<<", ";
    // cout<<"Tipo de evento: "<<endl;

}

void Eventos::imprFinal()
{
    cout<<"\n\nSe esta preparando la siguiente corrida..\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cout<<"Datos al final de la corrida: \n";
    cout<<"Tamaño promedio de las colas en Serv. No.1:\n";
    promCpaq=tamProColaPaqC1/contPa;
    cout<<"Tamaño promedio de la cola de Paquetes: "<<promCpaq<<endl;
    promCmsj= tamPRoVentanaC1/contVent;
    cout<<"Tamaño promedio de la Ventana de Paquetes: "<<promCmsj<<endl;
    promCven=tamProColaMsjC1/contMsj;
    cout<<"Tamaño promedio de la cola de Mensajes: "<<promCven<<endl;
    permaPaq = promPaqEnSist/Comp3.paqRecibidosBien.size();
    cout<<"Tiempo promedio de permanencia de un paquete en el sistema: "<<permaPaq<<endl;
    permaMsj= promMsjEnSist/Comp1.conMsj;
    cout<<"Tiempo promedio de permanencia de un mensaje en el sistema: "<<permaMsj<<endl;
    promTrans = tiemTransmision/contTransmisiones;
    cout<<"Promedio del tiempo de transmision para un paquete(se pueden enviar varias veces el mismo paq): "<<promTrans<<endl;
    tiemServ= permaPaq/promTrans;
    cout<<"Tiempo promedio de servicio (para un paquete): "<<tiemServ<<endl;
    eficiencia= promTrans/tiemServ;
    cout<<"Eficiencia: "<<eficiencia<<endl;

}
