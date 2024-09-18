#include "Nave.hpp"

Nave::Nave(const ObjetoDeJogo &obj, int vidas) : ObjetoDeJogo(obj), qtdVidas(vidas)
{
}

bool Nave::isAlive()
{
    if (qtdVidas > 0)
        return true;
    return false;
}

void Nave::sofrerAtaque()
{
    --qtdVidas;
}

void Nave::shoot(ObjetoDeJogo &obj)
{
}