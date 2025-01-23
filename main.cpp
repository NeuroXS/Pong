#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	loadFont();
	Game::get_instance().start();
}