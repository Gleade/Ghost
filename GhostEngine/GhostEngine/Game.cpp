#include "Game.hpp"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game(unsigned int width, unsigned int height, unsigned int bitsPerPixel , std::string title , unsigned int frameRate)
{
	m_window.reset(new GameWindow(width, height, bitsPerPixel, title, frameRate));

}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window->getWindow()->isOpen())
	{
		// Fixed time step calculations
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			// Update our game
			update(TimePerFrame);

			// Process game events
			processEvents();
		
		}

		render();
	}
}

void Game::update(sf::Time dt)
{
}

void Game::processEvents()
{
	sf::Event event;

	while (m_window->getWindow()->pollEvent(event))
	{
		if (event.Closed)
		{
			m_window->getWindow()->close();
		}
	}
}

void Game::render()
{
	m_window->getWindow()->clear();
	// Draw code here
	m_window->getWindow()->display();
}
