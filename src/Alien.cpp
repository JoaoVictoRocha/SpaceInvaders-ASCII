#include "Alien.hpp"

Alien::Alien(const Nave &n) : Nave(n), dir(false)
{
}

void Alien::activeDir()
{
    this->dir = true;
}

void Alien::disableDir()
{
    this->dir = false;
}

void Alien::shoot(ObjetoDeJogo &bullet)
{
    if (this->getName() == "Alien1")
    {
        bullet.moveTo( this->getPosL()  , this->getPosC() );
        bullet.ativarObj();
    }
    else if (this->getName() == "Alien2")
    {
        bullet.moveTo(this->getPosL(), this->getPosC());
        bullet.ativarObj();
    } else {
        bullet.moveTo(this->getPosL(), this->getPosC());
        bullet.ativarObj();
    }
    bullet.ativarObj();
}