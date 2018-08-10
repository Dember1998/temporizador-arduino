#include "temporizador.h"

Temporizador::Temporizador(int horas, int minutos, int segundos)
{
    Segundos = segundos;
    Minutos = minutos;
    Horas = horas;
    Restaurar();
    instancias = NInstancia++;
}

int Temporizador::NInstancia = 1;

void Temporizador::Restaurar()
{
    reloj.Segundos = Segundos;
    reloj.Minutos = Minutos;
    reloj.Horas = Horas;
}


int Temporizador::getInstancia() { return instancias; }
void Temporizador::IniciarDetener()
{
    activar = !activar;
}

void Temporizador::decrementar()
{
    if (activar == false)
    {
        return;
    }

    if (reloj.Horas == 0 && reloj.Minutos == 0 && reloj.Segundos == 0)
    {
        Restaurar();
        activar = false;
        return;
    }

    reloj.Segundos--;
    if (reloj.Segundos < 0)
    {
        reloj.Minutos--;
        reloj.Segundos = 59;
    }

    if (reloj.Minutos < 0)
    {
        reloj.Horas--;
        reloj.Minutos = 59;
    }
    if (reloj.Horas < 0)
        reloj.Horas = 0;
}
