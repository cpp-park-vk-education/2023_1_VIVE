#include "i_animatable.hpp"

class EntityAnimation : public IAnimatable {
public:
    EntityAnimation();
    virtual ~EntityAnimation() override;

    void animate(float delta_time) override;
    void setAnimation(int anim_index) override;
    void setPosition(const sf::Vector2f& pos) override;
    const sf::Vector2f getPosition() const override;
    bool isFinished() const override;
};
