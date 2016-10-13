#include <memory>

#include "Game.hpp"

int main()
{
	std::unique_ptr<Game> game;
	game.reset(new Game());
	game->run();

	return 0;
}