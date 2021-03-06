#include "temporizador.h"

Temporizador::Temporizador(int horas, int minutos, int segundos)
{
    Segundos = segundos;
    Minutos = minutos;
    Horas = horas;
    Restaurar();
}

void Temporizador::Restaurar()
{
    reloj.Segundos = Segundos;
    reloj.Minutos = Minutos;
    reloj.Horas = Horas;
}

void Temporizador::setSegundos(int s = 0) { Segundos = s; }
void Temporizador::setMinutos(int m = 0) { Minutos = m; }
void Temporizador::setHoras(int h = 0) { Horas = h; }

void Temporizador::setInstancia(int i) { instancias = i; }
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
