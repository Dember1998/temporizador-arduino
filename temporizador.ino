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
  int instancias;

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

  Reloj reloj;

  void setInstancia(int i) { instancias = i; }
  int getInstancia() { return instancias; }

  void decrementar()
  {
    if (reloj.Horas == 0 && reloj.Minutos == 0 && reloj.Segundos == 0)
    {
      return;
    }
    else
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
  }
};

// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Temporizador temp1(0, 0, 20), temp2(1, 2, 3);

const int intPin = 2;
const int btnIniciar = 13;
const int btnDetener = 12;

void setup()
{

  temp1.setInstancia(1);
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(intPin, INPUT_PULLUP);
  pinMode(btnIniciar, INPUT);
  pinMode(btnDetener, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (digitalRead(btnIniciar) == HIGH)
  {
    attachInterrupt(digitalPinToInterrupt(intPin), blink, CHANGE);
  }

  if (digitalRead(btnDetener) == HIGH)
  {
    detachInterrupt(digitalPinToInterrupt(intPin));
  }
}

void verPorSerial(Temporizador r)
{
  Serial.print("Temporizador ");
  Serial.print(r.getInstancia());
  Serial.print("-> ");

  Serial.print(" horas : ");
  Serial.print(r.reloj.Horas);

  Serial.print(" minutos : ");
  Serial.print(r.reloj.Minutos);

  Serial.print(" segundos : ");
  Serial.println(r.reloj.Segundos);
}

void blink()
{
  verPorSerial(temp1);
  temp1.decrementar();
}