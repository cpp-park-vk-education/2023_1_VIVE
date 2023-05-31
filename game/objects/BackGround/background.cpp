#include "background.hpp"

BackGround::BackGround(const sf::Vector2u& window_size) : window_size_(window_size) {
    priority_ = Priority::BACKGROUND;

    maps_[GREEN_WORLD_TEMPLE] = "green_world_temple";

    sf::Texture texture = AssetManager::getInstance()->getTexture(maps_[GREEN_WORLD_TEMPLE]);
    sprite_.setTexture(AssetManager::getInstance()->getTexture(maps_[GREEN_WORLD_TEMPLE]));
    sprite_.setScale(static_cast<float>(window_size_.x) / texture.getSize().x, 
                        static_cast<float>(window_size_.y) / texture.getSize().y);
}

void BackGround::loadLevelMap(TextureMap level_map) {
    
}

void BackGround::move(sf::Vector2f goal_coor) {
    sprite_.setPosition(goal_coor);
}

BackGround::~BackGround() {
}
