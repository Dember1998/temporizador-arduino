#include <Arduino.h>

class Contador
{
  private:
    int cnt = 0;
    int Limite = 0;

  public:
    void incrementar();

    void decrementar();

    int getContador();

    void setLimite(int limite = 0);
};