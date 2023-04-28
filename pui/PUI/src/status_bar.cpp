#include "status_bar.hpp"

//Constructor for StatusBar creating a sprite for icon pui bar and rectangle with text out %
StatusBar::StatusBar(const std::string& image, const std::string& font, unsigned int window_x, unsigned int window_y, bool is_mana) {
    //Create texture and sprite for icon (heart or mana) and position it
    icon_texture_.loadFromFile(image);
    sf::Vector2u texture_size = icon_texture_.getSize();
    icon_sprite_.setTexture(icon_texture_);
    icon_sprite_.setScale(static_cast<float>(window_x) / 1650.0f, static_cast<float>(window_y) / 900.0f);
    if (is_mana)
        icon_sprite_.setPosition(static_cast<float>(window_x) / 2.0f + static_cast<float>(window_x / 2) / 10.0f, static_cast<float>(window_y) / 25.0f);
    else
        icon_sprite_.setPosition(static_cast<float>(window_x) / 2.0f - static_cast<float>(window_x / 2) / 4.0f, static_cast<float>(window_y) / 25.0f);

    //Create full bar
    bar_background_.setSize(sf::Vector2f(sf::Vector2f(static_cast<float>(window_x) / 10.0f, static_cast<float>(window_y) / 30.0f)));
    bar_background_.setOutlineThickness(2.0f);
    bar_background_.setOutlineColor(sf::Color::Black);
    bar_background_.setPosition(icon_sprite_.getPosition().x + (icon_sprite_.getGlobalBounds().width / 2), 
                    icon_sprite_.getPosition().y + (icon_sprite_.getGlobalBounds().height / 2.0f) - (bar_background_.getGlobalBounds().height / 2.0f));
    bar_background_.setFillColor(sf::Color::Black);

    //Create dynamic bar
    bar_.setSize(sf::Vector2f(bar_background_.getSize().x, bar_background_.getSize().y));
    bar_.setPosition(bar_background_.getPosition().x, bar_background_.getPosition().y);
    if (is_mana)
        bar_.setFillColor(sf::Color::Blue);
    else
        bar_.setFillColor(sf::Color::Red);

    //Create text out %
    font_.loadFromFile(font);
    procent_.setFont(font_);
    procent_.setCharacterSize(static_cast<unsigned int>(window_y / 1650.0f * 125));
    procent_.setString(std::to_string(100) + "%");
    procent_.setPosition(bar_background_.getPosition().x + (bar_background_.getGlobalBounds().width / 4.0f), 
                            bar_background_.getPosition().y - (bar_background_.getGlobalBounds().height * 2.2f));
    procent_.setFillColor(sf::Color::Black);

    max_status_ = 100;
    current_status_ = 100;
}

//Update data if player get damage or hilling yourself
void StatusBar::setStatus(int status) {
    current_status_ = status;
    bar_.setSize(sf::Vector2f(bar_background_.getSize().x * (float)current_status_ / (float)max_status_, bar_background_.getSize().y));
    procent_.setString(std::to_string(current_status_) + "%");
}

//Draw StatusBar
void StatusBar::draw(sf::RenderWindow& window) const {
    window.draw(bar_background_);
    window.draw(bar_);
    window.draw(icon_sprite_);
    window.draw(procent_);
}
