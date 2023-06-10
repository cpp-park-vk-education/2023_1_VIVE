#include "sub_level.hpp"

#include "game.hpp"

SubLevel::SubLevel(const sf::Vector2u size,
                   std::vector<PlayerShPtr> players,
                   std::vector<TileShPtr> tiles,
                   std::vector<EnemyShPtr> enemies,
                   std::vector<TriggerShPtr> triggers,
                   BossShPtr boss)
    : map_size_(size),
      players_(players),
      tiles_(tiles),
      enemies_(enemies),
      triggers_(triggers),
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
        if (checkObjectInCamera(tile))
        {
            res.push_back(tile);
        }
    }
    for (auto &enemy : enemies_)
    {
        if (checkObjectInCamera(enemy))
        {
            res.push_back(enemy);
        }
    }
    for (auto &trigger : triggers_)
    {
        if (checkObjectInCamera(trigger))
        {
            res.push_back(trigger);
        }
    }
    for (auto &item : drop_)
    {
        if (item->doesExist() && checkObjectInCamera(item))
        {
            res.push_back(item);
        }
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
    // updateTiles(event);
    updateEnemies(event, delta_time);
    updateTriggers(event);
    updateBoss(event, delta_time);
    updateDrop(event, delta_time);
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

std::vector<PlayerShPtr> &SubLevel::getPlayers()
{
    return players_;
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

    camera_ = std::make_shared<CameraTarget>(camera_size, camera_restriction_);
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
    player->spawn();
    player->setStayAnimation();
}

bool SubLevel::checkObjectInCamera(const PhysicalObjectShPtr object)
{
    float camera_left_bound = camera_->getCameraCenter().x -
                              camera_->getCameraSize().x / 2;

    float camera_right_bound = camera_->getCameraCenter().x +
                               camera_->getCameraSize().x / 2;

    float camera_upper_bound = camera_->getCameraCenter().y -
                               camera_->getCameraSize().y / 2;

    float camera_lower_bound = camera_->getCameraCenter().y +
                               camera_->getCameraSize().y / 2;

    float object_left_bound = object->getCenter().x -
                              object->getGlobalBounds().width / 2;

    float object_right_bound = object->getCenter().x +
                               object->getGlobalBounds().width / 2;

    float object_upper_bound = object->getCenter().y -
                               object->getGlobalBounds().height / 2;

    float object_lower_bound = object->getCenter().y +
                               object->getGlobalBounds().height / 2;

    if (object_right_bound < camera_left_bound ||
        object_left_bound > camera_right_bound ||
        object_lower_bound < camera_upper_bound ||
        object_upper_bound > camera_lower_bound)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// bool SubLevel::checkEnemyInCamera(const EnemyShPtr enemy)
// {
//     if (!enemy->isDead())
//     {
//         return checkObjectInCamera(enemy);
//     }
//     else
//     {
        
//     }
// }

void SubLevel::updateBackGround()
{
    AnimStates cur_state = players_[0]->getCurrentState();
    switch (cur_state)
    {
    case AnimStates::STAY_ANIM:
        background_->move(camera_->getTopLeftCameraCoordinates(), 's');
        break;
    default:
        if (players_[0]->isLeftRun())
            background_->move(camera_->getTopLeftCameraCoordinates(), 'l');
        else
            background_->move(camera_->getTopLeftCameraCoordinates(), 'r');
        break;
    }
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
                if (checkObjectInCamera(enemy))
                {
                    player->updateAttack(event, enemy, delta_time);
                }
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
                background_->restart();
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
    std::vector<TileShPtr> tiles{};
    for (auto &tile : tiles_)
    {
        if (checkObjectInCamera(tile))
        {
            tiles.push_back(tile);
        }
    }

    std::vector<EnemyShPtr> enemies{};
    for (auto &enemy : enemies_)
    {
        if (checkObjectInCamera(enemy))
        {
            enemies.push_back(enemy);
        }
    }

    std::vector<ParticleShPtr> particles{};
    for (auto &particle : drop_)
    {
        if (checkObjectInCamera(particle))
        {
            particles.push_back(particle);
        }
    }
    
    std::vector<TriggerShPtr> triggers{};
    for (auto &trigger : triggers_)
    {
        if (checkObjectInCamera(trigger))
        {
            triggers.push_back(trigger);
        }
    }

    if (boss_ && checkObjectInCamera(boss_))
    {
        collision_handler_->run(players_, tiles, particles, enemies, triggers, boss_);
    }
    else
    {
        collision_handler_->run(players_, tiles, particles, enemies, triggers);
    }
}

void SubLevel::updateEnemies(const sf::Event &event, const float delta_time)
{
    // if (enemies_.empty())
    // {
    //     spawnEnemies();
    // }

    for (auto &enemy : enemies_)
    {
        if (checkObjectInCamera(enemy))
        {
            enemy->update(event, delta_time, players_.front());
        }
    }
}

void SubLevel::updateTriggers(const sf::Event &event)
{
    for (auto &trigger : triggers_)
    {
        trigger->update(event, 0);
    }
}

void SubLevel::updateBoss(const sf::Event &event, const float delta_time)
{
    if (boss_)
    {
        // std::cout << boss_->getHP() << std::endl;
        boss_->update(event, delta_time, players_.front());
        if (boss_->isDead() && !boss_->didDrop())
        {
            boss_->drop();
            ParticleShPtr gem = std::make_shared<Particle>(
                sf::Vector2f(BASE_SIZE / 2, BASE_SIZE / 2),
                boss_->getCenter(),
                ParticleType::GEM
            );
            gem->create();
            drop_.push_back(gem);
        }
    }
}

void SubLevel::updateDrop(const sf::Event &event, const float delta_time)
{
    for (auto &item : drop_)
    {
        if (checkObjectInCamera(item))
        {
            item->update(event, delta_time);
        }
    }
}

void SubLevel::updateNonExistentObjects()
{
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
}

void SubLevel::updateOutOfBounds()
{
    // check players
    for (auto &player : players_)
    {
        if (player->getCenter().y > getMapSize().y)
        {
            player->updateDamageTaken(player->getHP());
        }
    }
}
