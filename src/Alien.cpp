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