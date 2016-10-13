#include "GameWindow.hpp"



GameWindow::GameWindow(unsigned int width, unsigned int height, unsigned int bitsPerPixel, std::string title, unsigned int frameRate)
{
	// Create the new render window
	m_window.reset(new sf::RenderWindow(sf::VideoMode(width, height, bitsPerPixel), title));

	// Set the frame rate, 0 = no frame rate cap
	if (frameRate != 0)
	{
		m_window->setFramerateLimit(frameRate);
	}
}


GameWindow::~GameWindow()
{
}

sf::RenderWindow *GameWindow::getWindow()
{
	return m_window.get();
}
