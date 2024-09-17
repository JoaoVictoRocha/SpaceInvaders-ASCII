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

    projetilHero[0] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[0]->desativarObj();
    objs.push_back(projetilHero[0]);

    projetilHero[1] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[1]->desativarObj();
    objs.push_back(projetilHero[1]);

    projetilHero[2] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[2]->desativarObj();
    objs.push_back(projetilHero[2]);

    projetilHero[3] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[3]->desativarObj();
    objs.push_back(projetilHero[3]);

    projetilHero[4] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[4]->desativarObj();
    objs.push_back(projetilHero[4]);

    projetilHero[5] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[5]->desativarObj();
    objs.push_back(projetilHero[5]);

    projetilHero[6] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[6]->desativarObj();
    objs.push_back(projetilHero[6]);

    projetilHero[7] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[7]->desativarObj();
    objs.push_back(projetilHero[7]);

    projetilHero[8] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[8]->desativarObj();
    objs.push_back(projetilHero[8]);

    projetilHero[9] = new Projetil(ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 7, hero->getPosL() + 13 ));
    projetilHero[9]->desativarObj();
    objs.push_back(projetilHero[9]);
    /*
    projetilAlien[0] = nullptr;
    objs.push_back(projetilAlien[0]);

    projetilAlien[1] = nullptr;
    objs.push_back(projetilAlien[1]);

    projetilAlien[2] = nullptr;
    objs.push_back(projetilAlien[2]);

    projetilAlien[3] = nullptr;
    objs.push_back(projetilAlien[3]);

    projetilAlien[4] = nullptr;
    objs.push_back(projetilAlien[4]);
    */
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
        for (int i = 0; i < 5; ++i)
        {
            if (alien[i]->isAlive())
            {
                if (alien[i]->getDir() )
                {
                    alien[i]->moveRight(3);
                    if (alien[i]->getPosC() >= 314)
                        alien[i]->disableDir();
                }
                else {
                    alien[i]->moveLeft(3);
                    if (alien[i]->getPosC() <= 0)
                        alien[i]->activeDir();
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

