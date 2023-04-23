#include "Game.hpp"

void Game::initWindow()
{
    window.create(sf::VideoMode(800, 600), "Atomic God");
    window.setFramerateLimit(60);
}

Game::Game()
{
    initWindow();
}

Game::~Game()
{
}

void Game::update()
{
    // Polling window events
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed &&
                 event.key.code == sf::Keyboard::Escape)
            window.close();
    }
}

void Game::render()
{
    window.clear();

    // Render game
    window.display();
}
