#include "sub_level.hpp"

#include "game.hpp"

SubLevel::SubLevel(const sf::Vector2u size,
                   std::vector<PlayerShPtr> players,
                   std::vector<TileShPtr> tiles,
                   std::vector<EnemyShPtr> enemies,
                   BossShPtr boss)
    : map_size_(size),
      players_(players),
      tiles_(tiles),
      enemies_(enemies),
      boss_(boss)
{
    std::cout << "Creating SubLevel" << std::endl;
    players_count_ = players_.size();
    enemies_count_ = enemies_.size();
    init();
    clock_.restart();
    std::cout << "SubLevel Created" << std::endl;
}

std::vector<ObjectShPtr> SubLevel::getObjects()
{
    std::vector<ObjectShPtr> res{};
    for (auto &player : players_)
    {
        res.push_back(player);
    }
    for (auto &tile : tiles_)
    {
        res.push_back(tile);
    }
    for (auto &enemy : enemies_)
    {
        res.push_back(enemy);
    }
    res.push_back(player_user_interface_);
    res.push_back(background_);
    if (boss_)
    {
        res.push_back(boss_);
    }
    return res;
}

void SubLevel::update(const sf::Event &event)
{
    float delta_time = clock_.restart().asSeconds();

    SoundManager::getInstance()->playMusic();
    updateBackGround();
    updatePlayer(event, delta_time);
    updateCamera();
    updatePUI();
    updateTiles(event);
    updateEnemies(event, delta_time);
    updateBoss(event, delta_time);
    updateNonExistentObjects();
    updateCollision();
    // updateHeap();
    updateOutOfBounds();
}

void SubLevel::setMapSize(const sf::Vector2u size)
{
    map_size_ = size;
}

sf::Vector2u SubLevel::getMapSize() const
{
    return map_size_;
}

void SubLevel::init()
{
    background_ = std::make_shared<BackGround>(GameEngine::getWindow().getSize(), true);
    initCamera();
    initPUI();
    initCollisionHandler();
}

void SubLevel::initCamera()
{
    sf::Vector2u window_size = GameEngine::getWindow().getSize();
    sf::Vector2f camera_size = sf::Vector2f(window_size.x, window_size.y);
    sf::FloatRect camera_restriction_ = sf::FloatRect(0, 0, getMapSize().x, getMapSize().y);

    camera_ = new CameraTarget(camera_size, camera_restriction_);
    PlayerShPtr player = players_.front();
    camera_->setFollowByCoordinates(player->getCenter().x, player->getCenter().y);
}

void SubLevel::initPUI()
{
    player_user_interface_ = std::make_shared<PUI>(
        sf::Vector2f(GameEngine::getWindow().getSize().x,
                     GameEngine::getWindow().getSize().y));

    PlayerShPtr player = players_.front();

    player_user_interface_->updateMaxStatusBar(false, player->getHPMax());
    player_user_interface_->updateBar(false, player->getHP());
    player_user_interface_->updateMoney(player->getCoinsCount());
    player_user_interface_->updateExpirienceCurrentPoints(player->getExp());
}

void SubLevel::initCollisionHandler()
{
    collision_handler_ = std::make_shared<CollisionHandler>();
}

void SubLevel::spawnEnemies()
{
    for (int i = 0; i < enemies_count_; ++i)
    {
        int enemy_pos_x = random_int(0, GameEngine::getWindow().getSize().x);
        EnemyShPtr enemy = std::make_shared<Enemy>(sf::Vector2f(BASE_SIZE * 2.5f, BASE_SIZE * 3), sf::Vector2f(enemy_pos_x, 100.f));
        enemies_.push_back(enemy);
    }
}

void SubLevel::spawnPlayer(PlayerShPtr player)
{
    int player_new_pos_x = random_int(0, GameEngine::getWindow().getSize().x);
    player->setPosition(sf::Vector2f(player_new_pos_x, 100.f));
    player->spawn();
    player->setStayAnimation();
}

void SubLevel::updateBackGround()
{
    background_->move(camera_->getTopLeftCameraCoordinates());
}

void SubLevel::updatePlayer(const sf::Event &event, const float delta_time)
{
    for (auto &player : players_)
    {
        if (!player->isDead())
        {
            player->update(event, delta_time);

            // attacks
            for (auto &enemy : enemies_)
            {
                player->updateAttack(event, enemy, delta_time);
            }
            if (boss_)
            {
                player->updateAttack(event, boss_, delta_time);
            }

            if (!player->isAttack() && !player->isJumping() && !player->isRunning())
                player->setStayAnimation();
        }
        else
        {
            if (player->checkDeathFreeze(delta_time))
            {
                spawnPlayer(player);
            }
        }
        player->updateAnimation(delta_time);
    }
}

void SubLevel::updateCamera()
{
    PlayerShPtr player = players_.front();
    GameEngine::getWindow().setView(camera_->getView());
    camera_->setFollowByCoordinates(player->getCenter().x, player->getCenter().y);
}

void SubLevel::updatePUI()
{
    PlayerShPtr player = players_.front();
    player_user_interface_->updateBar(false, player->getHP());
    player_user_interface_->updateExpirienceLevel(player->getCurrLvl(), player->getExpMax());
    player_user_interface_->updateMoney(player->getCoinsCount());
    player_user_interface_->updateExpirienceCurrentPoints(player->getExp());
}

void SubLevel::updateTiles(const sf::Event &event)
{
    for (const auto &tile : tiles_)
    {
        tile->update(event, 0);
    }
}

void SubLevel::updateCollision()
{
    if (boss_)
    {
        collision_handler_->run(players_, tiles_, enemies_, boss_);
    }
    else
    {
        collision_handler_->run(players_, tiles_, enemies_);
    }
}

void SubLevel::updateEnemies(const sf::Event &event, const float delta_time)
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
        enemy->update(event, delta_time, players_.front());
        // enemy->updateAttack(event_, player_, delta_time);
    }
}

void SubLevel::updateBoss(const sf::Event &event, const float delta_time)
{
    if (boss_)
    {
        boss_->update(event, delta_time, players_.front());
    }
}

void SubLevel::updateNonExistentObjects()
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

void SubLevel::updateOutOfBounds()
{
    // check players
    for (auto &player : players_)
    {
        if (player->getPosition().y > getMapSize().y)
        {
            std::cout << "Out" << std::endl;
            spawnPlayer(player);
        }
    }
}
