#include "contador.h"

Contador::Contador() {}

Contador::Contador(int limite) {
    Limite = limite;
}

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
    if (cnt > 0)
    {
        cnt--;
    }
}

int Contador::getContador() { return cnt; };

void Contador::setLimite(int limite = 0) { Limite = limite; }
