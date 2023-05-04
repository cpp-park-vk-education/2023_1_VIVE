#pragma once

#include "Player.hpp"
#include "Menu.hpp"
#include "client.hpp"
#include "read_from_server_signal.hpp"

class GameEngine
{
private:
    void update();
    void render();

public:
    void run();

private:
    sf::RenderWindow window_;
    Client client_;
    ReadFromServerSignal read_signal_;


    ISound* sound_;
    IAssetManager asset_manager_;


    // Entities
    Player *player;
};
