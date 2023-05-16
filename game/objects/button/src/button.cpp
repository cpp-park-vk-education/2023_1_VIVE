#include "button.hpp"

#include "game.hpp"

void Button::setParams(const std::string &txt, unsigned int charSize, const std::string &fnt, float frameThickness, float padd,
               sf::Color textColor, sf::Color backColor) {
    padding = padd;
    back_color_ = backColor;

    text_.setString(txt);
    text_.setCharacterSize(charSize);
    text_.setFillColor(textColor);
    setFont(fnt);

    updateFrameSize();
    frame.setFillColor(backColor);
    frame.setOutlineThickness(frameThickness);

    initPosition();
}

void Button::initPosition() {
    frame.setPosition(0, 0);
    text_.setPosition(padding, padding);
}

void Button::setFont(const std::string &fontPath) {
    font_.loadFromFile(fontPath);
    text_.setFont(font_);
}

void Button::setPosition(float x, float y) {
    frame.setPosition(x, y);
    text_.setPosition(padding + x, y - padding);
}


bool Button::isMouseOver(const sf::RenderWindow &window) {
    sf::Vector2f frPos = frame.getPosition();
    sf::FloatRect frBds = frame.getGlobalBounds();

    float xPos = sf::Mouse::getPosition(window).x;
    float yPos = sf::Mouse::getPosition(window).y;
    return xPos >= frPos.x && xPos <= frPos.x + frBds.width &&
           yPos >= frPos.y && yPos <= frPos.y + frBds.height;
}

void Button::update(const sf::Event &event) {
    if (!isMouseOver(GameEngine::getWindow())) {
        setBackColor(back_color_);
        return;
    }
    if (event.type == sf::Event::MouseMoved) {
        setBackColor(hover_color_);
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        setBackColor(hover_color_);
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        setBackColor(active_color_);
    }
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(frame);
    target.draw(text_);
}

void Button::setBackColor(const sf::Color &backColor) {
    frame.setFillColor(backColor);
}

void Button::setHoverColor(const sf::Color &color) {
    hover_color_ = color;
}

void Button::setActiveColor(const sf::Color &color) {
    active_color_ = color;
}

void Button::setText(const std::string &text) {
    text_.setString(text);
    updateFrameSize();
}

std::string Button::getText() {
    return text_.getString().toAnsiString();
}

void Button::updateFrameSize() {
    frame.setSize(sf::Vector2f(
            2 * padding + text_.getGlobalBounds().width,
            2 * padding + text_.getGlobalBounds().height));
}
