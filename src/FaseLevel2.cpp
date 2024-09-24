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