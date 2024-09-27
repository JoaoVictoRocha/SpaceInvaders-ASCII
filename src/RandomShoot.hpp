#ifndef RANDOM_SHOOT_HPP
#define RANDOM_SHOOT_HPP

#include "ASCII_Engine/ObjetoDeJogo.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "Alien.hpp"
#include "HandleBullet.hpp"
#include <random>

class RandomShoot
{
public:
    RandomShoot(Alien **aliens, ObjetoDeJogo **bullets, int tam, int div, int numBullets) 
        : aliens(aliens), bullets(bullets), tamanho(tam), div(div), numBullets(numBullets) {}

    void randomShoot() {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, tamanho);

        int random_number = distrib(gen);

        // Decide qual alien vai disparar baseado no número aleatório
        if ( random_number % div == 0 && (random_number / div - 1) < tamanho) 
        {
            // Procure um projétil disponível e dispare
            for (int i = 0; i < numBullets; ++i) 
            {
                if (HandleBullet::checkAlien(*aliens[random_number / div - 1], *bullets[i])) {
                    break;
                }
            }
        }
    }

private:
    int tamanho;
    int div;
    int numBullets;
    Alien **aliens;
    ObjetoDeJogo **bullets;
};

#endif