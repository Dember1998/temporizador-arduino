#include <Arduino.h>
#include <LiquidCrystal.h>
#include "temporizador.h"

class Mostrar
{
private:
  int decenas, unidades;
  LiquidCrystal *lcd;
  bool _showSeconds = true;
  bool _showMinutes = true;
  bool _showHour = true;

  void ver(int tiempo);

public:
  Mostrar(LiquidCrystal *mylcd);

  void PorLcd(Temporizador *t);

  void HiddenSeconds();
  void ShowSeconds();

  void HiddenMinutes();
  void ShowMinutes();

  void HiddenHour();
  void ShowHour();

  void PorSerial(Temporizador *r);
};

class Blink
{
private:
  Mostrar *_mostrar;
  int _myCnt = 0;
  Temporizador *TempActual;

public:
  Blink(Mostrar *mostrar, Temporizador *actual);

  void Seconds();
  void Minutes();
  void Hour();
};
