#pragma once

#include "state.hpp"
#include "button.hpp"
#include "text.hpp"

class JoinState : public State {
public:
    JoinState();

    void update(const sf::Event &event) override;
    void readMessage(const proto::Response &msg);

    void load() override;
    void unload() override {};

    void updateHeap() override;

private:
    void sendCodeToServer_(const std::string &code);

private:
    ButtonShPtr return_;

    TextShPtr template_;

    std::string template_string_ = "Type the code and press 'Enter'";

    ButtonShPtr input_field_;

};
