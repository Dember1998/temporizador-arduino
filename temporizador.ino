#include <LiquidCrystal.h>

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

class Temporizador : private Reloj
{
private:
  Reloj reloj;

public:
  Temporizador(int horas, int minutos, int segundos)
  {
    reloj.Segundos = segundos;
    reloj.Minutos = minutos;
    reloj.Horas = horas;

    Segundos = segundos;
    Minutos = minutos;
    Horas = horas;
  }

  void decrementar()
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
  }

  void verPorSerial()
  {
    Serial.print(" horas : ");
    Serial.print(reloj.Horas);

    Serial.print(" minutos : ");
    Serial.print(reloj.Minutos);

    Serial.print(" segundos : ");
    Serial.println(reloj.Segundos);
  }
};

// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Temporizador temp1(0, 5, 10);
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  temp1.verPorSerial();
  temp1.decrementar();
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void verPorSerial(Reloj reloj)
{
  Serial.print("segundos : ");
  Serial.print(reloj.Segundos);

  Serial.print(" minutos : ");
  Serial.print(reloj.Minutos);

  Serial.print(" horas :");
  Serial.print(reloj.Horas);
}