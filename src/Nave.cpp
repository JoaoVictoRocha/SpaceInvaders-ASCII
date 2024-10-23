#include "Nave.hpp"

Nave::Nave(const ObjetoDeJogo &obj, int vidas, int velocidade) : ObjetoDeJogo(obj), qtdVidas(vidas), velMovimento(velocidade)
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

void Nave::setVelMovimento(int velocidade)
{
    if (velocidade > 0)
        velMovimento = velocidade;
}