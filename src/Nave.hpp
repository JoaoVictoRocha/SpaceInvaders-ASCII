#ifndef NAVE_HPP
#define NAVE_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Nave : public ObjetoDeJogo
{
public:
    Nave(const ObjetoDeJogo &obj, int vidas);
    bool isAlive();
    void sofrerAtaque(ObjetoDeJogo &bullet);
    virtual void shoot(ObjetoDeJogo &);
protected:
    int qtdVidas;
};

#endif