#include "Game.hpp"

#include <iostream>

void Game::initWindow() {
    window.create(sf::VideoMode(800, 600), "Atomic God");
    window.setFramerateLimit(60);
}

void Game::initPlayer() {
    player = new Player(sf::Vector2(50.f, 100.f), sf::Vector2(0.f, 0.f));
}

Game::Game() : menu(&window) {
    initWindow();
    initPlayer();
    menu.open();
}

Game::~Game() {
}

void Game::updatePlayer(const float delta_time) {
    player->update(delta_time, window);
}

void Game::renderPlayer() {
    player->render(window);
}

// void Game::updateCollision()
// {
//     // Collision bottom of the screen
//     if (player->getPosition().y + player->getGlobalBounds().height >
//         window.getSize().y)
//     {
//         player->resetVelocityY();
//         player->setPosition(
//             player->getPosition().x,
//             window.getSize().y - player->getGlobalBounds().height);
//     }
// }

void Game::update() {
    // Polling window events
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        menu.update(event);
    }
    delta_time = clock.restart().asSeconds();

    updatePlayer(delta_time);
    // updateCollision();
}

void Game::render() {
    window.clear(sf::Color::Green);
    if (menu.isOpen()) {
        menu.render();
    } else  {
        // Render Game
        renderPlayer();
    }
    window.display();
}
