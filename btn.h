#ifndef btn_h
#define btn_h

#include <Arduino.h>

class Btn
{
private:
  int Pin;
  bool oldstate;

  void delay_btn()
  {
    delay(50);
  }

public:
  Btn(int pin, String mode = "input")
  {
    Pin = pin;
    pinMode(pin, INPUT);
  }

  bool click()
  {
    if (digitalRead(Pin) == HIGH)
    {
      this->delay_btn();
      oldstate = true;
    }

    if (oldstate && digitalRead(Pin) == LOW)
    {
      this->delay_btn();
      oldstate = false;
      return true;
    }

    return false;
  }
};

#endif
