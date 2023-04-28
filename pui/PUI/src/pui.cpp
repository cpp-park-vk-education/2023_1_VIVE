#include "pui.hpp"

PUI::PUI(sf::RenderWindow& window) {
    health_bar_ = new StatusBar(assets[1], assets[0], window.getSize().x, window.getSize().y, false);
    mana_bar_ = new StatusBar(assets[2], assets[0], window.getSize().x, window.getSize().y, true);
}

//Function updated one of the bar
void PUI::updateBar(bool is_mana_bar, int status) {
    if (is_mana_bar)
        mana_bar_->setStatus(status);
    else
        health_bar_->setStatus(status);
}

void PUI::drawPUI(sf::RenderWindow& window) const {
    health_bar_->draw(window);
    mana_bar_->draw(window);
}

PUI::~PUI() {
    delete health_bar_;
    delete mana_bar_;
}
