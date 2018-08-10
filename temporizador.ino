#include <LiquidCrystal.h>
#include "contador.h"
#include "temporizador.h"
#include "mostrar.h"

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

Temporizador
    temp1(0, 0, 20),
    temp2(0, 1, 3),
    temp3(0, 1, 2),
    temp4(0, 1, 0),
    listTemporizadores[] = {temp1, temp2, temp3, temp4};

Contador
    cambiarCnt(3),
    programa(3),
    blinkCnt(2);

Mostrar mostrar(&lcd);

const int
    intPin = 2,
    btnIniciar = 13,
    btnMenuOk = 12,
    btnIncremento = 11,
    btnDecremento = 10;

bool
    editTemp = false,
    activar = true;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);

  setPinMode();

  mostrar.PorSerial(Actual());
  mostrar.PorLcd(Actual());
  attachInterrupt(digitalPinToInterrupt(intPin), interruption, CHANGE);
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
  if (digitalRead(btnMenuOk) == HIGH)
  {
    delay_btn();
    blinkCnt++;
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

  btnOk();
}

Blink myblink(&mostrar, Actual());

void EditTemp()
{
  if (editTemp)
  {
    switch (blinkCnt.getContador())
    {
    case 0:
      myblink.Seconds();
      break;
    case 1:
      myblink.Minutes();
      break;
    case 2:
      myblink.Hour();
      break;
    }
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
    mostrar.PorSerial(Actual());
  }

  if (digitalRead(btnDecremento) == HIGH)
  {
    delay_btn();
    cambiarCnt--;
    mostrar.PorSerial(Actual());
  }
}

void listTimer()
{
  mostrar.PorLcd(Actual());
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

void interruption()
{
  // mostrar.PorSerial(Actual());
  for (int list = 0; list < 4; list++)
  {
    listTemporizadores[list].decrementar();
  }

  EditTemp();
}