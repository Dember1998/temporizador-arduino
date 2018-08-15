#include "mostrar.h"
// --------------- class Mostrar ----------------------
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

void Mostrar::verHoras()
{
    if (_showHour)
        ver(Temp_Actual->reloj.Horas);
    else
        lcd->print("  ");
}

void Mostrar::verMinutos()
{
    if (_showMinutes)
        ver(Temp_Actual->reloj.Minutos);
    else
        lcd->print("  ");
}

void Mostrar::verSegundos()
{
    if (_showSeconds)
        ver(Temp_Actual->reloj.Segundos);
    else
        lcd->print("  ");
}

void Mostrar::PorLcd(Temporizador *t)
{
    // fila 0 "Temporizador 1"
    Temp_Actual = t;
    lcd->setCursor(1, 0);
    lcd->print("TEMPORIZADOR ");
    lcd->print(t->getInstancia());

    // fila 1 "00:00:12"
    lcd->setCursor(4, 1);

    verHoras();

    lcd->print(":");

    verMinutos();

    lcd->print(":");

    verSegundos();
}

void Mostrar::PorSerial(Temporizador *r)
{
    Serial.print("Temporizador ");
    Serial.print(r->getInstancia());
    Serial.print("-> ");

    Serial.print(" horas : ");
    Serial.print(r->reloj.Horas);

    Serial.print(" minutos : ");
    Serial.print(r->reloj.Minutos);

    Serial.print(" segundos : ");
    Serial.println(r->reloj.Segundos);
}

//-------------class BanderasMostrar---------------------

void BanderasMostrar::HiddenSeconds()
{
    _showSeconds = false;
}

void BanderasMostrar::ShowSeconds()
{
    _showSeconds = true;
}

void BanderasMostrar::HiddenMinutes()
{
    _showMinutes = false;
}

void BanderasMostrar::ShowMinutes()
{
    _showMinutes = true;
}

void BanderasMostrar::ShowHour()
{
    _showHour = true;
}

void BanderasMostrar::HiddenHour()
{
    _showHour = false;
}

// ----------------class Blink----------------------

void Blink::Seconds()
{
    ShowHour();
    ShowMinutes();

    PorLcd(TempActual);
    _myCnt++;

    if (_myCnt == 2)
        ShowSeconds();
    else if (_myCnt == 3)
    {
        HiddenSeconds();
        _myCnt = 0;
    }
}

void Blink::Minutes()
{
    ShowSeconds();
    ShowHour();

    PorLcd(TempActual);
    _myCnt++;

    if (_myCnt == 2)
        ShowMinutes();
    else if (_myCnt == 3)
    {
        HiddenMinutes();
        _myCnt = 0;
    }
}

void Blink::Hour()
{
    ShowSeconds();
    ShowMinutes();

    PorLcd(TempActual);
    _myCnt++;

    if (_myCnt == 2)
        ShowHour();
    else if (_myCnt == 3)
    {
        HiddenHour();
        _myCnt = 0;
    }
}

void Blink::restore()
{
    ShowSeconds();
    ShowMinutes();
    ShowHour();
}

void Blink::getTempActual(Temporizador *actual)
{
    TempActual = actual;
}
