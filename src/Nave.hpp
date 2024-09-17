#ifndef NAVE_HPP
#define NAVE_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Nave : public ObjetoDeJogo
{
public:
    Nave(const ObjetoDeJogo &obj, int vidas);
    ~Nave(){}
    bool isAlive();
    virtual void shoot(){}
    void sofrerAtaque();
protected:
    int qtdVidas;
};

#endif