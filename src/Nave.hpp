#ifndef NAVE_HPP
#define NAVE_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Nave : public ObjetoDeJogo
{
public:
    Nave(const ObjetoDeJogo &obj, int vidas);
    ~Nave(){}
    bool isAlive();
    void sofrerAtaque();
    virtual void shoot(ObjetoDeJogo &);
protected:
    int qtdVidas;
};

#endif