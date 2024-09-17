#ifndef ALIEN_HPP
#define ALIEN_HPP

#include "Nave.hpp"

class Alien : public Nave
{
public:
    Alien(const Nave &);
    ~Alien(){}

    bool getDir() const {return dir;}
    void activeDir();
    void disableDir();

private:
    bool dir;
};

#endif