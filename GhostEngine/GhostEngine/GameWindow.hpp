#pragma once

#include <SFML\Graphics.hpp>

#include <memory>

class GameWindow
{
public:
	// Creates a Game Window
	GameWindow(unsigned int width = 800, unsigned int height = 600, unsigned int bitsPerPixel = 32, std::string title = "GhostEngine", unsigned int frameRate = 0);
	~GameWindow();

	// Returns a pointer to the render window
	sf::RenderWindow *getWindow();

private:
	std::shared_ptr<sf::RenderWindow> m_window;
};

