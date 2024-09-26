#include "FaseLevel2.hpp"
#include <random>

FaseLevel2::FaseLevel2(const std::string &n, const Sprite &bkg) : Fase(n, bkg)
{
}

FaseLevel2::~FaseLevel2()
{
    delete hero;

    for(int i = 0; i<10; ++i)
    {
        delete alien[i];
        delete bulletAlien[i];
    }
    for (int j = 0; j<3; ++j)
    {
        delete bulletHero[j];
    }
}

void FaseLevel2::capturarTecla()
{
    while (this->flag.load()) {

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && hero->getPosC() > 0)
        {
            pausar(50);
            hero->moveLeft(4);
        }

        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && hero->getPosC() <= 323)
        {
            pausar(50);
            hero->moveRight(4);
        }

        if (GetAsyncKeyState(VK_SPACE) & 0X8000)
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

void FaseLevel2::pausar(int milissegundos) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milissegundos));
}

void FaseLevel2::init()
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

    alien[5] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo2.img"), 10, 314), 2));
    objs.push_back(alien[5]);

    alien[6] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo2.img"), 10, 275), 2));
    objs.push_back(alien[6]);

    alien[7] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo2.img"), 10, 236), 2));
    objs.push_back(alien[7]);

    alien[8] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo2.img"), 10, 197), 2));
    objs.push_back(alien[8]);

    alien[9] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo2.img"), 10, 158), 2));
    objs.push_back(alien[9]);

    for (int j = 0; j < 10; ++j)
    {   
        if (j < 3)
        {
            bulletHero[j] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilHero.img"), hero->getPosC() - 6, hero->getPosL() + 13 );
            bulletHero[j]->desativarObj();
            objs.push_back(bulletHero[j]);
        }

        bulletAlien[j] = new ObjetoDeJogo("Projetil", Sprite("rsc/projetilAlien.img"), 0, 0);
        bulletAlien[j]->desativarObj();
        objs.push_back(bulletAlien[j]);
    }
}

unsigned FaseLevel2::run(SpriteBuffer &screen)
{
    this->draw(screen);
    system("cls");
    this->show(screen);

    this->flag.store(true);

    std::thread tecladoFase2(capturarTecla, this);

    short cont = 0;

    while(this->flag.load())
    {
        if (cont == 10)
            return Fase::LEVEL_COMPLETE;
        
        for (int i = 0; i<10; ++i)
        {
            // eventos de colisão
            for (int t = 0; t<3; ++t)
            {
                if (bulletHero[t]->getActive())
                {
                    if (alien[i]->colideComBordas(*bulletHero[t]))
                    {
                        alien[i]->sofrerAtaque(*bulletHero[t]);
                        if (!alien[i]->isAlive())
                        {
                            alien[i]->desativarObj();
                            ++cont;
                        }
                    }
                    
                }
            }
            if (hero->colideComBordas(*bulletAlien[i]))
            {
                hero->sofrerAtaque(*bulletAlien[i]);
                if (!hero->isAlive())
                    return Fase::GAME_OVER;
            }

            // Implementação responsável por mover alien
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
            if (i < 3)
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
        std::uniform_int_distribution<> distrib(1, 60);
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
            case 36:
                HandleBullet::checkAlien(*alien[5], *bulletAlien[5]);
                break;
            case 42:
                HandleBullet::checkAlien(*alien[6], *bulletAlien[6]);
                break;
            case 48:
                HandleBullet::checkAlien(*alien[7], *bulletAlien[7]);
                break;
            case 54:
                HandleBullet::checkAlien(*alien[8], *bulletAlien[8]);
                break;
            case 60:
                HandleBullet::checkAlien(*alien[9], *bulletAlien[9]);
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

    return Fase::GAME_OVER;
}