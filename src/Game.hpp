#ifndef GAME_HPP
#define GAME_HPP

#include "Menu.hpp"
#include "FaseLevel1.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"

class Game
{
public:
    Game(){}
    ~Game(){}

    static void run()
    {
        SpriteBuffer buffer(350, 80);

        Menu menu("Menu", Sprite("rsc/background.img"));
        FaseLevel1 fase1("Fase1", Sprite("rsc/background.img"));

        menu.init();
        int val = menu.run(buffer);
        buffer.clear();
        if (val == Fase::LEVEL_1)
        {
            fase1.init();
            int ret1 = fase1.run(buffer);
            if ( ret1 != Fase::GAME_OVER && ret1 != Fase::END_GAME)
            {
                std::cout << "????";
            }
            else
                std::cout << "GAME OVER" << std::endl;
        } else {
            std::cout << "Fim de jogo" << std::endl;
        }


        buffer.clear();

    }

};

#endif