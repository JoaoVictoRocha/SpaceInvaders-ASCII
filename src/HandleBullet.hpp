#ifndef HANDLEBULLET_HPP
#define HANDLEBULLET_HPP

#include "Hero.hpp"
#include "Alien.hpp"

class HandleBullet
{
public:
    HandleBullet(){}
    ~HandleBullet(){}

    static void check(Alien &alien, ObjetoDeJogo &bullet)
    {
        if (!bullet.getActive())
        {
            
        }
    }
    static void check(Hero &hero, ObjetoDeJogo &bullet)
    {
        if (!bullet.getActive())
        {
            hero.shoot(bullet);
        }
    }

};

#endif