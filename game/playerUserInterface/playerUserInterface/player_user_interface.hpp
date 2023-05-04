#pragma once

#include "SFML/Graphics.hpp"
#include "i_navigation_icons.hpp"
#include "i_status_bar.hpp"
#include "i_status.hpp"

class StatusPlayerBar : public IStatusBar {
public:
    bool changePositionSprites(sf::Window& window) override;
    sf::Sprite getSprite() override;
    bool setStatus(int status) override;
private:
    bool is_mana_bar_;
};

class StatusWeapon : public IStatus {

};
