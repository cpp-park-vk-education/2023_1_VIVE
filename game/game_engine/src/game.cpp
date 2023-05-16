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
    game_engine_ = this;
}

void GameEngine::run() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    window_.setPosition(sf::Vector2i(w_width_ / 4, w_height_ / 4));

    while (window_.isOpen()) {
        update();
        render();
    }

    google::protobuf::ShutdownProtobufLibrary();
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
    for (const auto& obj : state_manager_.getHeap()) {
        window_.draw(*obj);
    }
//    game_render_.render(state_manager_.getHeap());
    window_.display();

}
