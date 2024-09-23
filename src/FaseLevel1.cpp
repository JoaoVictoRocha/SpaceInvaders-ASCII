#include "FaseLevel1.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include <iostream>
#include <conio.h>

#include <random>

#include "HandleBullet.hpp"

void FaseLevel1::capturarTecla()
{
    while (this->flag.load()) {

        char tecla = _getch();

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && hero->getPosC() > 0)
            hero->moveLeft(2);

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && hero->getPosC() <= 323)
            hero->moveRight(2);

        if ( tecla == 32)
        {
            for (int i = 0; i<5; ++i)
            {
                HandleBullet::check(*hero, *bulletHero[i]);
            }
        }

        if ( tecla == 27 )
        {
            this->flag.store(false);
            break;
        }
    }
}

void FaseLevel1::pausar(int milissegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milissegundos));
}

void FaseLevel1::init()
{
    hero = new Hero(Nave(ObjetoDeJogo("Heroi", Sprite("rsc/hero.img"), 68, 177), 3));
    objs.push_back(hero);

    alien[0] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo1.img"), 0, 314), 1));
    objs.push_back(alien[0]);

    alien[1] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo1.img"), 0, 275), 1));
    objs.push_back(alien[1]);

    alien[2] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo1.img"), 0, 236), 1));
    objs.push_back(alien[2]);

    alien[3] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo1.img"), 0, 197), 1));
    objs.push_back(alien[3]);

    alien[4] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo1.img"), 0, 158), 1));
    objs.push_back(alien[4]);

    for (int i = 0; i < 5; ++i)
    {
        bulletHero[i] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 6, hero->getPosL() + 13 );
        bulletHero[i]->desativarObj();
        objs.push_back(bulletHero[i]);
    }

    for (int j = 0; j < 5; ++j)
    {
        bulletAlien[j] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilAlien.img"), 0, 0);
        bulletAlien[j]->desativarObj();
        objs.push_back(bulletAlien[j]);
    }
}

unsigned FaseLevel1::run(SpriteBuffer &screen)
{
    this->draw(screen);
    system("cls");
    this->show(screen);

    this->flag.store(true);

    std::thread tecladoFase1(capturarTecla, this);

    short cont = 0;

    while(this->flag.load())
    {
        if (cont == 5)
            return Fase::LEVEL_2;
        // Eventos de colisão
        for (int k = 0; k < 5; ++k)
        {
            for (int t = 0; t < 5; ++t)
            {
                if (alien[k]->colideCom(*bulletHero[t]))
                { 
                    if (bulletHero[t]->getActive())
                        alien[k]->sofrerAtaque();
                    bulletHero[t]->desativarObj();
                    if (!alien[k]->isAlive())
                    {
                        alien[k]->desativarObj();
                        ++cont;
                    }
                }
            }
            if (hero->colideCom(*bulletAlien[k]))
            {
                hero->sofrerAtaque();
                bulletAlien[k]->desativarObj();
                if (!hero->isAlive())
                    return Fase::GAME_OVER;
            }
        }

        // Gera números aleatorios

        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> distrib(1, 50);
        int random_number = distrib(gen);

        // Disparo de alien
        if (random_number == 10)
            HandleBullet::check(*alien[0], *bulletAlien[0]);
        else if (random_number == 20)
            HandleBullet::check(*alien[1], *bulletAlien[1]);
        else if (random_number == 30)
            HandleBullet::check(*alien[2], *bulletAlien[2]);
        else if (random_number == 40)
            HandleBullet::check(*alien[3], *bulletAlien[3]);
        else if (random_number == 50)
            HandleBullet::check(*alien[4], *bulletAlien[4]);

        // Implementação responsável por mover os aliens
        for (int i = 0; i < 5; ++i)
        {
            if (alien[i]->isAlive())
            {
                if (alien[i]->getDir() )
                {
                    alien[i]->moveRight(2);
                    if (alien[i]->getPosC() >= 314)
                        alien[i]->disableDir();
                }
                else {
                    alien[i]->moveLeft(2);
                    if (alien[i]->getPosC() <= 0)
                        alien[i]->activeDir();
                }
            }
        }
        // Implementação responsável por mover os projeteis
        for (int j = 0; j < 5; ++j)
        {
            if (bulletAlien[j]->getActive())
            {
                if (bulletAlien[j]->getPosL() >= 75)
                    bulletAlien[j]->desativarObj();
                bulletAlien[j]->moveDown(4);
            }   

            if (bulletHero[j]->getActive())
            {
                if (bulletHero[j]->getPosL() <= 0)
                    bulletHero[j]->desativarObj();
                bulletHero[j]->moveUp(6);
            }
        }
        
        screen.clear();
        this->update();
        this->draw(screen);
        this->show(screen);
        pausar(45);
        system("cls");
        
    }

    return Fase::END_GAME;

}

