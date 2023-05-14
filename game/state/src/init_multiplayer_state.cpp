#include "init_multiplayer_state.hpp"

#include "game.hpp"

#include <iostream>


InitMultiplayerState::InitMultiplayerState() {
    if (!fnt_.loadFromFile("fonts/EightBits.ttf")) {
        std::cout << "error" << std::endl;
    }

    return_ = std::make_shared<Button>();
    return_->setParams("Return", 60, "fonts/EightBits.ttf", 5, 15, sf::Color::Red);
    return_->setPosition(20, 20);
    return_->setHoverColor(sf::Color::Yellow);
    return_->setActiveColor(sf::Color(222, 238, 0));

    template_ = std::make_shared<sf::Text>();
    template_->setString(template_string_);
    template_->setCharacterSize(60);
    template_->setPosition(300, 100);
    template_->setFillColor(sf::Color::Red);
    template_->setFont(fnt_);

    code_ = std::make_shared<sf::Text>();
    code_->setString(code_string_);
    code_->setCharacterSize(100);
    code_->setPosition(400, 200);
    code_->setFillColor(sf::Color::Red);
    code_->setFont(fnt_);

    copy_btn = std::make_shared<Button>();
    copy_btn->setParams("Copy", 60, "fonts/EightBits.ttf", 5, 15, sf::Color::Red);
    copy_btn->setPosition(400, 400);
    copy_btn->setHoverColor(sf::Color::Yellow);
    copy_btn->setActiveColor(sf::Color(222, 238, 0));

    copy_ = std::make_shared<sf::Text>();
    copy_->setString(copy_string_);
    copy_->setCharacterSize(60);
    copy_->setPosition(300, 500);
    copy_->setFillColor(sf::Color::Red);
    copy_->setFont(fnt_);

}

void InitMultiplayerState::update(const sf::Event &event) {
    auto &window = GameEngine::getWindow();
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (return_->isMouseOver(window)) {
            GameEngine::getStateManager()->changeState(StateManager::MAIN_MENU_STATE);
        }
        if (!is_waiting_) {
            if (copy_btn->isMouseOver(window)) {
                sf::Clipboard::setString(code_string_);
            }
        }
    }
    if (!is_waiting_) {
        if (event.type == sf::Event::KeyPressed &&
            event.key.control && event.key.code == sf::Keyboard::C) {
            sf::Clipboard::setString(code_string_);
            std::cout << "ctrl+c" << std::endl;
        }
    }

    return_->update(event);
    copy_btn->update(event);

    objects_.clear();
    objects_.push_back(template_);
    objects_.push_back(code_);
    objects_.push_back(return_);
    if (!is_waiting_) {
        objects_.push_back(copy_btn);
        objects_.push_back(copy_);
    }
}

void InitMultiplayerState::readMessage(const Message &msg) {
    // ...
    is_waiting_ = false;
}
