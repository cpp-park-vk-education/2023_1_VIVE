#pragma once

#include <SFML/Graphics.hpp>

class StatusMoney {
public:
    StatusMoney(const sf::Vector2u& camera_size);

    StatusMoney() = delete;
    StatusMoney(const StatusMoney&) = delete;
    StatusMoney(StatusMoney&&) = delete;
    StatusMoney& operator=(const StatusMoney&) = delete;
    StatusMoney& operator=(StatusMoney&&) = delete;

    ~StatusMoney() {
    }

    void setObjectPosition(const sf::Vector2u& camera_size);
    void setStatus(uint16_t status);
    sf::Text getText() const;
    sf::Sprite getSprite() const;

private:
    uint16_t current_status_;
    sf::Text text_;
    sf::Sprite icon_sprite_;
};
