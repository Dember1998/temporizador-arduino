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
    lcd->setCursor(1, 0);
    lcd->print("TEMPORIZADOR ");
    lcd->print(t->getInstancia());

    // fila 1 "00:00:12"
    lcd->setCursor(4, 1);
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

Blink::Blink(Mostrar *mostrar, Temporizador *actual)
{
    _mostrar = mostrar;
    TempActual = actual;
}

void Blink::Seconds()
{
    _mostrar->ShowHour();
    _mostrar->ShowMinutes();

    _mostrar->PorLcd(TempActual);
    _myCnt++;

    if (_myCnt == 2)
        _mostrar->ShowSeconds();
    else if (_myCnt == 3)
    {
        _mostrar->HiddenSeconds();
        _myCnt = 0;
    }
}

void Blink::Minutes()
{
    _mostrar->ShowSeconds();
    _mostrar->ShowHour();

    _mostrar->PorLcd(TempActual);
    _myCnt++;

    if (_myCnt == 2)
        _mostrar->ShowMinutes();
    else if (_myCnt == 3)
    {
        _mostrar->HiddenMinutes();
        _myCnt = 0;
    }
}

void Blink::Hour()
{
    _mostrar->ShowSeconds();
    _mostrar->ShowMinutes();

    _mostrar->PorLcd(TempActual);
    _myCnt++;

    if (_myCnt == 2)
        _mostrar->ShowHour();
    else if (_myCnt == 3)
    {
        _mostrar->HiddenHour();
        _myCnt = 0;
    }
}

void Blink::restore()
{
    _mostrar->ShowSeconds();
    _mostrar->ShowMinutes();
    _mostrar->ShowHour();
}

void Blink::getTempActual(Temporizador *actual)
{
    TempActual = actual;
}
