#include "iostream"
#include "Button.hpp"

Button::Button(const std::string& txt, unsigned int charSize, const std::string& fnt, float frameThickness, float padd,
               sf::Color textColor, sf::Color backColor) {
    padding = padd;

    text.setString(txt);
    text.setCharacterSize(charSize);
    text.setFillColor(textColor);
    setFont(fnt);

    frame.setSize(sf::Vector2f(
            2 * padding + text.getGlobalBounds().width,
            2 * padding + text.getGlobalBounds().height));
    frame.setFillColor(backColor);
    frame.setOutlineThickness(frameThickness);

    initPosition();
}

void Button::initPosition() {
    frame.setPosition(0, 0);
    text.setPosition(padding, padding);
}

void Button::setFont(const std::string& fontPath) {
    font.loadFromFile(fontPath);
    text.setFont(font);
}

void Button::setPosition(float x, float y) {
    frame.setPosition(x, y);
    text.setPosition(padding + x, y - padding);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(frame);
    target.draw(text);
}

void Button::setBackColor(sf::Color backColor) {
    frame.setFillColor(backColor);
}

void Button::resetBackColor() {
    frame.setFillColor(sf::Color::Transparent);
}

bool Button::isMouseOver(const sf::RenderWindow& window) {
    sf::Vector2f frPos = frame.getPosition();
    sf::FloatRect frBds = frame.getGlobalBounds();

    float xPos = sf::Mouse::getPosition(window).x;
    float yPos = sf::Mouse::getPosition(window).y;
    return xPos >= frPos.x && xPos <= frPos.x + frBds.width &&
           yPos >= frPos.y && yPos <= frPos.y + frBds.height;
}


