#include "mostrar.h"

void Mostrar::ver(int tiempo)
{
    decenas = tiempo / 10;
    unidades = tiempo % 10;
    lcd->print(decenas);
    lcd->print(unidades);
}

Mostrar::Mostrar(LiquidCrystal *mylcd)
{
    lcd = mylcd;
}

void Mostrar::PorLcd(Temporizador t)
{
    // fila 0 "Temporizador 1"
    lcd->setCursor(0, 0);
    lcd->print("Temporizador ");
    lcd->print(t.getInstancia());

    // fila 1 "00:00:12"
    lcd->setCursor(0, 1);
    ver(t.reloj.Horas);
    lcd->print(":");
    ver(t.reloj.Minutos);
    lcd->print(":");
    ver(t.reloj.Segundos);
}

void Mostrar::PorSerial(Temporizador r)
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
