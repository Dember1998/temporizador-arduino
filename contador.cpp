#include "contador.h"

void Contador::incrementar()
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

void Contador::decrementar()
{
    if (cnt > Limite)
    {
        cnt--;
    }
}

int Contador::getContador() { return cnt; };

void Contador::setLimite(int limite = 0) { Limite = limite; }
