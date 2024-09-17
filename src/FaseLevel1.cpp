#include "FaseLevel1.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include <iostream>
#include <conio.h>

void FaseLevel1::shoot()
{
    for (int i = 0; i < 10; ++i)
    {
        if ( ! projetilHero[i]->getActive() )
        {
            projetilHero[i]->ativarObj();
            projetilHero[i]->moveTo( (hero->getPosL() - 7 ), (hero->getPosC() + 10));
            
            break;
        }
    }
}

void FaseLevel1::capturarTecla()
{
    while (this->flag.load()) {

        char tecla = _getch();

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && hero->getPosC() > 0)
            hero->moveLeft();

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && hero->getPosC() <= 323)
            hero->moveRight();

        if ( tecla == 32)
            this->shoot();

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

    alien[1] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo1.img"), 0, 275), 1));
    objs.push_back(alien[1]);

    alien[2] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo1.img"), 0, 236), 1));
    objs.push_back(alien[2]);

    alien[3] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo1.img"), 0, 197), 1));
    objs.push_back(alien[3]);

    alien[4] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo1.img"), 0, 158), 1));
    objs.push_back(alien[4]);

    for (int i = 0; i<15; ++i)
    {
        projetilHero[i] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 );
        projetilHero[i]->desativarObj();
        objs.push_back(projetilHero[i]);
    }

    for (int j = 0; j < 5; ++j)
    {
        projetilAlien[j] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilAlien.img"), 0, 0);
        projetilAlien[j]->desativarObj();
        objs.push_back(projetilAlien[j]);
    }
}

unsigned FaseLevel1::run(SpriteBuffer &screen)
{
    this->draw(screen);
    system("cls");
    this->show(screen);

    this->flag.store(true);

    std::thread tecladoFase1(capturarTecla, this);

    while(this->flag.load())
    {
        // Implementação responsável por mover os aliens
        for (int i = 0; i < 5; ++i)
        {
            if (alien[i]->isAlive())
            {
                if (alien[i]->getDir() )
                {
                    alien[i]->moveRight(5);
                    if (alien[i]->getPosC() >= 314)
                        alien[i]->disableDir();
                }
                else {
                    alien[i]->moveLeft(5);
                    if (alien[i]->getPosC() <= 0)
                        alien[i]->activeDir();
                }
            }
        }
        // Implementação responsável por mover os projeteis
        for (int j = 0; j < 15; ++j)
        {
            if (j < 5)
            {
                if (projetilAlien[j]->getActive())
                    projetilAlien[j]->moveDown(3);
            }
            if (projetilHero[j]->getActive())
                projetilHero[j]->moveUp(3);
        }
        
        // Eventos de colisão
        for (int k = 0; k < 15; ++k)
        {
            if (alien[k]->colideComBordas(*projetilHero[k]))
            {
                alien[k]->sofrerAtaque();
                if (!alien[k]->isAlive())
                    alien[k]->desativarObj();
            }
            if (k < 5)
            {
                if (hero->colideComBordas(*projetilAlien[k]))
                {
                    hero->sofrerAtaque();
                    if (!hero->isAlive())
                        return Fase::GAME_OVER;
                }
            }
        }

        screen.clear();
        update();
        this->draw(screen);
        this->show(screen);
        pausar(150);
        system("cls");
        
    }

    return Fase::END_GAME;

}

