#pragma once

#include "game_state.hpp"
#include "level_manager.hpp"

class SingleState : public GameState
{
public:
    SingleState();
    ~SingleState();

    void readMessage(const proto::Response &msg) override;
    void update(const sf::Event &event) override;
    void load() override;
    void unload() override;

    // Heap methods
    void updateHeap() override;
    ObjectsHeap &getHeap() override;
    void setHeap(std::vector<ObjectShPtr> objects) override{};

private:
    LevelManager *level_manager_;
};
