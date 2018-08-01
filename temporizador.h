#ifndef temporizador_h
#define temporizador_h
#include <Arduino.h>
#include "reloj.h"

class Temporizador : private Reloj
{
private:
  int instancias;
  bool activar;
  static int NInstancia;

public:
  Temporizador(int horas, int minutos, int segundos);

  Reloj reloj;

  void Restaurar();

  void setSegundos(int s = 0);
  void setMinutos(int m = 0);
  void setHoras(int h = 0);

  void setInstancia(int i);
  int getInstancia();
  void IniciarDetener();

  void decrementar();
};
#endif
