#include "SFML/Graphics.hpp"


class ICameraTarget {
public:
    ICameraTarget();
    virtual ~ICameraTarget();
    virtual void setCenter(sf::Vector2u& coordinates) = 0;
    virtual void move(sf::Vector2u& offset) = 0;
    virtual sf::Vector2u getCenter() = 0;
    virtual sf::Vector2u getSize() = 0;
    virtual sf::View getTarget() = 0;
    virtual void update(float parametr) = 0;
private:
    sf::View view_;
    std::unique_ptr<sf::RenderTarget> target_;
    sf::Vector2u size_;
};
