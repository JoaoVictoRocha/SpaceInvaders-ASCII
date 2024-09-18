#ifndef FASE1_HPP
#define FASE1_HPP

#include "Hero.hpp"
#include "Alien.hpp"
#include "ASCII_Engine/Fase.hpp"

#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <windows.h>

class FaseLevel1 : public Fase
{
public:
    FaseLevel1(std::string n, const Sprite &bkg) : Fase(n,bkg) {}
    virtual ~FaseLevel1(){}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
    void capturarTecla();
    void moverAlien();
    void pausar(int);

    void handleBullet();
    //void shoot();
    
private:
    Hero *hero;
    Alien *alien[5];
    ObjetoDeJogo *bulletHero[5];
    ObjetoDeJogo *bulletAlien[5];

    std::atomic<bool> flag;

    std::list<ObjetoDeJogo*> colisoes;
};

#endif