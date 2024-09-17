#ifndef PROJETIL_HPP
#define PROJETIL_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"

class Projetil : public ObjetoDeJogo
{
public:
    Projetil(const ObjetoDeJogo &obj) : ObjetoDeJogo(obj) 
    {}
    ~Projetil(){}

};

#endif