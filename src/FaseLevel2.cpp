#include "FaseLevel2.hpp"

FaseLevel2::FaseLevel2(const std::string &n, const Sprite &bkg) : Fase(n, bkg)
{
}

FaseLevel2::~FaseLevel2()
{
}

void FaseLevel2::capturarTecla()
{
    while (this->flag.load()) {

        char tecla = _getch();

        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && hero->getPosC() > 0)
            hero->moveLeft(2);

        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && hero->getPosC() <= 323)
            hero->moveRight(2);

        if (tecla == 32)
        {
            for (int i = 0; i<5; ++i)
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

void FaseLevel2::pausar(int milissegundos) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milissegundos));
}

void FaseLevel2::init()
{
    hero = new Hero(Nave(ObjetoDeJogo("Heroi", Sprite("rsc/hero.img"), 68, 177), 3));
    objs.push_back(hero);

    for (int i = 0; i<10; ++i)
    {
        alien[i] = new Alien(Nave(ObjetoDeJogo("Alien1", Sprite("rsc/inimigo1.img"), 0, 314), 1));
        objs.push_back(alien[i]);
    }

    for (int j = 0; j < 10; ++j)
    {   
        if (j < 4)
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

    std::thread tecladoFase1(capturarTecla, this);

    short cont = 0;

    while(this->flag.load())
    {
        if (cont == 10)
            return Fase::LEVEL_COMPLETE;
        
        for (int i = 0; i<10; ++i)
        {
            // eventos de colisão
            for (int t = 0; t<4; t++)
            {
                if (bulletHero[t]->getActive())
                {
                    if (alien[i]->colideComBordas(*bulletHero[t]))
                        alien[i]->sofrerAtaque(*bulletHero[t]);
                }
            }
        }
    }

    return Fase::GAME_OVER;
}