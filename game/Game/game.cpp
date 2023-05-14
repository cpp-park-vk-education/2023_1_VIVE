#include "game.hpp"

void GameEngine::update()
{
    while (window_.pollEvent(event_))
    {
        if (event_.type == sf::Event::Closed)
            window_.close();
        else if (event_.type == sf::Event::KeyPressed &&
                 event_.key.code == sf::Keyboard::Escape)
            window_.close();
    }
    float delta_time = clock_.restart().asSeconds();

    updatePlayer(delta_time);
    
    updateTiles();

    updateCollision();
}

void GameEngine::drawPlayer()
{
    player_->draw(window_, sf::RenderStates());
}

void GameEngine::drawTiles()
{
    for (const auto &tile : tiles_)
    {
        tile->draw(window_, sf::RenderStates());
    }
}

void GameEngine::draw()
{
    window_.clear();

    // Render game
    drawPlayer();
    drawTiles();
    window_.display();
}

void GameEngine::initWindow()
{
    window_.create(sf::VideoMode(800, 600), "Atomic God");
    window_.setFramerateLimit(60);
}

void GameEngine::initPlayer()
{
    player_ = new Player(sf::Vector2(25.f, 50.f), sf::Vector2(300.f, 100.f));
}

void GameEngine::initTiles()
{
    size_t tiles_count = 10;
    float x = 250;
    float y = 400;
    sf::Vector2f tile_size(25.f, 25.f);
    
    for (size_t i{}; i < tiles_count; ++i)
    {
        sf::Vector2f tile_coords(x + i * 25, y);
        tiles_.push_back(new Tile(tile_size, tile_coords));
    }
}

void GameEngine::updatePlayer(const float delta_time)
{
    player_->update(event_, delta_time);
}

void GameEngine::updateTiles()
{
    for (const auto &tile : tiles_)
    {
        tile->update(event_, 0);
    }
}

void GameEngine::updateCollision()
{
    collision_handler_->checkPlayerTilesCollision(player_, tiles_);
}

GameEngine::GameEngine()
{
    initWindow();
    initPlayer();
    initTiles();

    collision_handler_ = new CollisionHandler();
}

GameEngine::~GameEngine()
{
}

void GameEngine::run()
{
    while (window_.isOpen())
    {
        update();

        draw();
    }
}
