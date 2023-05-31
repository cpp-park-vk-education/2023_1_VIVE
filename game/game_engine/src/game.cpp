#include "game.hpp"

#include "object.hpp"
#include "message.pb.h"

#include <iostream>

GameEngine* GameEngine::game_engine_;

GameEngine *GameEngine::getInstance() {
    return game_engine_;
}

sf::RenderWindow& GameEngine::getWindow() {
    GameEngine* game = getInstance();
    return game->window_;
}

StateManager *GameEngine::getStateManager() {
    GameEngine* game = getInstance();
    return &game->state_manager_;
}

Client *GameEngine::getClient() {
    GameEngine* game = getInstance();
    return &game->client_;
}

GameEngine::GameEngine():
window_(sf::VideoMode(w_width_ / 2, w_height_ / 2), "ATOMIC GOD") {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    game_engine_ = this;
}

void GameEngine::run() {
    window_.setPosition(sf::Vector2i(w_width_ / 4, w_height_ / 4));

    state_manager_.init();
    while (window_.isOpen()) {
        update();
        render();
    }
}

void GameEngine::update() {
    sf::Event event{};
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
            break;
        }
        state_manager_.update(event);
    }
}

void GameEngine::render() {
    window_.clear(sf::Color::Green);
    ObjectsHeap heap = state_manager_.getHeap();
    while (!heap.empty())
    {
        ObjectShPtr obj = heap.top();
        if (obj->getPriority() == PRIORITY::PLAYER_USER_INTERFACE)
        {
            window_.setView(window_.getDefaultView());
        }
        window_.draw(*obj);
        heap.pop();
    }

    window_.display();
}

GameEngine::~GameEngine() {
    google::protobuf::ShutdownProtobufLibrary();
}

void GameEngine::readMessage(const proto::Response &msg) {
    getStateManager()->readMessage(msg);
}

void GameEngine::writeMessage(const proto::Request &msg) {
    getClient()->writeMessage(msg);
}


