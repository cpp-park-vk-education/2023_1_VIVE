#include <SFML/Graphics.hpp>

struct AnimParametrs {
    int begin_pos_x;
    int begin_pos_y;
    int offset_x;
    int offset_y;
    float frame_duration;
    bool looped;
    int count_of_frames;
};

enum AnimStates {
    LEFT_RUN_ANIM,
    RIGHT_RUN_ANIM,
    JUMP_ANIM,
    STAY_ANIM,
    DEATH_ANIM,
    ATTACK_ANIM,
    GET_DAMMAGE,
    PARTICLE_ATTACK,
};

class IAnimatable {
public:
    virtual ~IAnimatable() = default;

    virtual void changeAnimation(AnimStates current_state) = 0;
    virtual void update(float delta_time) = 0;
    virtual sf::Sprite getSpriteAnimation() const = 0;
};
