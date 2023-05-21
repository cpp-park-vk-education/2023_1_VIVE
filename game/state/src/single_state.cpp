#include "single_state.hpp"

#include "game.hpp"

SingleState::SingleState()
{
}

SingleState::~SingleState()
{
    delete player_;
    delete player_user_interface_;
    delete camera_;

    for (auto &tile : tiles_)
    {
        delete tile;
    }

    for (auto &enemy : enemies_)
    {
        delete enemy;
    }

    delete collision_handler_;
}

void SingleState::readMessage(const proto::Response &msg)
{
}

void SingleState::update(const sf::Event &event)
{
    float delta_time = clock_.restart().asSeconds();

    updatePlayer(event, delta_time);

    updateCamera();

    updatePUI();

    updateTiles(event);
    updateEnemies(event, delta_time);

    updateNonExistentObjects();

    updateCollision();
}

void SingleState::load()
{
    std::cout << "Started initions" << std::endl;
    initPlayer();
    std::cout << "Inited players" << std::endl;
    initTiles();
    std::cout << "Inited tiles" << std::endl;
    initEnemies();
    std::cout << "Inited enemies" << std::endl;
    initBG();
    std::cout << "Inited bg" << std::endl;
    initAssets();
    std::cout << "Inited assets" << std::endl;
    initCamera();
    std::cout << "Inited camer" << std::endl;
    initPUI();
    std::cout << "Inited pui" << std::endl;
    initCollisionHandler();
    std::cout << "Inited collision handler" << std::endl;

    clock_.restart();

    std::cout << "Finished initions" << std::endl;
}

void SingleState::initBG()
{
    bg_.setTexture(AssetManager::getInstance()->getTexture("green_world_temple"));
    bg_.setScale(2.0f, 2.0f);
}

void SingleState::initAssets()
{
    AssetManager::getInstance()->loadAssets("level_1");
}

void SingleState::initCamera()
{
    sf::Vector2u window_size = GameEngine::getWindow().getSize();
    sf::Vector2f camera_size = sf::Vector2f(window_size.x, window_size.y);
    sf::FloatRect camera_restriction_ = bg_.getGlobalBounds();
}

void SingleState::initPUI()
{
    player_user_interface_ = new PUI(
        sf::Vector2f(GameEngine::getWindow().getSize().x,
                     GameEngine::getWindow().getSize().y));
    player_user_interface_->updateMaxStatusBar(false, player_->getHPMax());
    player_user_interface_->updateBar(false, player_->getHP());
    player_user_interface_->updateMoney(player_->getCoinsCount());
    player_user_interface_->updateExpirienceCurrentPoints(player_->getExp());
}

void SingleState::initPlayer()
{
    player_ = new Player(sf::Vector2f(BASE_SIZE, BASE_SIZE * 2),
                         sf::Vector2f(100.f, 100.f));
}

void SingleState::initTiles()
{
    std::cout << "Started initing tiles" << std::endl;
    size_t tiles_count = 10;
    std::cout << "1" << std::endl;
    float x = 0;
    std::cout << "2" << std::endl;
    float y = 400;
    std::cout << "3" << std::endl;
    sf::Vector2f tile_size(BASE_SIZE, BASE_SIZE);
    std::cout << "4" << std::endl;

    std::cout << GameEngine::getInstance()->getWindow().getSize().x << std::endl;

    std::cout << "5" << std::endl;

    int cntr = 0;
    for (size_t i{}; i <= GameEngine::getWindow().getSize().x; i += BASE_SIZE)
    {
        // std::cout << "4" << std::endl;
        x = i;
        sf::Vector2f tile_coords(x, y);
        tiles_.push_back(new Tile(tile_size, tile_coords));
        std::cout << "Tile #" << cntr << "created" << std::endl;
    }
}

void SingleState::initEnemies()
{
    spawnEnemies();
}

void SingleState::initCollisionHandler()
{
    collision_handler_ = new CollisionHandler();
}

void SingleState::updatePlayer(const sf::Event &event, const float delta_time)
{
    player_->update(event, delta_time);
    player_->updateAttack(event, enemies_.front(), delta_time);
}

void SingleState::updateCamera()
{
    GameEngine::getWindow().setView(camera_->getView());
    camera_->setFollowByCoordinates(player_->getCenter().x, player_->getCenter().y);
}

void SingleState::updatePUI()
{
    player_user_interface_->updateBar(false, player_->getHP());
    player_user_interface_->updateExpirienceLevel(player_->getCurrLvl(), player_->getExpMax());
    player_user_interface_->updateMoney(player_->getCoinsCount());
    player_user_interface_->updateExpirienceCurrentPoints(player_->getExp());
}

void SingleState::updateTiles(const sf::Event &event)
{
    for (const auto &tile : tiles_)
    {
        tile->update(event, 0);
    }
}

void SingleState::updateCollision()
{
    std::vector<Player *> players;
    players.push_back(player_);

    collision_handler_->run(players, tiles_, enemies_);

    players.clear();
}

void SingleState::updateEnemies(const sf::Event &event, const float delta_time)
{
    if (enemies_.empty())
    {
        spawnEnemies();
    }

    for (const auto &enemy : enemies_)
    {
        // if (enemy->isDead)
        // {
        //     delete enemy
        // }
        enemy->update(event, delta_time, player_);
        // enemy->updateAttack(event_, player_, delta_time);
    }
}

void SingleState::updateNonExistentObjects()
{
    // Check player

    // Check enemies
    for (auto it = enemies_.begin(); it != enemies_.end();)
    {
        if (!(*it)->doesExist())
        {
            it = enemies_.erase(it);
        }
        else
        {
            ++it;
        }
    }
    // if (enemies_.empty())
    // {
    //     std::cout << "Enemy disappeared" << std::endl;
    // }
}

void SingleState::drawBG()
{
    GameEngine::getWindow().draw(bg_);
}

void SingleState::drawPlayer()
{
    player_->draw(GameEngine::getWindow(), sf::RenderStates());
}

void SingleState::drawTiles()
{
    for (const auto &tile : tiles_)
    {
        tile->draw(GameEngine::getWindow(), sf::RenderStates());
    }
}

void SingleState::drawEnemies()
{
    for (const auto &enemy : enemies_)
    {
        enemy->draw(GameEngine::getWindow(), sf::RenderStates());
    }
}

void SingleState::spawnEnemies()
{
    int enemy_pos_x = random_int(0, GameEngine::getWindow().getSize().x);
    Enemy *enemy = new Enemy(sf::Vector2f(BASE_SIZE, BASE_SIZE * 2),
                             sf::Vector2f(enemy_pos_x, 100.f));

    enemies_.push_back(enemy);
}
