#pragma once

#include "asset_manager.hpp"
#include <SFML/Graphics.hpp>

class StatusExpirience {
public:
    StatusExpirience(const sf::Vector2f& camera_size);

    StatusExpirience() = delete;
    StatusExpirience(const StatusExpirience&) = delete;
    StatusExpirience(StatusExpirience&&) = delete;
    StatusExpirience& operator=(const StatusExpirience&) = delete;
    StatusExpirience& operator=(StatusExpirience&&) = delete;

    ~StatusExpirience() {
    }

    void setObjectPosition(const sf::Vector2f& camera_size);
    void setTotalLever(uint8_t total_level);
    void setCurrentPoints(uint16_t current_points);
    void setMaxPoints(uint16_t max_points);
    sf::Text getText() const;
    sf::Sprite getSprite() const;

private:
    void updateTextInfo();

    uint8_t total_level_;
    uint16_t current_points_;
    uint16_t max_points_;
    sf::Text text_;
    sf::Sprite icon_sprite_;
};
