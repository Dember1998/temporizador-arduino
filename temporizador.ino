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
  bool activar;

public:
  Temporizador(int horas, int minutos, int segundos)
  {
    Segundos = segundos;
    Minutos = minutos;
    Horas = horas;
    Restaurar();
  }

  Reloj reloj;

  void Restaurar()
  {
    reloj.Segundos = Segundos;
    reloj.Minutos = Minutos;
    reloj.Horas = Horas;
  }

  void setSegundos(int s = 0) { Segundos = s; }
  void setMinutos(int m = 0) { Minutos = m; }
  void setHoras(int h = 0) { Horas = h; }

  void setInstancia(int i) { instancias = i; }
  int getInstancia() { return instancias; }
  void IniciarDetener()
  {
    activar = !activar;
    ;
  }

  void decrementar()
  {
    if (activar == false)
    {
      return;
    }

    if (reloj.Horas == 0 && reloj.Minutos == 0 && reloj.Segundos == 0)
    {
      Restaurar();
      activar = false;
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

class Contador
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
    if (cnt > 0)
    {
      cnt--;
    }
  }

  int getContador() { return cnt; };

  void setLimite(int limite = 0) { Limite = limite; }
};

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

class Vista
{
  void adelante() {}
  void atras() {}
  Contador vistasCnt;
  void vistaLCD(int cnt)
  {
  }
};

Temporizador temp1(0, 0, 20),
    temp2(0, 1, 3);
Contador cambiarCnt, menuCnt;
Temporizador listTemporizadores[] = {temp1, temp2};

const int intPin = 2;
const int btnIniciar = 13;
const int btnMenuOk = 12;
const int btnIncrementar = 11;
const int btnDecrementar = 10;

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
  pinMode(btnIncrementar, INPUT);
  pinMode(btnDecrementar, INPUT);

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

  if (digitalRead(btnIncrementar) == HIGH)
  {
    delay(300);
    cambiarCnt.incrementar();
    mostrar.PorSerial(*Actual());
  }

  if (digitalRead(btnDecrementar) == HIGH)
  {
    delay(300);
    cambiarCnt.decrementar();
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
  mostrar.PorLcd(*Actual());
  for (int list = 0; list < 2; list++)
  {
    listTemporizadores[list].decrementar();
  }
}