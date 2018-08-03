#include <Arduino.h>
#include <LiquidCrystal.h>
#include "temporizador.h"

class Mostrar
{
  private:
    int decenas, unidades;
    LiquidCrystal *lcd;
    bool _showSeconds = true;

    void ver(int tiempo);

  public:
    Mostrar(LiquidCrystal *mylcd);

    void PorLcd(Temporizador t);
    void HiddenSeconds();
    void ShowSeconds();

    void PorSerial(Temporizador r);
};