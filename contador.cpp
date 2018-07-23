#include "contador.h"

void Contador::operator++(int)
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

void Contador::operator--(int)
{
    if (cnt >= Limite)
    {
        cnt--;
    }
}

int Contador::getContador() { return cnt; };

void Contador::setLimite(int limite = 0) { Limite = limite; }
