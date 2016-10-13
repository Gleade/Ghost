#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GameWindow.hpp"

class Game
{
public:
	Game(unsigned int width = 800, unsigned int height = 600, unsigned int bitsPerPixel = 32, std::string title = "GhostEngine", unsigned int frameRate = 0);
	~Game();

	void run();


private:
	std::shared_ptr<GameWindow> m_window;
	static const sf::Time TimePerFrame;

	void processEvents();
	void update(sf::Time dt);
	void render();
};

