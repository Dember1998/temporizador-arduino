#include <Arduino.h>
#include <LiquidCrystal.h>
#include "temporizador.h"

class Mostrar
{
  private:
    int decenas, unidades;
    LiquidCrystal *lcd;

    void ver(int tiempo);

  public:
    Mostrar(LiquidCrystal *mylcd);

    void PorLcd(Temporizador t);

    void PorSerial(Temporizador r);
};