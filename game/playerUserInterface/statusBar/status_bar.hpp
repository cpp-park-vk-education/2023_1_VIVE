#pragma once

#include <SFML/Graphics.hpp>
#include "asset_manager.hpp"
#include <iostream>

class StatusPlayerBar {
public:
    StatusPlayerBar(bool is_mana_bar, const sf::Vector2f& camera_size);

    StatusPlayerBar() = delete;
    StatusPlayerBar(const StatusPlayerBar&) = delete;
    StatusPlayerBar(StatusPlayerBar&&) = delete;
    StatusPlayerBar& operator=(const StatusPlayerBar&) = delete;
    StatusPlayerBar& operator=(StatusPlayerBar&&) = delete;

    ~StatusPlayerBar() {
    }

    void setObjectsPositions(const sf::Vector2f&);
    void setMaxStatus(uint16_t max_status);
    void setStatus(uint16_t status);
    sf::Sprite getSprite() const;
    sf::RectangleShape getBar() const;
    sf::RectangleShape getBgBar() const;
    sf::Text getText() const;

private:
    bool is_mana_bar_;
    sf::RectangleShape bar_;
    sf::RectangleShape bg_bar_;
    uint16_t max_status_;
    uint16_t current_status_;
    sf::Font font_;
    sf::Text procent_;
    sf::Sprite icon_sprite_;
};
