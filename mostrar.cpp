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

void Mostrar::PorLcd(Temporizador *t)
{
    // fila 0 "Temporizador 1"
    lcd->setCursor(0, 0);
    lcd->print("Temporizador ");
    lcd->print(t->getInstancia());

    // fila 1 "00:00:12"
    lcd->setCursor(0, 1);
    if (_showHour)
        ver(t->reloj.Horas);
    else
        lcd->print("  ");

    lcd->print(":");

    if (_showMinutes)
        ver(t->reloj.Minutos);
    else
        lcd->print("  ");

    lcd->print(":");

    if (_showSeconds)
        ver(t->reloj.Segundos);
    else
        lcd->print("  ");
}

void Mostrar::HiddenSeconds()
{
    _showSeconds = false;
}

void Mostrar::ShowSeconds()
{
    _showSeconds = true;
}

void Mostrar::HiddenMinutes()
{
    _showMinutes = false;
}

void Mostrar::ShowMinutes()
{
    _showMinutes = true;
}

void Mostrar::ShowHour()
{
    _showHour = true;
}

void Mostrar::HiddenHour()
{
    _showHour = false;
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
