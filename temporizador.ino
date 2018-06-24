#include <LiquidCrystal.h>

class Reloj
{
public:
  Reloj() {}
  Reloj(int segundos, int minutos, int horas)
  {
    Horas = horas;
    Minutos = minutos;
    Segundos = segundos;
  }

  int Horas = 0;
  int Minutos = 0;
  int Segundos = 0;
};

class Temporizador : private Reloj
{
private:
  Reloj reloj;

public:
  Temporizador(int segundos, int minutos, int horas)
  {
    reloj.Segundos = segundos;
    reloj.Minutos = minutos;
    reloj.Horas = horas;

    Segundos = segundos;
    Minutos = minutos;
    Horas = horas;
  }

  Reloj iniciar()
  {
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

    return reloj;
  }
};

// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

bool pinLed = LOW;
void setup()
{
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void verTemporizador(Reloj reloj)
{
  Serial.print("segundos : ");
  Serial.print(reloj.Segundos);

  Serial.print(" minutos : ");
  Serial.print(reloj.Minutos);

  Serial.print(" horas :");
  Serial.print(reloj.Horas);
}