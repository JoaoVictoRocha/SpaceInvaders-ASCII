#ifndef HERO_HPP
#define HERO_HPP

#include "Nave.hpp"

class Hero : public Nave
{
public:
    Hero(const Nave &);

    void shoot(ObjetoDeJogo &) override;
};

#endif