#ifndef HANDLEBULLET_HPP
#define HANDLEBULLET_HPP

#include "Hero.hpp"
#include "Alien.hpp"

class HandleBullet
{
public:
    HandleBullet(){}
    ~HandleBullet(){}

    static void checkAlien(Alien &alien, ObjetoDeJogo &bullet)
    {
        if (alien.getActive() && !bullet.getActive())
        {
            alien.shoot(bullet);
        }
    }
    static bool checkHero(Hero &hero, ObjetoDeJogo &bullet)
    {
        if (hero.getActive() && !bullet.getActive())
        {
            hero.shoot(bullet);
            return true;
        }
        return false;
    }

};

#endif