#include "Hero.hpp"

Hero::Hero(const Nave &n) : Nave(n)
{
}

void Hero::shoot(ObjetoDeJogo &bullet)
{
    bullet.moveTo(this->getPosL() - 7, this->getPosC() + 10);
    bullet.ativarObj();
}