#ifndef FASE_LEVEL_3_HPP
#define FASE_LEVEL_3_HPP

#include "ASCII_Engine/Fase.hpp"
#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "Hero.hpp"
#include "Alien.hpp"
#include "HandleBullet.hpp"
#include <conio.h>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <windows.h>
#include <random>

class FaseLevel3 : public Fase
{
public:
    FaseLevel3(const std::string &n, const Sprite &bkg);
    ~FaseLevel3();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
    void capturarTecla();
    void pausar(int);
    
private:
    Hero *hero;
    Alien *alien[15];
    ObjetoDeJogo *bulletHero[3];
    ObjetoDeJogo *bulletAlien[15];
    ObjetoDeJogo *vidasTxt;
    ObjetoDeJogo *vidas[3];
    ObjetoDeJogo *nivel;
    ObjetoDeJogo *gameOver;
    ObjetoDeJogo *congrats;
    std::atomic<bool> flag;
};

#endif