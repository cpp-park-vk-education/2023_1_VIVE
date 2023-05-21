#include <SFML/Graphics.hpp>

class IAnimatable {
public:
    virtual ~IAnimatable() = default;

    virtual void changeAnimation(char current_state) = 0;
    virtual void update(float delta_time) = 0;
    virtual sf::Sprite getSpriteAnimation() const = 0;
};
