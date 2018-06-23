#include <LiquidCrystal.h>

class Reloj
{
public:
  int horas = 0;
  int minutos = 0;
  int segundos = 0;
};


LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
bool pinLed = LOW;
void setup()
{
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("hola con arduino");
}

void loop()
{
  // put your main code here, to run repeatedly:
}
