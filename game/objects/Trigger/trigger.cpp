#include "trigger.hpp"

#include "level_manager.hpp"

void Trigger::initSprite()
{
    sprite_.setTexture(AssetManager::getInstance()->getTexture("ground_portal"));
    sprite_.setScale(0.20f, 0.20f);
    sprite_.setPosition(hitbox_.getPosition().x - 80.0f, hitbox_.getPosition().y - 50.0f);
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
    target.draw(sprite_);
}

void Trigger::changeTrigger()
{
    trigger = !trigger;
}
