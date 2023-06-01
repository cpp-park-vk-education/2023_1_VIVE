#include "single_state.hpp"

#include "game.hpp"

SingleState::SingleState()
{
    std::cout << "Creating Single" << std::endl;
    level_manager = new LevelManager;
}

SingleState::~SingleState()
{

}

void SingleState::readMessage(const proto::Response &msg)
{

}

void SingleState::update(const sf::Event &event)
{
    level_manager->update(event);
    updateHeap();
}

void SingleState::load()
{
    std::cout << "Loading LevelManager" << std::endl;
    level_manager->load();
    std::cout << "LevelManager loaded" << std::endl;
}

void SingleState::updateHeap()
{
    std::cout << "heap size before update single state: " << heap_.size() << std::endl;
    for (auto& object : level_manager->getObjects())
    {
        heap_.push(object);
    }
    std::cout << "heap size after update single state: " << heap_.size() << std::endl;
}
