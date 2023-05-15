#include "player_user_interface.hpp"

PUI::PUI(const sf::Vector2u& camera_size) {
    weapon_status_ = std::make_unique<StatusWeapon>(camera_size);
    status_expirience_ = std::make_unique<StatusExpirience>(camera_size);
    money_status_ = std::make_unique<StatusMoney>(camera_size);
    navigation_icons_ = std::make_unique<NavigationIcons>(camera_size);
    health_bar_ = std::make_unique<StatusPlayerBar>(false, camera_size);
    mana_bar_ = std::make_unique<StatusPlayerBar>(true, camera_size);
}

void PUI::initSprite() {

}

void PUI::update(const sf::Event& event) {

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

//Function updates one of the bar
void PUI::updateBar(bool is_mana_bar, uint8_t status) {
    if (is_mana_bar)
        mana_bar_->setStatus(status);
    else
        health_bar_->setStatus(status);
}

PUI::~PUI() {
}
