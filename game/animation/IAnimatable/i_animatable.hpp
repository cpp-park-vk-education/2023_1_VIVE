#include "SFML/Graphics.hpp"
#include <vector>

class IAnimatable {
public:
    virtual void animate(float delta_time) = 0;
    virtual void setAnimation(int anim_index) = 0;
    virtual void setPosition(const sf::Vector2f& pos) = 0;
    virtual const sf::Vector2f getPosition() const = 0;
    virtual bool isFinished() const = 0;
    virtual ~IAnimatable();
    IAnimatable();

private:
    std::vector<sf::Sprite> anim_sprites_;
    int current_frame_;
    float animation_time_;
    float time_per_game_;
    bool finished_;
};