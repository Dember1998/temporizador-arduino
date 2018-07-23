#include <Arduino.h>

class Contador
{
  private:
    int cnt = 0;
    int Limite = 0;

  public:
    void operator ++ (int);
    void operator --(int);
    int getContador();

    void setLimite(int limite = 0);
};