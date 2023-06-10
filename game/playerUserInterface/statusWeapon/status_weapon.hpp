#pragma once

#include "asset_manager.hpp"
#include <SFML/Graphics.hpp>

class StatusWeapon {
public:
    StatusWeapon(const sf::Vector2f& camera_size, const std::string& weapon_name = "sword");

    StatusWeapon() = delete;
    StatusWeapon(const StatusWeapon&) = delete;
    StatusWeapon(StatusWeapon&&) = delete;
    StatusWeapon& operator=(const StatusWeapon&) = delete;
    StatusWeapon& operator=(StatusWeapon&&) = delete;

    ~StatusWeapon() {
    }

    void setObjectsPosition(const sf::Vector2f& camera_size);
    void setNewWeapon(const std::string& weapon_name, const sf::Vector2f& camera_size);
    sf::Sprite getSprite() const;
    sf::CircleShape getCircle() const;

private:
    sf::Sprite icon_sprite_;
    sf::CircleShape zone_;
};
