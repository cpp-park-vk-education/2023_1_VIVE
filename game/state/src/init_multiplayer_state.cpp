#include "init_multiplayer_state.hpp"

#include "game.hpp"

#include <iostream>


InitMultiplayerState::InitMultiplayerState() {

}

void InitMultiplayerState::load() {
    fnt_ = AssetManager::getInstance()->getFont("eight_bits");
    initObjects_();
}

void InitMultiplayerState::initObjects_() {
    return_ = std::make_shared<Button>();
    return_->setParams("Return", 60, 5, 15, sf::Color::Red);
    return_->setPosition(20, 20);
    return_->setHoverColor(sf::Color::Yellow);
    return_->setActiveColor(sf::Color(222, 238, 0));

    template_ = std::make_shared<Text>(template_string_);
    template_->setString(template_string_);
    template_->setCharacterSize(60);
    template_->setPosition(300, 100);
    template_->setFillColor(sf::Color::Red);

    code_ = std::make_shared<Text>(code_string_);
    code_->setString(code_string_);
    code_->setCharacterSize(100);
    code_->setPosition(400, 200);
    code_->setFillColor(sf::Color::Red);

    copy_btn = std::make_shared<Button>();
    copy_btn->setParams("Copy", 60, 5, 15, sf::Color::Red);
    copy_btn->setPosition(400, 400);
    copy_btn->setHoverColor(sf::Color::Yellow);
    copy_btn->setActiveColor(sf::Color(222, 238, 0));

    copy_ = std::make_shared<Text>(copy_string_);
    copy_->setString(copy_string_);
    copy_->setCharacterSize(60);
    copy_->setPosition(300, 500);
    copy_->setFillColor(sf::Color::Red);

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

    return_->update(event, 0);
    copy_btn->update(event, 0);

    heap_.push(template_);
    heap_.push(code_);
    heap_.push(return_);
    if (!is_waiting_) {
        heap_.push(copy_btn);
        heap_.push(copy_);
    }
}

void InitMultiplayerState::readMessage(const proto::Response &msg) {
    if (msg.has_init_multiplayer_state()) {
        code_string_ = msg.init_multiplayer_state().code();
        code_->setString(code_string_);
        is_waiting_ = false;
    }
    if (msg.has_join_state()) {
        GameEngine::getStateManager()->changeState(StateManager::SINGLE_STATE);

//        // пишем другому игроку о запуске игры
//        proto::Request ans;
//        proto::Request::InitMultiplayerState init_state;
//        init_state.set_is_start_game(true);
//        *ans.mutable_init_multiplayer_state() = init_state;
//        GameEngine::writeMessage(ans);
    }
}

void InitMultiplayerState::updateHeap() {

}



