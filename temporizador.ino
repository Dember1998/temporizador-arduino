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

public:
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

class Temporizador : private Reloj
{
public:
  Temporizador() {

  }

  void setSegundos(int s) { segundos = s; }
  void setMinutos(int m) { minutos = m; }
  void setHoras(int h) { horas = h; }

  Reloj getReloj()
  {
    Reloj reloj(horas, minutos, horas);
    return reloj;
  }

// declementa y un objeto tipo cuenta regresiva
  CuentaRegresiva decrementar()
  {
    Reloj reloj(horas, minutos, horas);
    CuentaRegresiva cuenta(reloj);
  }
};

// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

bool pinLed = LOW;
void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}
