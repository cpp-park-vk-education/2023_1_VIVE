#include "Game.hpp"

void Game::initWindow()
{
    window.create(sf::VideoMode(800, 600), "Atomic God");
    window.setFramerateLimit(60);
}

void Game::initPlayer()
{
    player = new Player(sf::Vector2(50.f, 100.f), sf::Vector2(0.f, 0.f));
}

Game::Game()
{
    initWindow();
    initPlayer();
}

Game::~Game()
{
}

void Game::updatePlayer()
{
    player->update();
}

void Game::renderPlayer()
{
    player->render(window);
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

    updatePlayer();
}

void Game::render()
{
    window.clear();

    // Render game
    renderPlayer();
    window.display();
}
