#include <iostream>

#include "game.hpp"

#include "main_menu_state.hpp"

MainMenuState::MainMenuState() {
    for (int i = 0; i < names_.size(); ++i) {
        name_to_en_btn_.insert({names_[i], en_buttons_[i]});

        ButtonShPtr btn = std::make_shared<Button>();
        btn->setParams(names_[i], 60, "fonts/EightBits.ttf", 5, 15, sf::Color::Red);
        btn->setPosition(100, (i + 1) * 100);
        btn->setHoverColor(sf::Color::Yellow);
        btn->setActiveColor(sf::Color(222, 238, 0));
        buttons_.push_back(btn);
    }
}

void MainMenuState::update(const sf::Event &event) {
    objects_.clear();

    StateManager* manager = GameEngine::getStateManager();
    for (const auto &btn: buttons_) {
        btn->update(event);
        handlePressedButton(btn, manager, event);
        objects_.push_back(btn);
    }
}

void MainMenuState::handlePressedButton(const ButtonShPtr& btn, StateManager* manager, const sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        btn->isMouseOver(GameEngine::getWindow())) {

        EnButton en_btn = name_to_en_btn_[btn->getText()];
        if (en_btn == START) {
            manager->changeState(StateManager::SINGLE_STATE);
        }
        if (en_btn == START_MULTIPLAYER) {
            manager->changeState(StateManager::INIT_MULTIPLAYER_STATE);
            sendServerAboutInitMultiplayer_();
        }
        if (en_btn == JOIN) {
            manager->changeState(StateManager::JOIN_STATE);
        }
    }
}

void MainMenuState::readMessage(const proto::Response &msg) {

}

void MainMenuState::sendServerAboutInitMultiplayer_() {
    proto::Request msg;
    proto::Request::InitMultiplayerState state;
    msg.set_allocated_init_multiplayer_state(&state);
    std::cout << msg.has_init_multiplayer_state() << std::endl;
    GameEngine::getClient()->write(msg);
}
