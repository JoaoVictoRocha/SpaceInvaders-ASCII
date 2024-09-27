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
    FaseLevel1(std::string n, const Sprite &bkg);
    virtual ~FaseLevel1();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
    void capturarTecla();
    void pausar(int);
    
private:
    Hero *hero;
    Alien *alien[5];
    ObjetoDeJogo *bulletHero[3];
    ObjetoDeJogo *bulletAlien[5];
    ObjetoDeJogo *vidasTxt;
    ObjetoDeJogo *vidas[3];
    ObjetoDeJogo *nivel;
    ObjetoDeJogo *gameOver;
    std::atomic<bool> flag;
};

#endif