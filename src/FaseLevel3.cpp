#include "FaseLevel3.hpp"

FaseLevel3::FaseLevel3(const std::string &n, const Sprite &bkg) : Fase(n, bkg)
{
}

FaseLevel3::~FaseLevel3()
{
    delete hero;
    delete vidasTxt;
    delete nivel;
    delete gameOver;
    delete congrats;

    for(int i = 0; i<15; ++i)
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

void FaseLevel3::capturarTecla()
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

void FaseLevel3::pausar(int milissegundos) 
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milissegundos));
}

void FaseLevel3::init()
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

    alien[5] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo2.img"), 14, 314), 2));
    objs.push_back(alien[5]);

    alien[6] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo2.img"), 14, 275), 2));
    objs.push_back(alien[6]);

    alien[7] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo2.img"), 14, 236), 2));
    objs.push_back(alien[7]);

    alien[8] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo2.img"), 14, 197), 2));
    objs.push_back(alien[8]);

    alien[9] = new Alien(Nave(ObjetoDeJogo("Alien2", Sprite("rsc/inimigo2.img"), 14, 158), 2));
    objs.push_back(alien[9]);

    alien[10] = new Alien(Nave(ObjetoDeJogo("Alien3", Sprite("rsc/inimigo3.img"), 28, 314), 3));
    objs.push_back(alien[10]);

    alien[11] = new Alien(Nave(ObjetoDeJogo("Alien3", Sprite("rsc/inimigo3.img"), 28, 275), 3));
    objs.push_back(alien[11]);

    alien[12] = new Alien(Nave(ObjetoDeJogo("Alien3", Sprite("rsc/inimigo3.img"), 28, 236), 3));
    objs.push_back(alien[12]);

    alien[13] = new Alien(Nave(ObjetoDeJogo("Alien3", Sprite("rsc/inimigo3.img"), 28, 197), 3));
    objs.push_back(alien[13]);

    alien[14] = new Alien(Nave(ObjetoDeJogo("Alien3", Sprite("rsc/inimigo3.img"), 28, 158), 3));
    objs.push_back(alien[14]);

    vidasTxt = new ObjetoDeJogo("Vidas", Sprite("rsc/vidaExtraTxt.img"), 5, 360);
    objs.push_back(vidasTxt);

    vidas[0] = new ObjetoDeJogo("Vidas", Sprite("rsc/hero.img"), 12, 360);
    objs.push_back(vidas[0]);

    vidas[1] = new ObjetoDeJogo("Vidas", Sprite("rsc/hero.img"), 12, 390);
    objs.push_back(vidas[1]);

    vidas[2] = new ObjetoDeJogo("Vidas", Sprite("rsc/hero.img"), 27, 360);
    objs.push_back(vidas[2]);

    nivel = new ObjetoDeJogo("Nivel", Sprite("rsc/nivel3.img"), 70, 380);
    objs.push_back(nivel);

    gameOver = new ObjetoDeJogo("GameOver", Sprite("rsc/gameOver.img"), 45, 150);
    gameOver->desativarObj();
    objs.push_back(gameOver);

    congrats = new ObjetoDeJogo("cong", Sprite("rsc/congrats.img"), 50, 120);
    congrats->desativarObj();
    objs.push_back(congrats);

    for (int j = 0; j < 15; ++j)
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

unsigned FaseLevel3::run(SpriteBuffer &screen)
{
    this->draw(screen);
    system("cls");
    this->show(screen);

    this->flag.store(true);

    std::thread tecladoFase3(capturarTecla, this);

    short cont = 0;

    while(this->flag.load())
    {
        if (cont == 15)
        {
            congrats->ativarObj();
            screen.clear();
            this->draw(screen);
            this->show(screen);
            this->flag.store(false);
            tecladoFase3.join();
            return Fase::END_GAME;
        }
        
        for (int i = 0; i<15; ++i)
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
                for (int j = 2; j >= 0; --j)
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
                    tecladoFase3.join();
                    return Fase::GAME_OVER;
                }
            }

            // Implementação responsável por mover alien
            alien[i]->update();
            
            // Implementação responsável por mover os projeteis
            if (bulletAlien[i]->getActive())
            {
                if (bulletAlien[i]->getPosL() >= 105)
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
            case 4:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[0], *bulletAlien[i]))
                        break;
                }
                break;
            case 8:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[1], *bulletAlien[i]))
                        break;
                }
                break;
            case 12:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[2], *bulletAlien[i]))
                        break;
                }
                break;
            case 16:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[3], *bulletAlien[i]))
                        break;
                }
                break;
            case 20:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[4], *bulletAlien[i]))
                        break;
                }
                break;
            case 24:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[5], *bulletAlien[i]))
                        break;
                }
                break;
            case 28:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[6], *bulletAlien[i]))
                        break;
                }
                break;
            case 32:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[7], *bulletAlien[i]))
                        break;
                }
                break;
            case 36:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[8], *bulletAlien[i]))
                        break;
                }
                break;
            case 40:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[9], *bulletAlien[i]))
                        break;
                }
                break;
            case 44:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[10], *bulletAlien[i]))
                        break;
                }
                break;
            case 48:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[11], *bulletAlien[i]))
                        break;
                }
                break;
            case 52:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[12], *bulletAlien[i]))
                        break;
                }
                break;
            case 56:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[13], *bulletAlien[i]))
                        break;
                }
                break;
            case 60:
                for (int i = 0; i < 15; ++i)
                {
                    if (HandleBullet::checkAlien(*alien[14], *bulletAlien[i]))
                        break;
                }
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