#include "FaseLevel1.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include <iostream>

#include <random>

#include "HandleBullet.hpp"

FaseLevel1::FaseLevel1(std::string n, const Sprite &bkg) : Fase(n,bkg) 
{

}

FaseLevel1::~FaseLevel1()
{
    delete hero;

    for(int i = 0; i<5; ++i)
    {
        delete alien[i];
        delete bulletAlien[i];
    }
    for (int j = 0; j<3; ++j)
    {
        delete bulletHero[j];
    }
}

void FaseLevel1::capturarTecla()
{
    while (this->flag.load()) {

        if ( (GetAsyncKeyState(VK_LEFT) & 0x8000) && ( hero->getPosC() > 0) )
        {
            pausar(50);
            hero->moveLeft(4);
        }

        else if ( (GetAsyncKeyState(VK_RIGHT) & 0x8000) && (hero->getPosC() <= 323) )
        {
            pausar(50);
            hero->moveRight(4);
        }

        else if (GetAsyncKeyState(VK_SPACE) & 0X8000)
        {
            pausar(200);
            for (int i = 0; i<3; ++i)
            {
                if(HandleBullet::checkHero(*hero, *bulletHero[i]))
                    break;
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            this->flag.store(false);
            break;
        }
        
    }
}

void FaseLevel1::pausar(int milissegundos) 
{
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
        if (i<3)
        {
            bulletHero[i] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 6, hero->getPosL() + 13 );
            bulletHero[i]->desativarObj();
            objs.push_back(bulletHero[i]);
        }

        bulletAlien[i] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilAlien.img"), 0, 0);
        bulletAlien[i]->desativarObj();
        objs.push_back(bulletAlien[i]);
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
        {
            this->flag.store(false);
            tecladoFase1.join();
            return Fase::LEVEL_COMPLETE;
        }
        // Eventos de colisão
        for (int i = 0; i < 5; ++i)
        {
            for (int t = 0; t < 3; t++)
            {
                if (alien[i]->colideComBordas(*bulletHero[t]))
                { 
                    if (bulletHero[t]->getActive())
                        alien[i]->sofrerAtaque(*bulletHero[t]);
                    if (!alien[i]->isAlive())
                    {
                        alien[i]->desativarObj();
                        ++cont;
                    }
                }
            }
            if (hero->colideComBordas(*bulletAlien[i]))
            {
                hero->sofrerAtaque(*bulletAlien[i]);
                if (!hero->isAlive())
                    return Fase::GAME_OVER;
            }

            // Implementação responsável por mover os aliens
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

            // Implementação responsável por mover os projeteis
            if (bulletAlien[i]->getActive())
            {
                if (bulletAlien[i]->getPosL() >= 75)
                    bulletAlien[i]->desativarObj();
                bulletAlien[i]->moveDown(3);
            }   
            if (i<3)
            {
                if (bulletHero[i]->getActive())
                {
                    if (bulletHero[i]->getPosL() <= 0)
                        bulletHero[i]->desativarObj();
                    else {
                        bulletHero[i]->moveUp(3);
                    }
                }
            }

        }
        // Gera números aleatorios
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 30);
        int random_number = distrib(gen);

        // Disparo de alien

        switch(random_number)
        {
            case 6:
                HandleBullet::checkAlien(*alien[0], *bulletAlien[0]);
                break;
            case 12:
                HandleBullet::checkAlien(*alien[1], *bulletAlien[1]);
                break;
            case 18:
                HandleBullet::checkAlien(*alien[2], *bulletAlien[2]);
                break;
            case 24:
                HandleBullet::checkAlien(*alien[3], *bulletAlien[3]);
                break;
            case 30:
                HandleBullet::checkAlien(*alien[4], *bulletAlien[4]);
                break;
            default:
                break;
        }
        
        screen.clear();
        this->update();
        this->draw(screen);
        this->show(screen);
        pausar(60);
        system("cls");
        
    }

    tecladoFase1.join();
    return Fase::END_GAME;

}

