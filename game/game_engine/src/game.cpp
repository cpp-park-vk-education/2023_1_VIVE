#include "game.hpp"

#include "object.hpp"
#include "message.pb.h"

#include <iostream>

GameEngine *GameEngine::game_engine_;

GameEngine *GameEngine::getInstance()
{
    return game_engine_;
}

sf::RenderWindow &GameEngine::getWindow()
{
    GameEngine *game = getInstance();
    return game->window_;
}

StateManager *GameEngine::getStateManager()
{
    GameEngine *game = getInstance();
    return &game->state_manager_;
}

Client *GameEngine::getClient()
{
    GameEngine *game = getInstance();
    return &game->client_;
}

GameEngine::GameEngine() : window_(sf::VideoMode(w_width_ / 2, w_height_ / 2), "ATOMIC GOD")
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    game_engine_ = this;
    int window_pos_x = sf::VideoMode::getDesktopMode().width / 2 - window_.getSize().x / 2;
    int window_pos_y = sf::VideoMode::getDesktopMode().height / 2 - window_.getSize().y / 2;
    window_.setPosition(sf::Vector2i(window_pos_x, window_pos_y));
    window_.setFramerateLimit(60);
    std::cout << "GameEngine constructor end" << std::endl;
}

void GameEngine::run()
{
    window_.setPosition(sf::Vector2i(w_width_ / 4, w_height_ / 4));

    state_manager_.init();

    sf::Texture& txtr = AssetManager::getInstance()->getTexture("pixel_mountain");
    bg_main_.setTexture(txtr);
    bg_main_.setScale(float(window_.getSize().x) / txtr.getSize().x, float(window_.getSize().y) / txtr.getSize().y);

    while (window_.isOpen())
    {
        update();
        render();
    }
}

void GameEngine::update()
{
    sf::Event event{};
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_.close();
            break;
        }
        // TODO change updating current state
        if (state_manager_.getState() != StateManager::EnState::SINGLE_STATE)
        {
            state_manager_.update(event);
        }
    }
    if (state_manager_.getState() == StateManager::EnState::SINGLE_STATE)
    {
        state_manager_.update(event);
    }
}

void GameEngine::render()
{
    if (state_manager_.getState() == StateManager::EnState::MAIN_MENU_STATE) {
        window_.draw(bg_main_);
    }

    ObjectsHeap heap = state_manager_.getHeap();
    while (!heap.empty())
    {
        ObjectShPtr obj = heap.top();
        if (obj->getPriority() == Priority::PLAYER_USER_INTERFACE)
        {
            window_.setView(window_.getDefaultView());
        }
        window_.draw(*obj);
        heap.pop();
    }
    window_.display();
}

GameEngine::~GameEngine()
{
    google::protobuf::ShutdownProtobufLibrary();
}

void GameEngine::readMessage(const proto::Response &msg)
{
    getStateManager()->readMessage(msg);
}

void GameEngine::writeMessage(const proto::Request &msg)
{
    getClient()->writeMessage(msg);
}
