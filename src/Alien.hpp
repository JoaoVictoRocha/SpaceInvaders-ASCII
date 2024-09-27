#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "Nave.hpp"

class Alien : public Nave
{
public:
    Alien(const Nave &);

    bool getDir() const {return dir;}
    void activeDir();
    void disableDir();

    void shoot(ObjetoDeJogo &) override;

private:
    bool dir;
};

#endif