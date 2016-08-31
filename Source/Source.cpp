#include "Game.hpp"


#include <iostream>

int main()
{
	try 
	{
		Game game;
		game.run();
	}
	catch (std::exception &e)
	{
		std::cout << "Exception error : " << e.what() << "\n";
	}
}