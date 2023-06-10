#include "status_money.hpp"

StatusMoney::StatusMoney(const sf::Vector2f& camera_size) {
    icon_sprite_.setTexture(AssetManager::getInstance()->getTexture("coin"));

    text_.setFont(AssetManager::getInstance()->getFont("eight_bits"));
    text_.setString("0$");
    text_.setOutlineThickness(1);
    text_.setOutlineColor(sf::Color::Black);
    text_.setFillColor(sf::Color::Yellow);

    setObjectPosition(camera_size);
}

void StatusMoney::setObjectPosition(const sf::Vector2f& camera_size) {
    icon_sprite_.setScale(static_cast<float>(camera_size.x) / 8500.0f, static_cast<float>(camera_size.y) / 5500.0f);
    icon_sprite_.setPosition(static_cast<float>(camera_size.x) - static_cast<float>(camera_size.x) * 15.0f / 100.0f,
                            static_cast<float>(camera_size.y) - icon_sprite_.getGlobalBounds().height);

    text_.setCharacterSize(static_cast<unsigned int>(camera_size.y / 1650.0f * 150));
    text_.setPosition(static_cast<float>(camera_size.x) - static_cast<float>(camera_size.x) * 8.0f / 100.0f,
                            static_cast<float>(camera_size.y) - text_.getGlobalBounds().height - static_cast<float>(camera_size.y) * 7.5f / 100.0f);
}

void StatusMoney::setStatus(uint16_t status) {
    current_status_ = status;

    text_.setString(std::to_string(current_status_) + "$");
}

sf::Sprite StatusMoney::getSprite() const {
    return icon_sprite_;
}

sf::Text StatusMoney::getText() const {
    return text_;
}
