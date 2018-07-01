#include <Arduino.h>

class Reloj
{
  public:
    Reloj() {}
    Reloj(int horas, int minutos, int segundos)
    {
        Horas = horas;
        Minutos = minutos;
        Segundos = segundos;
    }

    int Horas = 0;
    int Minutos = 0;
    int Segundos = 0;
};