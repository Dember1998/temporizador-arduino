#include "temporizador.h"

Temporizador::Temporizador(int horas, int minutos, int segundos)
{
    Segundos = segundos;
    Minutos = minutos;
    Horas = horas;
    Restaurar();
    instancia = NInstancia++;
}

Temporizador::Temporizador() {
    reloj.Segundos = 0;
    reloj.Minutos = 0;
    reloj.Horas = 0;
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
    Reloj relojTemporal;
    EEPROM.get(instancia, relojTemporal);

   // if (relojTemporal.Segundos > 0 && relojTemporal.Minutos > 0 && relojTemporal.Horas > 0)
  //  {
       // reloj = relojTemporal;
 //   }
 //   else
 //   {
        reloj.Segundos = Segundos;
        reloj.Minutos = Minutos;
        reloj.Horas = Horas;
 //   }
}

void Temporizador::save()
{
    EEPROM.put(instancia, reloj);
}
