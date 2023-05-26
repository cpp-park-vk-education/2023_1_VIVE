#pragma once

#include <string>

#include "SFML/Graphics.hpp"
#include "boost/signals2.hpp"

#include "object.hpp"

class Button;

using ButtonShPtr = std::shared_ptr<Button>;

class Button : public Object {
private:
    void initPosition();

public:
    Button();
    ~Button();
    void setParams(const std::string& txt, unsigned int charSize, float frameThickness, float padding,
                   sf::Color textColor = sf::Color::Black, sf::Color backColor = sf::Color::Transparent);

    void setFont(const sf::Font& font);
    void setPosition(float x, float y);
    void setBackColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    void setActiveColor(const sf::Color& color);

    void setText(const std::string& text);
    std::string getText();

    bool isMouseOver(const sf::RenderWindow& window);

    void update(const sf::Event &event, const float delta_time) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void updateFrameSize();

    sf::Font font_;

    sf::Text text_;
    sf::RectangleShape frame;
    float padding = 0;

    sf::Color back_color_;
    sf::Color hover_color_;
    sf::Color active_color_;
};
