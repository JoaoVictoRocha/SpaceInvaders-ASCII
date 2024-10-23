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
        bullet.moveTo( this->getPosL() + 12 , this->getPosC() + 10);
        bullet.ativarObj();
    }
    else if (this->getName() == "Alien2")
    {
        bullet.moveTo(this->getPosL() + 10, this->getPosC() + 13);
        bullet.ativarObj();
    } else {
        bullet.moveTo(this->getPosL() + 14, this->getPosC() + 13);
        bullet.ativarObj();
    }
    bullet.ativarObj();
}

void Alien::update()
{
    // Movimentação do alien
    if (isAlive())
    {
        if (dir)
        {
            moveRight(this->getVelMovimento());
            if (getPosC() >= 314)  // Limite direito
                disableDir();
        }
        else
        {
            moveLeft(this->getVelMovimento());
            if (getPosC() <= 0)  // Limite esquerdo
                activeDir();
        }
    }
    // Chamar o update da classe base para manter a funcionalidade original
    Nave::update();
}