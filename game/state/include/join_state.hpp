#pragma once

#include "state.hpp"
#include "button.hpp"

class JoinState : public State {
public:
    JoinState();

    void update(const sf::Event &event) override;
    void readMessage(const proto::Response &msg);

private:
    void sendCodeToServer_(const std::string &code);

private:
    sf::Font fnt_;
    ButtonShPtr return_;

    std::shared_ptr<sf::Text> template_;

    std::string template_string_ = "Type the code and press 'Enter'";

    ButtonShPtr input_field_;

};
