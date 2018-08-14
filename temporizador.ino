#include <EEPROM.h>

#include <LiquidCrystal.h>
#include "contador.h"
#include "temporizador.h"
#include "mostrar.h"
#include "btn.h"
#include "EditarTemporizador.h"

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

Temporizador
    temp1,
    temp2,
    temp3,
    temp4,
    *listTemporizadores[] = {&temp1, &temp2, &temp3, &temp4};

Contador
    cambiarCnt(3),
    programa(3),
    blinkCnt(2);

Btn btnIniciar(13),
    btnMenuOk(12),
    btnIncremento(11),
    btnDecremento(10);

Mostrar mostrar(&lcd);

Temporizador *Actual()
{
  return listTemporizadores[cambiarCnt.getContador()];
}

Blink myblink(&mostrar, Actual());
EditarTemporizador editarTemp(
    &myblink,
    &btnIncremento,
    &btnDecremento);

const int intPin = 2;

bool activar = true;

void setup()
{
  //  StructReloj myReloj = {0, 17, 0};
  //  EEPROM.put(4, myReloj);

  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(intPin, INPUT_PULLUP);

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
  if (btnMenuOk.click())
  {
    blinkCnt++;
  }

  LastProgram();
}

void listTimerConfig()
{
  lcd.setCursor(1, 0);
  lcd.print("CONFIGURAR");
  lcd.setCursor(1, 1);
  lcd.print("TEMPORIZADOR ");
  lcd.print(Actual()->getInstancia());

  changeTemp();

  if (btnMenuOk.click())
  {
    editarTemp.getTempActual(Actual());
    myblink.getTempActual(Actual());
    lcd.clear();
    programa++;
  }

  LastProgram();
}

void EditTemp()
{
  if (programa.getContador() == 2)
  {
    switch (blinkCnt.getContador())
    {
    case 0:
      editarTemp.editarSegundos();
      break;
    case 1:
      editarTemp.editarMinutos();
      break;
    case 2:
      editarTemp.editarHoras();
      break;
    }

    if (btnMenuOk.click())
    {
      Actual()->save();
    }
  }
  else
  {
    editarTemp.restore();
  }
}

void NextPrograma()
{
  if (btnMenuOk.click())
  {
    lcd.clear();
    programa++;
  }
}

void LastProgram()
{
  if (btnIniciar.click())
  {
    lcd.clear();
    programa--;
  }
}

void changeTemp()
{
  if (btnIncremento.click())
  {
    cambiarCnt++;
    mostrar.PorSerial(Actual());
  }

  if (btnDecremento.click())
  {
    cambiarCnt--;
    mostrar.PorSerial(Actual());
  }
}

void listTimer()
{
  mostrar.PorLcd(Actual());
  if (btnIniciar.click())
  {
    Actual()->IniciarDetener();
  }

  changeTemp();

  NextPrograma();
}

void interruption()
{
  // mostrar.PorSerial(Actual());
  for (int list = 0; list < 4; list++)
  {
    listTemporizadores[list]->decrementar();
  }

  EditTemp();
}