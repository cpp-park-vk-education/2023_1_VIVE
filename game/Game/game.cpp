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

    if (player_->getPosition().x > 400)
    {
        coin_particles_->generate();
    }

    updateParticles(delta_time);

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

void GameEngine::drawParticles()
{
    coin_particles_->draw(window_, sf::RenderStates());
}

void GameEngine::draw()
{
    window_.clear();

    // Render game
    drawPlayer();
    drawTiles();
    drawParticles();
    window_.display();
}

void GameEngine::initWindow()
{
    window_.create(sf::VideoMode(800, 600), "Atomic God");
    window_.setFramerateLimit(60);
}

void GameEngine::initPlayer()
{
    player_ = new Player(sf::Vector2f(BASE_SIZE, BASE_SIZE * 2),
                         sf::Vector2f(300.f, 100.f));
}

void GameEngine::initTiles()
{
    size_t tiles_count = 10;
    float x = 250;
    float y = 400;
    sf::Vector2f tile_size(BASE_SIZE, BASE_SIZE);

    for (size_t i{}; i < tiles_count; ++i)
    {
        x += 25;
        sf::Vector2f tile_coords(x, y);
        tiles_.push_back(new Tile(tile_size, tile_coords));
    }

    for (int i{}; i < tiles_count; ++i)
    {
        if (i % 2)
        {
            x += 25;
        }
        else
        {
            y -= 25;
        }

        sf::Vector2f tile_coords(x, y);
        tiles_.push_back(new Tile(tile_size, tile_coords));
    }
}

void GameEngine::initParticles()
{
    coin_particles_ = new ParticleSet(10, sf::Vector2f(10, 10),
                                      sf::Vector2f(400.f, 200.f), COIN);
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

void GameEngine::updateParticles(const float delta_time)
{
    coin_particles_->update(event_, delta_time);
}

void GameEngine::updateCollision()
{
    std::vector<Player *> players;
    players.push_back(player_);
    
    collision_handler_->run(players, tiles_, coin_particles_);

    players.clear();
}

GameEngine::GameEngine()
{
    initWindow();
    initPlayer();
    initTiles();
    initParticles();

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
