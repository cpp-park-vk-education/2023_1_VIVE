#include "join_state.hpp"
#include "game.hpp"

#include <iostream>

JoinState::JoinState() {
}

void JoinState::load() {
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

    input_field_ = std::make_shared<Button>();
    input_field_->setParams("", 60, 5, 15, sf::Color::Red);
    input_field_->setPosition(50, 300);
}

void JoinState::update(const sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        if (return_->isMouseOver(GameEngine::getWindow())) {
            GameEngine::getStateManager()->changeState(StateManager::MAIN_MENU_STATE);
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace) {
            std::string new_text = input_field_->getText();
            if (!new_text.empty()) {
                new_text.pop_back();
            }
            input_field_->setText(new_text);
        }
        if (event.key.code >= sf::Keyboard::Num0 &&
            event.key.code <= sf::Keyboard::Num9) {
            input_field_->setText(input_field_->getText() +
                                  std::to_string(event.key.code - sf::Keyboard::Num0));
        }
        if (event.key.control && event.key.code == sf::Keyboard::V) {
            input_field_->setText(input_field_->getText() + sf::Clipboard::getString().toAnsiString());
        }
        if (event.key.code == sf::Keyboard::Enter) {
            std::string code = input_field_->getText();
            sendCodeToServer_(code);
        }
    }

    return_->update(event, 0);

    updateHeap();
}

void JoinState::sendCodeToServer_(const std::string &code) {
    proto::Request msg;
    proto::Request::JoinState state;
    state.set_code(code);
    *msg.mutable_join_state() = state;
    GameEngine::writeMessage(msg);
}

void JoinState::readMessage(const proto::Response &msg) {
    if (msg.has_join_state()) {
        if (msg.join_state().ok()) {
            GameEngine::getStateManager()->changeState(StateManager::SINGLE_STATE);
        }
    }
}

void JoinState::updateHeap() {
    clearHeap();
    heap_.push(return_);
    heap_.push(template_);
    heap_.push(input_field_);
}
