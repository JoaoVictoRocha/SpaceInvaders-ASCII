#ifndef GAME_HPP
#define GAME_HPP

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

        FaseLevel1 fase1("Fase1", Sprite("rsc/background.img"));

        fase1.init();
        int ret1 = fase1.run(buffer);
		if ( ret1 != Fase::GAME_OVER && ret1 != Fase::END_GAME){
		
			buffer.clear();
		}
		else
			std::cout << "GAME OVER" << std::endl;


        buffer.clear();

    }

};

#endif