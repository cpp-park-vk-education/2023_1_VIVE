#pragma once

#include <string>

#include "SFML/Graphics.hpp"
#include "boost/signals2.hpp"

#include "iobject.hpp"

class Button;

using ButtonShPtr = std::shared_ptr<Button>;

class Button : public IObject {
private:
    void initPosition();

public:
    void setParams(const std::string& txt, unsigned int charSize, const std::string& font, float frameThickness, float padding,
                   sf::Color textColor = sf::Color::Black, sf::Color backColor = sf::Color::Transparent);

    void setFont(const std::string& fontPath);
    void setPosition(float x, float y);
    void setBackColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    void setActiveColor(const sf::Color& color);

    void setText(const std::string& text);
    std::string getText();

    bool isMouseOver(const sf::RenderWindow& window);

    void update(const sf::Event& event) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void updateFrameSize();

    sf::Text text_;
    sf::Font font_;
    sf::RectangleShape frame;
    float padding = 0;

    sf::Color back_color_;
    sf::Color hover_color_;
    sf::Color active_color_;
};
