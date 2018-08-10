#ifndef EditarTemporizador_h
#define EditarTemporizador_h
#include "Arduino.h"
#include "mostrar.h"
#include "btn.h"
#include "temporizador.h"

class EditarTemporizador
{
  private:
    Blink *blink;
    Temporizador *TempActual;
    Btn *BtnIncremento;
    Btn *BtnDecremento;

  public:
    EditarTemporizador(
        Blink *blink,
        Temporizador *tempActual,
        Btn *btnIncremento,
        Btn *btnDecremento)
    {
        this->blink = blink;
        TempActual = tempActual;
        BtnIncremento = btnIncremento;
        BtnDecremento = btnDecremento;
    }

    void editarSegundos()
    {
        blink->Seconds();

        if (BtnIncremento->click())
        {
            TempActual->IncSegundos();
        }

        if (BtnDecremento->click())
        {
            TempActual->DecSegundos();
        }
    }

    void editarMinutos()
    {
        blink->Minutes();

        if (BtnIncremento->click())
        {
            TempActual->IncMinutos();
        }

        if (BtnDecremento->click())
        {
            TempActual->DecMinutos();
        }
    }

    void editarHoras()
    {
        blink->Hour();
        if (BtnIncremento->click())
        {
            TempActual->IncHoras();
        }

        if (BtnDecremento->click())
        {
            TempActual->DecHoras();
        }
    }
};

#endif