#pragma once

#include "player.hpp"
#include "client.hpp"
#include "state_manager.hpp"
#include "object.hpp"

class ISound{

};
class IAssetManager {

};

class GameRender {

};

class GameEngine
{
public:
    GameEngine();

    void run();

    static GameEngine* getInstance();
    static sf::RenderWindow& getWindow();
    static StateManager* getStateManager();
    static Client* getClient();

private:
    void update();
    void render();

private:
    static GameEngine* game_engine_;

    unsigned int w_width_ = sf::VideoMode::getDesktopMode().width;
    unsigned int w_height_ = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window_;
    Client client_;  // при инициализации игры создается, но не подключается к серверу
    StateManager state_manager_;
    GameRender game_render_;

    ISound sound_;
    IAssetManager asset_manager_;


    // Entities
    Player *player;
};
