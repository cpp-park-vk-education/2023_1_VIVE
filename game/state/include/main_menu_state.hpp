#pragma once

#include "state.hpp"
#include "button.hpp"
#include "state_manager.hpp"
#include "asset_manager.hpp"
#include "sound.hpp"

class StateManager;

class MainMenuState : public State
{
    enum EnButton
    {
        START,
        START_MULTIPLAYER,
        JOIN,
    };

public:
    MainMenuState();

    void update(const sf::Event &event) override;
    void readMessage(const proto::Response &msg) override;
    void load() override;
    void unload() override {}

    // Heap methods
    void updateHeap() override {};

private:
    void sendServerAboutInitMultiplayer_();
    void handlePressedButton(const ButtonShPtr &btn, StateManager *manager, const sf::Event &event);

private:
    std::vector<ButtonShPtr> buttons_;
    std::vector<std::string> names_{
        "Start",
        "Start a multiplayer game",
        "Join",
    };
    std::vector<EnButton> en_buttons_{
        START,
        START_MULTIPLAYER,
        JOIN,
    };
    std::unordered_map<std::string, EnButton> name_to_en_btn_;
};
