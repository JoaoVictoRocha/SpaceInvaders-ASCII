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

void Nave::sofrerAtaque(ObjetoDeJogo &bullet)
{
    --qtdVidas;
    bullet.desativarObj();
}

void Nave::shoot(ObjetoDeJogo &obj)
{
}