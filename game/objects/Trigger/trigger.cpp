#include "trigger.hpp"

#include "level_manager.hpp"

void Trigger::initSprite()
{
    shape_.setFillColor(sf::Color::Blue);
    shape_.setSize(hitbox_.getSize());
    shape_.setPosition(hitbox_.getPosition());
    // std::cout << shape_.getPosition().x << ", " << shape_.getPosition().y
    //           << "\t" << hitbox_.getPosition().x << ", "
    //           << hitbox_.getPosition().y << std::endl;
}

Trigger::Trigger(const sf::Vector2f size, const sf::Vector2f position)
    : PhysicalObject(size, position),
      trigger(false)
{
    priority_ = Priority::TRIGGERS;
    initSprite();
}

Trigger::~Trigger()
{
}

void Trigger::update(const sf::Event &event, const float delta_time)
{
    if (trigger)
    {
        std::cout << "Trigger" << std::endl;
        LevelManager::getInstance()->changeNext();
        trigger = false;
    }
}

void Trigger::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
    target.draw(shape_);
}

void Trigger::changeTrigger()
{
    trigger = !trigger;
}
