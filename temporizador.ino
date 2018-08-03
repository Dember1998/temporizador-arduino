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
bool editTemp = false;
bool activar = true;

Mostrar mostrar(&lcd);

void setup()
{
  lcd.begin(16, 2);

  cambiarCnt.setLimite(3);
  programa.setLimite(3);
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

  case 2:
    setTimer();
    break;
  }
}

void setTimer()
{
  editTemp = true;
}

void listTimerConfig()
{
  lcd.setCursor(1, 0);
  lcd.print("configurar");
  lcd.setCursor(1, 1);
  lcd.print("temporizador ");
  lcd.print(Actual()->getInstancia());

  changeTemp();

  btnOk();
}

int mycnt = 0;
void EditTemp()
{
  mycnt++;
  if (mycnt == 2)
    activar = false;
  else if (mycnt == 3)
  {
    activar = true;
    mycnt = 0;
  }

  if (editTemp)
  {
    mostrar.PorLcd(*Actual());
    if (activar)
    {
      mostrar.ShowSeconds();
    }
    else
      mostrar.HiddenSeconds();
  }
}

void btnOk()
{
  if (digitalRead(btnMenuOk) == HIGH)
  {
    delay_btn();
    lcd.clear();
    programa++;
  }
}

void setPinMode()
{
  pinMode(intPin, INPUT_PULLUP);
  pinMode(btnIniciar, INPUT);
  pinMode(btnMenuOk, INPUT);
  pinMode(btnIncremento, INPUT);
  pinMode(btnDecremento, INPUT);
}

void delay_btn()
{
  delay(300);
}

void changeTemp()
{

  if (digitalRead(btnIncremento) == HIGH)
  {
    delay_btn();
    cambiarCnt++;
    mostrar.PorSerial(*Actual());
  }

  if (digitalRead(btnDecremento) == HIGH)
  {
    delay_btn();
    cambiarCnt--;
    mostrar.PorSerial(*Actual());
  }
}

void listTimer()
{
  mostrar.PorLcd(*Actual());
  if (digitalRead(btnIniciar) == HIGH)
  {
    delay_btn();
    Actual()->IniciarDetener();
  }

  changeTemp();

  btnOk();
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

  EditTemp();
}