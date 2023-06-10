#include "single_state.hpp"

#include "game.hpp"

SingleState::SingleState()
{
    std::cout << "Creating Single" << std::endl;
}

SingleState::~SingleState()
{

}

void SingleState::readMessage(const proto::Response &msg)
{

}

void SingleState::update(const sf::Event &event)
{
    LevelManager::getInstance()->update(event);
    updateHeap();
}

void SingleState::load()
{
    std::cout << "Loading LevelManager" << std::endl;
    LevelManager::getInstance()->load();
    std::cout << "LevelManager loaded" << std::endl;
}

void SingleState::updateHeap()
{
    // std::cout << "heap size before update single state: " << heap_.size() << std::endl;
    for (auto& object : LevelManager::getInstance()->getObjects())
    {
        heap_.push(object);
    }
    // std::cout << "heap size after update single state: " << heap_.size() << std::endl;
}
