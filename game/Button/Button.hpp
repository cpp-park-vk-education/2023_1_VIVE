#pragma once

#include "SFML/Graphics.hpp"

class Button : public sf::Drawable {
 private:
    void initPosition();

 public:
    Button(const std::string& txt, unsigned int charSize, const std::string& font, float frameThickness, float padding,
           sf::Color textColor = sf::Color::Black, sf::Color backColor = sf::Color::Transparent);


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setFont(const std::string& fontPath);
    void setPosition(float x, float y);
    void setBackColor(sf::Color color);
    void resetBackColor();
    bool isMouseOver(const sf::RenderWindow& window);

 private:
    sf::Text text;
    sf::Font font;
    sf::RectangleShape frame;

    float padding;
};
