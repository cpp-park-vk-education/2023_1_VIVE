#pragma once

#include "asset_manager.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class NavigationIcons {
public:
    NavigationIcons(const sf::Vector2f& camera_size);

    NavigationIcons() = delete;
    NavigationIcons(const NavigationIcons&) = delete;
    NavigationIcons(NavigationIcons&&) = delete;
    NavigationIcons& operator=(const NavigationIcons&) = delete;
    NavigationIcons& operator=(NavigationIcons&&) = delete;

    ~NavigationIcons() {
    }

    void setObjectPosition(const sf::Vector2f& camera_size);
    sf::Sprite getMenuIcon() const;
    sf::Sprite getInventoryIcon() const;
    sf::Sprite getLevelPointsIcon() const;

private:
    sf::Sprite menu_icon_;
    sf::Sprite inventory_icon_;
    sf::Sprite level_points_icon_;
};
