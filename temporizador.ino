#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
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
