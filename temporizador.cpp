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

void Temporizador::IncSegundos() {
    reloj.Segundos++;
    if (reloj.Segundos > 59)
    {
        reloj.Segundos = 0;
    }
}

void Temporizador::Restaurar()
{
    Reloj relojTemporal;
    EEPROM.get(instancias, relojTemporal);

    if (relojTemporal.Segundos > 0 && relojTemporal.Minutos > 0 && relojTemporal.Horas > 0)
    {
        reloj = relojTemporal;
    }
    else
    {
        reloj.Segundos = Segundos;
        reloj.Minutos = Minutos;
        reloj.Horas = Horas;
    }
}

void Temporizador::save()
{
    EEPROM.put(instancias, reloj);
}
