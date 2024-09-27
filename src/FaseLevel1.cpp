#include "FaseLevel1.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include <iostream>

#include <random>

#include "HandleBullet.hpp"
#include "RandomShoot.hpp"

FaseLevel1::FaseLevel1(std::string n, const Sprite &bkg) : Fase(n,bkg) 
{

}

FaseLevel1::~FaseLevel1()
{
    delete hero;
    delete vidasTxt;
    delete nivel;
    delete gameOver;

    for(int i = 0; i<5; ++i)
    {
        delete alien[i];
        delete bulletAlien[i];
    }
    for (int j = 0; j<3; ++j)
    {
        delete bulletHero[j];
        delete vidas[j];
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
    hero = new Hero(Nave(ObjetoDeJogo("Heroi", Sprite("rsc/hero.img"), 98, 177), 3));
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

    vidasTxt = new ObjetoDeJogo("Vidas", Sprite("rsc/vidaExtraTxt.img"), 5, 360);
    objs.push_back(vidasTxt);

    vidas[0] = new ObjetoDeJogo("Vidas", Sprite("rsc/hero.img"), 12, 360);
    objs.push_back(vidas[0]);

    vidas[1] = new ObjetoDeJogo("Vidas", Sprite("rsc/hero.img"), 12, 390);
    objs.push_back(vidas[1]);

    vidas[2] = new ObjetoDeJogo("Vidas", Sprite("rsc/hero.img"), 27, 360);
    objs.push_back(vidas[2]);

    nivel = new ObjetoDeJogo("Nivel", Sprite("rsc/nivel1.img"), 70, 380);
    objs.push_back(nivel);

    gameOver = new ObjetoDeJogo("GameOver", Sprite("rsc/gameOver.img"), 45, 150);
    gameOver->desativarObj();
    objs.push_back(gameOver);

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

    RandomShoot controlShoot(alien, bulletAlien, 30, 6, 5);

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
                if (alien[i]->colideCom(*bulletHero[t]))
                { 
                    alien[i]->sofrerAtaque(*bulletHero[t]);
                    if (!alien[i]->isAlive())
                    {
                        alien[i]->desativarObj();
                        ++cont;
                    }
                }
            }
            if (hero->colideCom(*bulletAlien[i]))
            {
                hero->sofrerAtaque(*bulletAlien[i]);
                for (int j = 2; j >= 0; j--)
                {
                    if (vidas[j]->getActive())
                    {
                        vidas[j]->desativarObj();
                        break;
                    }
                }
                if (!hero->isAlive())
                {
                    gameOver->ativarObj();
                    screen.clear();
                    this->draw(screen);
                    this->show(screen);
                    this->flag.store(false);
                    tecladoFase1.join();
                    return Fase::GAME_OVER;
                }
            }

            // Implementação responsável por mover os aliens
            alien[i]->update();

            // Implementação responsável por mover os projeteis
            if (bulletAlien[i]->getActive())
            {
                if (bulletAlien[i]->getPosL() >= 105)
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
        // Gera números aleatorios, com base no número emite o disparo do alien
        controlShoot.randomShoot();
        
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

