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

class CuentaRegresiva : Reloj
{
public:
  CuentaRegresiva(Reloj reloj)
  {
    horas = reloj.horas;
    minutos = reloj.minutos;
    segundos = reloj.segundos;
  }

  // cuanta hacia atras y devuelve el resultado
  Reloj iniciar()
  {
    if (segundos < 0)
    {
      minutos--;
      segundos = 59;
    }

    if (minutos < 0)
    {
      horas--;
      minutos = 59;
    }
    if (horas < 0)
      horas = 0;
    Reloj r(horas, minutos, segundos);
    return r;
  }
};
Reloj r(1, 2, 3);
Reloj temporizadores[] = {r};

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

bool pinLed = LOW;
void setup()
{
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("hola con arduino");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
