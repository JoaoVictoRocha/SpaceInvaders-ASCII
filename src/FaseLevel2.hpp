#ifndef FASE_LEVEL_2_HPP
#define FASE_LEVEL_2_HPP

#include "ASCII_Engine/Fase.hpp"
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "Hero.hpp"
#include "Alien.hpp"
#include "HandleBullet.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <windows.h>

class FaseLevel2 : public Fase
{
public:
    FaseLevel2(const std::string &n, const Sprite &bkg);
    ~FaseLevel2();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
    void capturarTecla();
    void pausar(int);

private:
    Hero *hero;
    Alien *alien[10];
    ObjetoDeJogo *bulletHero[3];
    ObjetoDeJogo *bulletAlien[10];
    ObjetoDeJogo *vidasTxt;
    ObjetoDeJogo *vidas[3];
    ObjetoDeJogo *nivel;
    ObjetoDeJogo *gameOver;
    std::atomic<bool> flag;
};

#endif