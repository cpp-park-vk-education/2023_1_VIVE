#include "status_bar.hpp"

//Constructor which define is it mana bar or not and set corresponing image
StatusPlayerBar::StatusPlayerBar(bool is_mana_bar, const sf::Vector2f& camera_size) {
    is_mana_bar_ = is_mana_bar;

    //Install sprite according to whether it's mana or health
    if (is_mana_bar_) {
        icon_sprite_.setTexture(AssetManager::getInstance()->getTexture("mana"));
    } else {
        icon_sprite_.setTexture(AssetManager::getInstance()->getTexture("heart"));
    }

    //Install back ground bar (default = Black)
    bg_bar_.setOutlineThickness(2.0f);
    bg_bar_.setOutlineColor(sf::Color::Black);
    bg_bar_.setFillColor(sf::Color::Black);

    //Install color according to whether it's mana or health
    if (is_mana_bar_)
        bar_.setFillColor(sf::Color::Blue);
    else
        bar_.setFillColor(sf::Color::Red);

    //Install font and set default value
    procent_.setFont(AssetManager::getInstance()->getFont("eight_bits"));
    procent_.setString(std::to_string(100) + "%");
    procent_.setFillColor(sf::Color::Black);
    procent_.setOutlineColor(sf::Color::White);
    procent_.setOutlineThickness(0.5);

    //Set begining status
    max_status_ = 100;
    current_status_ = 100;

    setObjectsPositions(camera_size);
}

//This setting allows you to adjust to the size of the window and display sprite correctly
void StatusPlayerBar::setObjectsPositions(const sf::Vector2f& camera_size) {
    //Postion sprite for our icon (heart or mana)
    icon_sprite_.setScale(static_cast<float>(camera_size.x) / 1650.0f, static_cast<float>(camera_size.y) / 900.0f);
    if (is_mana_bar_)
        icon_sprite_.setPosition(static_cast<float>(camera_size.x) / 2.0f + static_cast<float>(camera_size.x / 2) * 10.0f / 100.0f, 
                                static_cast<float>(camera_size.y) / 25.0f);
    else
        icon_sprite_.setPosition(static_cast<float>(camera_size.x) / 2.0f - static_cast<float>(camera_size.x / 2) * 20.0f / 100.0f, 
                                static_cast<float>(camera_size.y) / 25.0f);
    
    //Position full bar
    bg_bar_.setSize(sf::Vector2f(sf::Vector2f(static_cast<float>(camera_size.x) / 10.0f, 
                    static_cast<float>(camera_size.y) / 30.0f)));
    bg_bar_.setPosition(icon_sprite_.getPosition().x + (icon_sprite_.getGlobalBounds().width / 2), 
                        icon_sprite_.getPosition().y + (icon_sprite_.getGlobalBounds().height / 2.0f) - (bg_bar_.getGlobalBounds().height / 2.0f));

    //Position dynamic bar
    bar_.setSize(sf::Vector2f(bg_bar_.getSize().x, bg_bar_.getSize().y));
    bar_.setPosition(bg_bar_.getPosition().x, 
                    bg_bar_.getPosition().y);

    //Position text out %
    procent_.setCharacterSize(static_cast<unsigned int>(camera_size.y / 1650.0f * 125));
    procent_.setPosition(bg_bar_.getPosition().x + (bg_bar_.getGlobalBounds().width / 4.0f), 
                            bg_bar_.getPosition().y - (bg_bar_.getGlobalBounds().height * 2.0f));
}


//Set current status if value greatest than one
void StatusPlayerBar::setStatus(uint16_t status) {
    if (status < 0) {
        std::cerr << "Error at StatusBar class. setStatus(uint8_t status). status can't be less than zero!" << std::endl;
        return;
    }

    current_status_ = status;

    uint16_t procent = static_cast<uint16_t>(static_cast<float>(current_status_) / static_cast<float>(max_status_) * 100.0f);

    bar_.setSize(sf::Vector2f(bg_bar_.getSize().x * (float)current_status_ / (float)max_status_, bg_bar_.getSize().y));
    procent_.setString(std::to_string(procent) + "%");
}

void StatusPlayerBar::setMaxStatus(uint16_t max_status) {
    max_status_ = max_status;
    setStatus(current_status_);
}

sf::Sprite StatusPlayerBar::getSprite() const {
    return icon_sprite_;
}

sf::RectangleShape StatusPlayerBar::getBgBar() const {
    return bg_bar_;
}

sf::RectangleShape StatusPlayerBar::getBar() const {
    return bar_;
}

sf::Text StatusPlayerBar::getText() const {
    return procent_;
}
