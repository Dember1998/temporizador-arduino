#ifndef mostrar_h
#define mostrar_h
#include <Arduino.h>
#include <LiquidCrystal.h>
#include "temporizador.h"

class BanderasMostrar
{
protected:
  bool _showSeconds = true;
  bool _showMinutes = true;
  bool _showHour = true;

public:
  void HiddenSeconds();
  void ShowSeconds();

  void HiddenMinutes();
  void ShowMinutes();

  void HiddenHour();
  void ShowHour();
};

class Mostrar : public BanderasMostrar
{
private:
  int decenas, unidades;
  LiquidCrystal *lcd;
  Temporizador *Temp_Actual;

  void ver(int tiempo);

  void verSegundos();
  void verMinutos();
  void verHoras();

public:
  Mostrar(LiquidCrystal *mylcd);

  void PorLcd(Temporizador *t);

  void PorSerial(Temporizador *r);
};

class Blink : public Mostrar
{
private:
  int _myCnt = 0;
  Temporizador *TempActual;

public:
  Blink::Blink(Temporizador *actual, LiquidCrystal *mylcd) : Mostrar(mylcd)
  {
    TempActual = actual;
  }

  void Seconds();
  void Minutes();
  void Hour();

  void restore();
  void getTempActual(Temporizador *actual);
};
#endif
