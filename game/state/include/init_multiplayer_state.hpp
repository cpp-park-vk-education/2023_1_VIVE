#pragma once

#include "state.hpp"
#include "button.hpp"
#include "text.hpp"

class InitMultiplayerState : public State {
public:
    InitMultiplayerState();

    void update(const sf::Event &event) override;
    void readMessage(const proto::Response &msg);

    void load() override;
    void unload() override {};

    void updateHeap() override;

private:
    void initObjects_();

    sf::Font fnt_;



    TextShPtr template_;
    TextShPtr code_;
    TextShPtr copy_;

    std::string template_string_ = "Unique code for connection: ";
    std::string code_string_ = "Please wait...";
    std::string copy_string_ = "Press the button or type Ctrl+C";

    ButtonShPtr return_;
    ButtonShPtr copy_btn;

    bool is_waiting_ = true;
};
