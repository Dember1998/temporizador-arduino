#ifndef temporizador_h
#define temporizador_h
#include <Arduino.h>
#include "reloj.h"
#include <EEPROM.h>

class Temporizador : private Reloj
{
private:
  int instancia;
  bool activar;
  static int NInstancia;

public:
  Temporizador(int horas, int minutos, int segundos);

  Reloj reloj;

  void Restaurar();
  void save();

  void setInstancia(int i);
  int getInstancia();
  void IniciarDetener();

  void decrementar();

  void IncSegundos();
  void DecSegundos();

  void IncMinutos();
  void DecMinutos();

  void IncHoras();
  void DecHoras();
};
#endif
