#include <LiquidCrystal.h>

class Reloj
{
public:
  Reloj() {}
  Reloj(int Horas, int Minutos, int Segundos)
  {
    horas = Horas;
    minutos = Minutos;
    segundos = Segundos;
  }

  int horas = 0;
  int minutos = 0;
  int segundos = 0;
};

class CuentaRegresiva
{
public:
  CuentaRegresiva(Reloj r)
  {
    reloj = r;
  }

  Reloj reloj;
  // cuanta hacia atras y devuelve el resultado
  Reloj iniciar()
  {
    if (reloj.segundos < 0)
    {
      reloj.minutos--;
      reloj.segundos = 59;
    }

    if (reloj.minutos < 0)
    {
      reloj.horas--;
      reloj.minutos = 59;
    }
    if (reloj.horas < 0)
      reloj.horas = 0;
    return reloj;
  }
};

class Temporizador
{
public:
  Temporizador() {}
}

Reloj r(1, 2, 3);
Reloj temporizadores[] = {r};

// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

bool pinLed = LOW;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Reloj temp = temporizadores[0];
  Serial.println("segundos =");
  Serial.println(temp.segundos);

  Serial.println("minutos =");
  Serial.println(temp.minutos);
}

void loop()
{
  // put your main code here, to run repeatedly:
}
