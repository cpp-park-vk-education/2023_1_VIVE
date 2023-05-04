#pragma once

#include "Player.hpp"
#include "client.hpp"
#include "state_manager.hpp"
#include "read_from_server_signal.hpp"

class ISound{

};
class IAssetManager {

};

class GameEngine
{
public:
    void run();

private:
    void update();
    void render();

private:
    sf::RenderWindow window_;
    Client client_;
    std::shared_ptr<ReadFromServerSignal> read_signal_;
    StateManager stateManager;

    ISound sound_;
    IAssetManager asset_manager_;


    // Entities
    Player *player;
};
