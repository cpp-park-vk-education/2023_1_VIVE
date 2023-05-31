#include "player_user_interface.hpp"

PUI::PUI(const sf::Vector2f& camera_size) {
    priority_ = Priority::PLAYER_USER_INTERFACE;
    weapon_status_ = std::make_unique<StatusWeapon>(camera_size);
    status_expirience_ = std::make_unique<StatusExpirience>(camera_size);
    money_status_ = std::make_unique<StatusMoney>(camera_size);
    navigation_icons_ = std::make_unique<NavigationIcons>(camera_size);
    health_bar_ = std::make_unique<StatusPlayerBar>(false, camera_size);
    mana_bar_ = std::make_unique<StatusPlayerBar>(true, camera_size);
}

PUI::~PUI() {

}

void PUI::initSprite() {

}

void PUI::update(const sf::Event& event, const float delta_time) {

}

void PUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mana_bar_->getBgBar());
    target.draw(mana_bar_->getBar());
    target.draw(mana_bar_->getSprite());
    target.draw(mana_bar_->getText());

    target.draw(health_bar_->getBgBar());
    target.draw(health_bar_->getBar());
    target.draw(health_bar_->getSprite());
    target.draw(health_bar_->getText());

    target.draw(navigation_icons_->getMenuIcon());
    target.draw(navigation_icons_->getInventoryIcon());
    target.draw(navigation_icons_->getLevelPointsIcon());

    target.draw(money_status_->getSprite());
    target.draw(money_status_->getText());

    target.draw(status_expirience_->getSprite());
    target.draw(status_expirience_->getText());

    target.draw(weapon_status_->getCircle());
    target.draw(weapon_status_->getSprite());
}

void PUI::updateCoordinates(const sf::Vector2f& camera_size) {
    weapon_status_->setObjectsPosition(camera_size);
    status_expirience_->setObjectPosition(camera_size);
    money_status_->setObjectPosition(camera_size);
    navigation_icons_->setObjectPosition(camera_size);
    health_bar_->setObjectsPositions(camera_size);
    mana_bar_->setObjectsPositions(camera_size);
}

//Functions update status
void PUI::updateBar(bool is_mana_bar, uint16_t status) {
    if (is_mana_bar)
        mana_bar_->setStatus(status);
    else
        health_bar_->setStatus(status);
}

void PUI::updateMaxStatusBar(bool is_mana_bar, uint16_t max_status) {
    if (is_mana_bar)
        mana_bar_->setMaxStatus(max_status);
    else
        health_bar_->setMaxStatus(max_status);
}

void PUI::updateWeapon(const std::string& name, const sf::Vector2f& camera_size) {
    weapon_status_->setNewWeapon(name, camera_size);
}

void PUI::updateMoney(uint16_t money) {
    money_status_->setStatus(money);
}

void PUI::updateExpirienceLevel(uint16_t total_level, uint16_t max_points) {
    status_expirience_->setTotalLever(total_level);
    status_expirience_->setMaxPoints(max_points);
}

void PUI::updateExpirienceCurrentPoints(uint16_t current_points) {
    status_expirience_->setCurrentPoints(current_points);
}
