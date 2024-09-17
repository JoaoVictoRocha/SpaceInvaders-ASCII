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
    virtual ~FaseLevel1(){delete [] hero; for (int i = 0; i<5; ++i) {delete [] alien[i];}}

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
    void capturarTecla();
    void moverAlien();
    void pausar(int);

    void shoot();
    
private:
    Hero *hero;
    Alien *alien[5];
    ObjetoDeJogo *projetilHero[15];
    ObjetoDeJogo *projetilAlien[5];

    std::atomic<bool> flag;

    std::list<ObjetoDeJogo*> colisoes;
};

#endif