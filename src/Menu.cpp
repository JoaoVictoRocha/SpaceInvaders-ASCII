#include "Menu.hpp"

Menu::Menu(const std::string &n, const Sprite &bkg) : Fase(n, bkg)
{
    escolha = 0;
}

Menu::~Menu()
{
}

void Menu::capturarTecla()
{
    while (this->flag.load())
    {
        //char tecla = _getch();
        pausar(200);
        if (GetAsyncKeyState(VK_UP) & 0x8000) 
        {
            if (escolha == 0)
            {
                escolha = 1;
                seta->moveTo(33, 180);
            } else {
                escolha = 0;
                seta->moveTo(26, 180);
            }
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            if (escolha == 0)
            {
                escolha = 1;
                seta->moveTo(33, 180);
            } else {
                escolha = 0;
                seta->moveTo(26, 180);
            }
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            this->flag.store(false); // Sinaliza para a main que o programa deve encerrar
            break;
        }

        if (GetAsyncKeyState(VK_RETURN) & 0x8000) 
        {
            this->flag.store(false);
            break;
        }
        
    }
}

void Menu::pausar(int millissegundos)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millissegundos));
}

void Menu::init()
{
    this->menu = new ObjetoDeJogo("Menu", Sprite("rsc/menu.img"), 20, 170);
    objs.push_back(menu);

    this->seta = new ObjetoDeJogo("Seta", Sprite("rsc/setaEscolha.img"), 26, 180);
    objs.push_back(seta);

    this->start = new ObjetoDeJogo("Start", Sprite("rsc/start.img"), 27, 140);
    objs.push_back(start);

    this->exit = new ObjetoDeJogo("Exit", Sprite("rsc/exit.img"), 34, 140);
    objs.push_back(exit);

}

unsigned Menu::run(SpriteBuffer &screen)
{
    this->draw(screen);
    system("cls");
    this->show(screen);

    this->flag.store(true);

    std::thread menu(capturarTecla, this);

    while (this->flag.load())
    {
        screen.clear();
        this->update();
        this->draw(screen);
        this->show(screen);

        pausar(200);
        system("cls");
    }
    menu.join();

    return (escolha == 0) ? Fase::LEVEL_1 : Fase::END_GAME;
}