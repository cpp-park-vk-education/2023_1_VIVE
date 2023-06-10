#include "text.hpp"
#include "asset_manager.hpp"

Text::Text(const std::string& s) {
    fnt_ = AssetManager::getInstance()->getFont("eight_bits");
    text_obj_.setString(s);
    text_obj_.setFont(fnt_);
}

void Text::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    target.draw(text_obj_);
}

void Text::update(const sf::Event &event, const float delta_time) {

}

void Text::setCharacterSize(unsigned int size) {
    text_obj_.setCharacterSize(size);
}

void Text::setString(const std::string &str) {
    text_obj_.setString(str);
}

void Text::setPosition(float x, float y) {
    text_obj_.setPosition(x, y);
}

void Text::setFillColor(const sf::Color &color) {
    text_obj_.setFillColor(color);
}

