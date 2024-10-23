#ifndef NAVE_HPP
#define NAVE_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Nave : public ObjetoDeJogo
{
public:
    Nave(const ObjetoDeJogo &obj, int vidas, int velocidade);
    bool isAlive();
    void sofrerAtaque(ObjetoDeJogo &bullet);
    virtual void shoot(ObjetoDeJogo &);

    void setVelMovimento (int);
    inline int getVelMovimento () const {return velMovimento;}
protected:
    int velMovimento;
    int qtdVidas;
};

#endif