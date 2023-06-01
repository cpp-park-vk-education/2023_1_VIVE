#include "i_animation.hpp"
#include "asset_manager.hpp"

class Animation : IAnimatable {
public:
    Animation(const std::string& name_of_animation_object);
    ~Animation() override;

    Animation(const Animation&) = delete;
    Animation(Animation&&) = delete;
    Animation& operator=(const Animation&) = delete;
    Animation& operator=(Animation&&) = delete;

    bool isLeftRun() const;

    void updateSpriteSize(const sf::Vector2f& size_of_sprite);
    void changeAnimation(AnimStates current_state) override;
    void update(float delta_time) override;
    sf::Sprite getSpriteAnimation() const override;

    AnimStates getCurrentState() const;

private:
    void setStayAnimation();
    void setLeftRunAnimation();
    void setRightRunAnimation();
    void setDeathAnimation();
    void setAttackAnimation();
    void setJumpAnimation();
    void setDamageTakenAnimation();

    void playAnimation(float delta_time);
    void playLeftRunAnimation(float delta_time);
    void playRightRunAnimation(float delta_time);

    sf::Vector2f size_of_sprite_;
    sf::Sprite sprite_of_animation_;
    float current_frame_;
    bool is_left_run;
    bool is_playing_;
    int current_offset_;
    AnimParametrs current_animation_;
    AnimStates current_state_;
    std::unordered_map<AnimStates, AnimParametrs> anim_settigns_;
};
