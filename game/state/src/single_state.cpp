#include "single_state.hpp"

#include "game.hpp"

SingleState::SingleState()
{
    std::cout << "Creating Single" << std::endl;
    level_manager_ = new LevelManager;
}

SingleState::~SingleState()
{
}

void SingleState::readMessage(const proto::Response &msg)
{
}

void SingleState::update(const sf::Event &event)
{
    level_manager_->update(event);
    updateHeap();
}

void SingleState::load()
{
    std::cout << "Loading LevelManager" << std::endl;
    LEVEL level = LEVEL::L1;
    SUBLEVEL sublevel = SUBLEVEL::SBL1;
    level_manager_->changeTo(level, sublevel);
    std::cout << "LevelManager loaded" << std::endl;
}

void SingleState::unload()
{
    delete level_manager_;
}

void SingleState::updateHeap()
{
    clearHeap();
    for (auto &object : level_manager_->getObjects())
    {
        heap_.push(object);
    }
}

ObjectsHeap &SingleState::getHeap()
{
    return heap_;
}
