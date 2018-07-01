#include <LiquidCrystal.h>
#include "contador.h"
#include "temporizador.h"

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

class Mostrar
{
private:
  int decenas, unidades;

  void ver(int tiempo)
  {
    decenas = tiempo / 10;
    unidades = tiempo % 10;
    lcd.print(decenas);
    lcd.print(unidades);
  }

public:
  void PorLcd(Temporizador t)
  {
    // fila 0 "Temporizador 1"
    lcd.setCursor(0, 0);
    lcd.print("Temporizador ");
    lcd.print(t.getInstancia());

    // fila 1 "00:00:12"
    lcd.setCursor(0, 1);
    ver(t.reloj.Horas);
    lcd.print(":");
    ver(t.reloj.Minutos);
    lcd.print(":");
    ver(t.reloj.Segundos);
  }

  void PorSerial(Temporizador r)
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
};

Temporizador temp1(0, 0, 20), temp2(0, 1, 3);
Contador cambiarCnt;
Temporizador listTemporizadores[] = {temp1, temp2};

const int intPin = 2;
const int btnIniciar = 13;
const int btnMenuOk = 12;
const int btnChange = 11;

Mostrar mostrar;

void setup()
{
  lcd.begin(16, 2);
  listTemporizadores[0].setInstancia(1);
  listTemporizadores[1].setInstancia(2);
  cambiarCnt.setLimite(1);
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(intPin, INPUT_PULLUP);
  pinMode(btnIniciar, INPUT);
  pinMode(btnMenuOk, INPUT);
  pinMode(btnChange, INPUT);

  mostrar.PorSerial(*Actual());
  mostrar.PorLcd(*Actual());
  attachInterrupt(digitalPinToInterrupt(intPin), blink, CHANGE);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (digitalRead(btnIniciar) == HIGH)
  {
    delay(300);
    Actual()->IniciarDetener();
  }

  if (digitalRead(btnChange) == HIGH)
  {
    delay(300);
    cambiarCnt.incrementar();
    mostrar.PorSerial(*Actual());
  }

  if(digitalRead(btnMenuOk) == HIGH) {

  }
}

Temporizador *Actual()
{
  return &listTemporizadores[cambiarCnt.getContador()];
}

void blink()
{
  // mostrar.PorSerial(Actual());
  mostrar.PorLcd(*Actual());
  for (int list = 0; list < 2; list++)
  {
    listTemporizadores[list].decrementar();
  }
}