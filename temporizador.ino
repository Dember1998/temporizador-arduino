#include <LiquidCrystal.h>
#include "contador.h"
#include "temporizador.h"
#include "mostrar.h"

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
Temporizador temp1(0, 0, 20), temp2(0, 1, 3), temp3(0, 1, 2), temp4(0, 1, 0);
Contador cambiarCnt, programa;
Temporizador listTemporizadores[] = {temp1, temp2, temp3, temp4};

const int intPin = 2;
const int btnIniciar = 13;
const int btnMenuOk = 12;
const int btnIncremento = 11;
const int btnDecremento = 10;

Mostrar mostrar(&lcd);

void setup()
{
  lcd.begin(16, 2);
  listTemporizadores[0].setInstancia(1);
  listTemporizadores[1].setInstancia(2);
  listTemporizadores[2].setInstancia(3);
  listTemporizadores[3].setInstancia(4);

  cambiarCnt.setLimite(3);
  programa.setLimite(1);
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(intPin, INPUT_PULLUP);
  pinMode(btnIniciar, INPUT);
  pinMode(btnMenuOk, INPUT);
  pinMode(btnIncremento, INPUT);
  pinMode(btnDecremento, INPUT);

  mostrar.PorSerial(*Actual());
  mostrar.PorLcd(*Actual());
  attachInterrupt(digitalPinToInterrupt(intPin), blink, CHANGE);
}

void loop()
{
  if (programa.getContador() == 0)
  {
    listTimer();
  }
}

void listTimer()
{
  mostrar.PorLcd(*Actual());
  if (digitalRead(btnIniciar) == HIGH)
  {
    delay(300);
    Actual()->IniciarDetener();
  }

  if (digitalRead(btnIncremento) == HIGH)
  {
    delay(300);
    cambiarCnt++;
    mostrar.PorSerial(*Actual());
  }

  if (digitalRead(btnDecremento) == HIGH)
  {
    delay(300);
    cambiarCnt--;
    mostrar.PorSerial(*Actual());
  }

  if (digitalRead(btnMenuOk) == HIGH)
  {
  }
}

Temporizador *Actual()
{
  return &listTemporizadores[cambiarCnt.getContador()];
}

void blink()
{
  // mostrar.PorSerial(Actual());
  for (int list = 0; list < 2; list++)
  {
    listTemporizadores[list].decrementar();
  }
}