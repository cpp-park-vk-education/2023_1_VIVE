#include "i_animation.hpp"
#include "asset_manager.hpp"

class Animation : IAnimatable {
public:
    Animation(const std::string& name_of_animation_object, float frame_duration);
    ~Animation() override;

    Animation(const Animation&) = delete;
    Animation(Animation&&) = delete;
    Animation& operator=(const Animation&) = delete;
    Animation& operator=(Animation&&) = delete;

    bool isLeftRun() const;

    void updateSpriteSize(const sf::Vector2f& size_of_sprite);
    void changeAnimation(char current_state) override;
    void update(float delta_time) override;
    sf::Sprite getSpriteAnimation() const override;

private:
    void setStayAnimation();
    void setLeftRunAnimation();
    void setRightRunAnimation();
    void setDeathAnimation();
    void setAttackAnimation();
    void setJumpAnimation();

    void playStayAnimation(float delta_time);
    void playLeftRunAnimation(float delta_time);
    void playRightRunAnimation(float delta_time);
    void playDeathAnimation(float delta_time);
    void playAttackAnimation(float delta_time);
    void playJumpAnimation(float delta_time);

    sf::Vector2f size_of_sprite_;
    sf::Sprite sprite_of_animation_;
    float current_frame_;
    size_t count_of_frames_;
    float frame_duration_;
    float elapsed_time_;
    bool looped_;
    bool is_playing_;
    bool is_left_run;
    char current_state_;
};
