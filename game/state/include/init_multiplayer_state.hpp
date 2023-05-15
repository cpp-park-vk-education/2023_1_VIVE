#pragma once

#include "state.hpp"
#include "button.hpp"

class InitMultiplayerState : public State {
public:
    InitMultiplayerState();

    void update(const sf::Event &event) override;
    void readMessage(const proto::Message& msg);
    void sendServerAboutInit();

private:
    void initObjects_();

    sf::Font fnt_;
    std::shared_ptr<sf::Text> template_;
    std::shared_ptr<sf::Text> code_;
    std::shared_ptr<sf::Text> copy_;

    std::string template_string_ = "Unique code for connection: ";
    std::string code_string_ = "Please wait...";
    std::string copy_string_ = "Press the button or type Ctrl+C";

    ButtonShPtr return_;
    ButtonShPtr copy_btn;

    bool is_waiting_ = true;
};
