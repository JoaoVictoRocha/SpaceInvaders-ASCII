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

class FaseLevel3 : public Fase
{
public:
    FaseLevel3();
    ~FaseLevel3();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
    void capturarTecla();
    void pausar(int);
    
private:
    Hero *hero;
    Alien *alien[15];
    ObjetoDeJogo *bulletHero[5];
    ObjetoDeJogo *bulletAlien[15];

    std::atomic<bool> flag;
};

#endif