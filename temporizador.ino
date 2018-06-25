#include <LiquidCrystal.h>

class Reloj
{
public:
  Reloj() {}
  Reloj(int horas, int minutos, int segundos)
  {
    Horas = horas;
    Minutos = minutos;
    Segundos = segundos;
  }

  int Horas = 0;
  int Minutos = 0;
  int Segundos = 0;
};

class Temporizador : private Reloj
{
private:
  int instancias;
  bool activar = false;

public:
  Temporizador(int horas, int minutos, int segundos)
  {
    reloj.Segundos = segundos;
    reloj.Minutos = minutos;
    reloj.Horas = horas;

    Segundos = segundos;
    Minutos = minutos;
    Horas = horas;
  }

  Reloj reloj;

  void setInstancia(int i) { instancias = i; }
  int getInstancia() { return instancias; }
  void Activar() { activar = true; }
  void desActivar() { activar = false; }

  void decrementar()
  {
    if (!activar)
    {
      return;
    }
    
    if (reloj.Horas == 0 && reloj.Minutos == 0 && reloj.Segundos == 0)
    {
      return;
    }

    reloj.Segundos--;
    if (reloj.Segundos < 0)
    {
      reloj.Minutos--;
      reloj.Segundos = 59;
    }

    if (reloj.Minutos < 0)
    {
      reloj.Horas--;
      reloj.Minutos = 59;
    }
    if (reloj.Horas < 0)
      reloj.Horas = 0;
  }
};

class Change
{
private:
  int cnt = 0;
  int Limite = 0;

public:
  void incrementar()
  {
    if (cnt < Limite)
    {
      cnt++;
    }
    else
    {
      cnt = 0;
    }
  }

  void decrementar()
  {
    if (cnt > Limite)
    {
      cnt--;
    }
  }

  int getContador() { return cnt; };

  void setLimite(int limite = 0) { Limite = limite; }
};

// LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
Temporizador temp1(0, 0, 20), temp2(1, 2, 3);
Change cambiar;
Temporizador listTemporizadores[] = {temp1, temp2};

const int intPin = 2;
const int btnIniciar = 13;
const int btnDetener = 12;
const int btnChange = 11;

void setup()
{
  listTemporizadores[0].setInstancia(1);
  listTemporizadores[1].setInstancia(2);
  cambiar.setLimite(1);
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(intPin, INPUT_PULLUP);
  pinMode(btnIniciar, INPUT);
  pinMode(btnDetener, INPUT);
  pinMode(btnChange, INPUT);

  verPorSerial(listTemporizadores[cambiar.getContador()]);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (digitalRead(btnIniciar) == HIGH)
  {
    attachInterrupt(digitalPinToInterrupt(intPin), blink, CHANGE);
  }

  if (digitalRead(btnDetener) == HIGH)
  {
    detachInterrupt(digitalPinToInterrupt(intPin));
  }

  if (digitalRead(btnChange) == HIGH)
  {
    delay(300);
    cambiar.incrementar();
    verPorSerial(listTemporizadores[cambiar.getContador()]);
  }
}

void verPorSerial(Temporizador r)
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

void blink()
{
  verPorSerial(listTemporizadores[cambiar.getContador()]);
  listTemporizadores[cambiar.getContador()].decrementar();
}