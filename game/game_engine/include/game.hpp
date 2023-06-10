#pragma once

#include "player.hpp"
#include "client.hpp"
#include "state_manager.hpp"
#include "object.hpp"

class GameRender {

};

class GameEngine
{
public:
    GameEngine();
    GameEngine(const GameEngine& other) = delete;
    GameEngine& operator=(const GameEngine& other) = delete;

    ~GameEngine();

    void run();

    static GameEngine* getInstance();
    static sf::RenderWindow& getWindow();
    static StateManager* getStateManager();
    static Client* getClient();
    static void readMessage(const proto::Response& msg);
    static void writeMessage(const proto::Request& msg);

private:
    void update();
    void render();

private:
    static GameEngine* game_engine_;

    sf::Sprite bg_main_;

    unsigned int w_width_ = sf::VideoMode::getDesktopMode().width;
    unsigned int w_height_ = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window_;
    Client client_;  // при инициализации игры создается, но не подключается к серверу
    StateManager state_manager_;
    // GameRender game_render_;

    // ISound sound_;

    // Entities
    // Player *player;
/*
private:
    // Objects
    sf::Event event_;
    sf::Sprite bg_;
    Player *player_;
    PUI* player_user_interface_;
    CameraTarget* camera_;
    std::vector<Tile *> tiles_;
    ParticleSet *coin_particles_;
    std::vector<Enemy *> enemies_;

    CollisionHandler *collision_handler_;

    void updateGame();

    // Inits
    void initBG();
    void initAssets();
    void initCamera();
    void initPUI();
    void initPlayer();
    void initTiles();
    void initParticles();
    void initEnemies();

    // Updates
    void updatePlayer(const float delta_time);
    void updateCamera();
    void updatePUI();
    void updateTiles();
    void updateParticles(const float delta_time);
    void updateCollision();
    void updateEnemies(const float delta_time);
    void updateNonExistentObjects();

    // Draws
    void drawBG();
    void drawPlayer();
    void drawTiles();
    void drawParticles();
    void drawEnemies();

    // Spawners
    void spawnEnemies();

    // Timer
    sf::Clock clock_;

    char state_game_ = 'R';
*/
};
