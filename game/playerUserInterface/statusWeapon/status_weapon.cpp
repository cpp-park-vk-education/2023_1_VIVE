#include "status_weapon.hpp"

StatusWeapon::StatusWeapon(const sf::Vector2f& camera_size, const std::string& weapon_name) {
    zone_.setOutlineColor(sf::Color::Red);
    zone_.setOutlineThickness(2);
    zone_.setFillColor(sf::Color::Cyan);

    icon_sprite_.setTexture(AssetManager::getInstance()->getTexture(weapon_name));

    setObjectsPosition(camera_size);
}

void StatusWeapon::setObjectsPosition(const sf::Vector2f& camera_size) {
    zone_.setRadius(static_cast<float>(camera_size.x * camera_size.y) * 0.009f / 100.0f);
    zone_.setPosition(static_cast<float>(camera_size.x) * 0.25f / 100.0f,
                        static_cast<float>(camera_size.y) * 0.5f / 100.0f);
    
    icon_sprite_.setScale(static_cast<float>(camera_size.x) / 20500.0f,
                        static_cast<float>(camera_size.y) / 12000.0f);
    icon_sprite_.setPosition(zone_.getGlobalBounds().width / 30.0f, 
                            zone_.getGlobalBounds().height / 4.0f);
}

void StatusWeapon::setNewWeapon(const std::string& weapon_name, const sf::Vector2f& camera_size) {
    icon_sprite_.setTexture(AssetManager::getInstance()->getTexture(weapon_name));
    icon_sprite_.setScale(static_cast<float>(camera_size.x) / 19500.0f,
                        static_cast<float>(camera_size.y) / 10000.0f);

    setObjectsPosition(camera_size);
}

sf::Sprite StatusWeapon::getSprite() const {
    return icon_sprite_;
}

sf::CircleShape StatusWeapon::getCircle() const {
    return zone_;
}
