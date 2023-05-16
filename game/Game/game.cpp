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

    updateCamera();

    updatePUI();

    // if (player_->getPosition().x > 400)
    // {
    //     coin_particles_->generate();
    // }

    // updateParticles(delta_time);
    updateTiles();
    updateEnemies(delta_time);

    updateNonExistentObjects();
    
    updateCollision();
}

void GameEngine::updateNonExistentObjects()
{
    // Check player

    // Check enemies
    for (auto it = enemies_.begin(); it != enemies_.end(); )
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

void GameEngine::drawBG() {
    window_.draw(bg_);
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

void GameEngine::drawEnemies()
{
    for (const auto &enemy : enemies_)
    {
        enemy->draw(window_, sf::RenderStates());
    }
}

void GameEngine::draw()
{
    window_.clear();

    drawBG();

    // Render game
    drawTiles();
    drawEnemies();
    // drawParticles();
    drawPlayer();

    player_user_interface_->draw(window_, sf::RenderStates());

    window_.display();
}

void GameEngine::spawnEnemies()
{
    int enemy_pos_x = random_int(0, window_.getSize().x);
    Enemy *enemy = new Enemy(sf::Vector2f(BASE_SIZE, BASE_SIZE * 2),
                                sf::Vector2f(enemy_pos_x, 100.f));
    
    enemies_.push_back(enemy);
}

void GameEngine::initBG() {
    bg_.setTexture(AssetManager::getInstance()->getTexture("green_world_temple"));
    bg_.setScale(2.0f, 2.0f);
}

void GameEngine::initAssets() {
    AssetManager::getInstance()->loadAssets("level_1");
}

void GameEngine::initWindow() {
    window_.create(sf::VideoMode(BASE_SIZE * 32, BASE_SIZE * 18), "Atomic God");
    int window_pos_x = sf::VideoMode::getDesktopMode().width / 2 - window_.getSize().x / 2;
    int window_pos_y = sf::VideoMode::getDesktopMode().height / 2 - window_.getSize().y / 2;
    window_.setPosition(sf::Vector2i(window_pos_x, window_pos_y));
    window_.setFramerateLimit(60);
}

void GameEngine::initCamera() {
    sf::Vector2u window_size = window_.getSize();
    sf::Vector2f camera_size = sf::Vector2f(window_size.x, window_size.y);
    sf::FloatRect camera_restriction_ = bg_.getGlobalBounds();

    camera_ = new CameraTarget(camera_size, camera_restriction_);
    camera_->setFollowByCoordinates(player_->getCenter().x, player_->getCenter().y);
}

void GameEngine::initPUI() {
    player_user_interface_ = new PUI(camera_->getCameraSize(), camera_->getTopLeftCameraCoordinates());
    player_user_interface_->updateMaxStatusBar(false, player_->getHPMax());
    player_user_interface_->updateBar(false, player_->getHP());
    player_user_interface_->updateMoney(player_->getCoinsCount());
    player_user_interface_->updateExpirienceCurrentPoints(player_->getExp());
}

void GameEngine::initPlayer()
{
    player_ = new Player(sf::Vector2f(BASE_SIZE, BASE_SIZE * 2),
                         sf::Vector2f(100.f, 100.f));
}

void GameEngine::initTiles()
{
    size_t tiles_count = 10;
    float x = 0;
    float y = 400;
    sf::Vector2f tile_size(BASE_SIZE, BASE_SIZE);

    for (size_t i{}; i <= window_.getSize().x; i += BASE_SIZE)
    {
        x = i;
        sf::Vector2f tile_coords(x, y);
        tiles_.push_back(new Tile(tile_size, tile_coords));
    }
}

void GameEngine::initParticles()
{
    coin_particles_ = new ParticleSet(10, sf::Vector2f(10, 10),
                                      sf::Vector2f(400.f, 200.f), COIN);
}

void GameEngine::initEnemies()
{
    spawnEnemies();
}

void GameEngine::updatePlayer(const float delta_time)
{
    // std::cout << "Update Player" << std::endl;

    if (!player_->isDead())
    {
        player_->update(event_, delta_time);
        player_->updateAttack(event_, enemies_.front(), delta_time);
    }
    else
    {
        int player_new_pos_x = random_int(0, window_.getSize().x);
        player_->setPosition(sf::Vector2f(player_new_pos_x, 100.f));
        player_->spawn();
    }
}

void GameEngine::updateCamera() {
    window_.setView(camera_->getView());
    camera_->setFollowByCoordinates(player_->getCenter().x, player_->getCenter().y);
}

void GameEngine::updatePUI() {
    player_user_interface_->updateCoordinates(camera_->getCameraSize(), camera_->getTopLeftCameraCoordinates());
    player_user_interface_->updateBar(false, player_->getHP());
    player_user_interface_->updateMoney(player_->getCoinsCount());
    player_user_interface_->updateExpirienceCurrentPoints(player_->getExp());
}

void GameEngine::updateTiles()
{
    // std::cout << "Update Tiles" << std::endl;

    for (const auto &tile : tiles_)
    {
        tile->update(event_, 0);
    }
}

void GameEngine::updateParticles(const float delta_time)
{
    // std::cout << "Update Particles" << std::endl;

    coin_particles_->update(event_, delta_time);
}

void GameEngine::updateCollision()
{
    std::vector<Player *> players;
    players.push_back(player_);

    collision_handler_->run(players, tiles_, enemies_);

    players.clear();
}

void GameEngine::updateEnemies(const float delta_time)
{
    // std::cout << "Update Enemies" << std::endl;
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
        enemy->update(event_, delta_time, player_);
        // enemy->updateAttack(event_, player_, delta_time);
    }
}

GameEngine::GameEngine()
{
    initWindow();
    initAssets();
    initBG();
    initPlayer();
    initCamera();
    initPUI();
    initTiles();
    // initParticles();
    initEnemies();

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
