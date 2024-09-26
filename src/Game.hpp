#ifndef GAME_HPP
#define GAME_HPP

#include "Fase1.hpp"
#include "Fase2.hpp"
#include "Fase3.hpp"
#include "../ASCII_Engine/SpriteBuffer.hpp"

class Game
{
public:
	Game(){}
	~Game(){}
	
	static void run()
	{
		SpriteBuffer buffer(176,49);
	
		Fase1 fase1("Fase1",Sprite("./rsc/space.txt"));
		Fase2 fase2("Fase2",Sprite("./rsc/space.txt"));
		Fase3 fase3("Fase3",Sprite("./rsc/space.txt"));

		fase1.init();
		int ret1 = fase1.run(buffer);
		if ( ret1 == Fase::LEVEL_COMPLETE){
		
			buffer.clear();

			fase2.init();
			int ret2 = fase2.run(buffer);
			if ( ret2 == Fase::LEVEL_COMPLETE){
			
				buffer.clear();
				
				fase3.init();
				int ret3 = fase3.run(buffer);
				if ( ret3 == Fase::LEVEL_COMPLETE){
					std::cout << "YOU WIN" << std::endl;
				}
				else
					std::cout << "GAME OVER" << std::endl;
			}
			else
				std::cout << "GAME OVER" << std::endl;

		}
		else
			std::cout << "GAME OVER" << std::endl;
		
		std::cout << "Saindo..." << std::endl;
	}

};

#endif //GAME_HPP