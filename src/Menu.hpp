#ifndef MENU_HPP
#define MENU_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Fase.hpp"

#include <atomic>
#include <thread>
#include <chrono>
#include <windows.h>
#include <string>
#include <conio.h>

class Menu : public Fase
{
public:
    Menu(const std::string &, const Sprite &);
    ~Menu();

    virtual void init();
    virtual unsigned run(SpriteBuffer &screen);
    void capturarTecla();
    void pausar(int);

private:
    ObjetoDeJogo *menu;
    ObjetoDeJogo *seta;
    ObjetoDeJogo *start;
    ObjetoDeJogo *exit;
    int escolha;
    std::atomic<bool> flag;
};

#endif