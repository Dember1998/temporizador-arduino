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

  cambiarCnt.setLimite(3);
  programa.setLimite(2);
  // put your setup code here, to run once:
  Serial.begin(9600);

  setPinMode();

  mostrar.PorSerial(*Actual());
  mostrar.PorLcd(*Actual());
  attachInterrupt(digitalPinToInterrupt(intPin), blink, CHANGE);
}

void loop()
{
  switch (programa.getContador())
  {
  case 0:
    listTimer();
    break;

  case 1:
    listTimerConfig();
    break;
  }
}

void listTimerConfig()
{
  lcd.setCursor(1, 0);
  lcd.print("configurar");
  lcd.setCursor(1, 1);
  lcd.print("temporizador ");
  lcd.print(Actual()->getInstancia());

  changeTemp();
}

void setPinMode()
{
  pinMode(intPin, INPUT_PULLUP);
  pinMode(btnIniciar, INPUT);
  pinMode(btnMenuOk, INPUT);
  pinMode(btnIncremento, INPUT);
  pinMode(btnDecremento, INPUT);
}

void changeTemp()
{

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
}

void listTimer()
{
  mostrar.PorLcd(*Actual());
  if (digitalRead(btnIniciar) == HIGH)
  {
    delay(300);
    Actual()->IniciarDetener();
  }

  changeTemp();

  if (digitalRead(btnMenuOk) == HIGH)
  {
    delay(300);
    lcd.clear();
    programa++;
  }
}

Temporizador *Actual()
{
  return &listTemporizadores[cambiarCnt.getContador()];
}

void blink()
{
  // mostrar.PorSerial(Actual());
  for (int list = 0; list < 4; list++)
  {
    listTemporizadores[list].decrementar();
  }
}