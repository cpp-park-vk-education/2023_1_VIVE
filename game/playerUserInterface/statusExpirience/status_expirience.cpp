#include "status_expirience.hpp"

StatusExpirience::StatusExpirience(const sf::Vector2f& camera_size) {
    icon_sprite_.setTexture(AssetManager::getInstance()->getTexture("level"));

    total_level_ = 0;
    max_points_ = 0;
    current_points_ = 0;

    text_.setFont(AssetManager::getInstance()->getFont("eight_bits"));
    text_.setString("Level " + std::to_string(total_level_) + "\n" + std::to_string(current_points_) + "/" + std::to_string(max_points_));
    text_.setOutlineThickness(1);
    text_.setOutlineColor(sf::Color::Black);
    text_.setFillColor(sf::Color::Yellow);

    setObjectPosition(camera_size);
}

void StatusExpirience::setObjectPosition(const sf::Vector2f& camera_size) {
    icon_sprite_.setScale(static_cast<float>(camera_size.x) / 8500.0f, static_cast<float>(camera_size.y) / 5500.0f);
    icon_sprite_.setPosition(static_cast<float>(camera_size.x) * 0.5f / 100.0f,
                            static_cast<float>(camera_size.y) - icon_sprite_.getGlobalBounds().height);

    text_.setCharacterSize(static_cast<unsigned int>(camera_size.y / 1650.0f * 100));
    text_.setLineSpacing(0.75f);
    text_.setPosition(static_cast<float>(camera_size.x) * 8.0f / 100.0f,
                            static_cast<float>(camera_size.y) - static_cast<float>(camera_size.y) * 12.5f / 100.0f);
}

void StatusExpirience::updateTextInfo() {
    text_.setString("Level " + std::to_string(total_level_) + "\n" + std::to_string(current_points_) + "/" + std::to_string(max_points_));
}

void StatusExpirience::setTotalLever(uint8_t level) {
    total_level_ = level;
    current_points_ = 0;
    updateTextInfo();
}

void StatusExpirience::setMaxPoints(uint16_t max_points) {
    max_points_ = max_points;
    current_points_ = 0;
    updateTextInfo();
}

void StatusExpirience::setCurrentPoints(uint16_t current_points) {
    current_points_ = current_points;
    updateTextInfo();
}

sf::Text StatusExpirience::getText() const {
    return text_;
}

sf::Sprite StatusExpirience::getSprite() const {
    return icon_sprite_;
}
