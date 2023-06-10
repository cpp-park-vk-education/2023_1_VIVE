#include "navigation_icons.hpp"

#include "navigation_icons.hpp"

NavigationIcons::NavigationIcons(const sf::Vector2f& camera_size) {
    menu_icon_.setTexture(AssetManager::getInstance()->getTexture("menu_icon"));
    inventory_icon_.setTexture(AssetManager::getInstance()->getTexture("inventory_icon"));
    level_points_icon_.setTexture(AssetManager::getInstance()->getTexture("level_points_icon"));

    setObjectPosition(camera_size);
}

//This setting allows you to adjust to the size of the window and display sprite correctly
void NavigationIcons::setObjectPosition(const sf::Vector2f& camera_size) {
    menu_icon_.setScale(static_cast<float>(camera_size.x) / 1920.0f, static_cast<float>(camera_size.y) / 1080.0f);
    inventory_icon_.setScale(static_cast<float>(camera_size.x) / 1920.0f, static_cast<float>(camera_size.y) / 1080.0f);
    level_points_icon_.setScale(static_cast<float>(camera_size.x) / 1920.0f, static_cast<float>(camera_size.y) / 1080.0f);

    menu_icon_.setPosition(static_cast<float>(camera_size.x) / 2.0f, 
            static_cast<float>(camera_size.y) - menu_icon_.getGlobalBounds().height - static_cast<float>(camera_size.y) * 1.0f / 100.0f );
    inventory_icon_.setPosition(static_cast<float>(camera_size.x) / 2.0f - static_cast<float>(camera_size.x) * 7.5f / 100.0f,
                                static_cast<float>(camera_size.y) - menu_icon_.getGlobalBounds().height - static_cast<float>(camera_size.y) * 1.0f / 100.0f );
    level_points_icon_.setPosition(static_cast<float>(camera_size.x) / 2.0f + static_cast<float>(camera_size.x) * 7.5f / 100.0f,
            static_cast<float>(camera_size.y) - menu_icon_.getGlobalBounds().height - static_cast<float>(camera_size.y) * 1.0f / 100.0f );
}

sf::Sprite NavigationIcons::getMenuIcon() const {
    return menu_icon_;
}

sf::Sprite NavigationIcons::getInventoryIcon() const {
    return inventory_icon_;
}

sf::Sprite NavigationIcons::getLevelPointsIcon() const {
    return level_points_icon_;
}
