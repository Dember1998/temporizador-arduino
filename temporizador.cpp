#include "temporizador.h"

Temporizador::Temporizador()
{
    instancia = NInstancia++;
    Restaurar();
}

int Temporizador::NInstancia = 1;

int Temporizador::getInstancia() { return instancia; }
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

void Temporizador::IncSegundos()
{
    reloj.Segundos++;
    if (reloj.Segundos > 59)
    {
        reloj.Segundos = 0;
    }
}

void Temporizador::DecSegundos()
{
    reloj.Segundos--;
    if (reloj.Segundos < 0)
    {
        reloj.Segundos = 59;
    }
}

void Temporizador::IncMinutos()
{
    reloj.Minutos++;
    if (reloj.Minutos > 59)
    {
        reloj.Minutos = 0;
    }
}

void Temporizador::DecMinutos()
{
    reloj.Minutos--;
    if (reloj.Minutos < 0)
    {
        reloj.Minutos = 59;
    }
}

void Temporizador::IncHoras()
{
    reloj.Horas++;
    if (reloj.Horas > 23)
        reloj.Horas = 0;
}

void Temporizador::DecHoras()
{
    reloj.Horas--;
    if (reloj.Horas < 0)
        reloj.Horas = 23;
}

void Temporizador::Restaurar()
{
    StructReloj myReloj;
    EEPROM.get(instancia, myReloj);

    reloj.Segundos = myReloj.Segundos;
    reloj.Minutos = myReloj.Minutos;
    reloj.Horas = myReloj.Horas;
}

void Temporizador::save()
{
    StructReloj myReloj;

    myReloj.Segundos = reloj.Segundos;
    myReloj.Minutos = reloj.Minutos;
    myReloj.Horas = reloj.Horas;

    EEPROM.put(instancia, myReloj);
    Serial.println("datos guardados");
}
