#ifndef GAME_HPP
#define GAME_HPP

#include "Menu.hpp"
#include "FaseLevel1.hpp"
#include "FaseLevel2.hpp"
#include "FaseLevel3.hpp"
#include "ASCII_Engine/Sprite.hpp"
#include "ASCII_Engine/SpriteBuffer.hpp"

class Game
{
public:
    Game(){}
    ~Game(){}

    static void run()
    {
        SpriteBuffer buffer(420, 110);

        Menu menu("Menu", Sprite("rsc/background.img"));
        FaseLevel1 fase1("Fase1", Sprite("rsc/background.img"));
        FaseLevel2 fase2("Fase2", Sprite("rsc/background.img"));
        FaseLevel3 fase3("Fase3", Sprite("rsc/background.img"));

        menu.init();
        int level0 = menu.run(buffer);

        buffer.clear();

        if (level0 == Fase::LEVEL_1)
        {
            fase1.init();
            int level1 = fase1.run(buffer);
            if ( level1 == Fase::LEVEL_COMPLETE)
            {
                buffer.clear();
                fase2.init();
                int level2 = fase2.run(buffer);
                if (level2 == Fase::LEVEL_COMPLETE)
                {
                    buffer.clear();
                    fase3.init();
                    int level3 = fase3.run(buffer);
                }
            }
        }
        buffer.clear();
    }

};

#endif