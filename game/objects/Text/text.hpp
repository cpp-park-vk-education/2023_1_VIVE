#pragma once

#include "object.hpp"

class Text;

using TextShPtr = std::shared_ptr<Text>;

class Text : public Object {
public:
    Text(const std::string& s);

    void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
    void update(const sf::Event &event, const float delta_time) override;

    void setCharacterSize(unsigned int size);
    void setString(const std::string& str);
    void setPosition(float x, float y);
    void setFillColor(const sf::Color& color);

    virtual ~Text() {}

private:
    sf::Font fnt_;

    sf::Text text_obj_;
};
