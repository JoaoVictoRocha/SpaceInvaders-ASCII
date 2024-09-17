#ifndef HERO_HPP
#define HERO_HPP

#include "Nave.hpp"
#include "Projetil.hpp"

class Hero : public Nave
{
public:
    Hero(const Nave &);
    ~Hero(){}

    void shoot() override;

};

#endif