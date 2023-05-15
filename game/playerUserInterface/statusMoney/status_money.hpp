#pragma once

#include "asset_manager.hpp"
#include <SFML/Graphics.hpp>

class StatusMoney {
public:
    StatusMoney(const sf::Vector2f& camera_size, const sf::Vector2f& camera_coordinates);

    StatusMoney() = delete;
    StatusMoney(const StatusMoney&) = delete;
    StatusMoney(StatusMoney&&) = delete;
    StatusMoney& operator=(const StatusMoney&) = delete;
    StatusMoney& operator=(StatusMoney&&) = delete;

    ~StatusMoney() {
    }

    void setObjectPosition(const sf::Vector2f& camera_size, const sf::Vector2f& camera_coordinates);
    void setStatus(uint16_t status);
    sf::Text getText() const;
    sf::Sprite getSprite() const;

private:
    uint16_t current_status_;
    sf::Text text_;
    sf::Sprite icon_sprite_;
};
