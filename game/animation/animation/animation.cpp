#include "animation.hpp"
#include <iostream>

Animation::Animation(const std::string& name_of_animation_object)
        : current_frame_(0), current_state_(AnimStates::STAY_ANIM), is_left_run(false), is_playing_(false) {

    sprite_of_animation_.setTexture(AssetManager::getInstance()->getTexture(name_of_animation_object));
    sprite_of_animation_.setTextureRect(sf::IntRect(6,4,17,27));
    size_of_sprite_ = sf::Vector2f(sprite_of_animation_.getGlobalBounds().width, sprite_of_animation_.getGlobalBounds().height);


    std::filesystem::path path_to_config = std::filesystem::current_path().parent_path() / "game" / "animation" / "config";
    std::filesystem::path path_to_file;

    for (const auto& entry : std::filesystem::directory_iterator(path_to_config)) {
        if (entry.path().stem().string() == name_of_animation_object) {
            path_to_file = entry.path();
            break;
        }
    }

    std::fstream file(path_to_file);

    AnimParametrs ap;

    file >> current_offset_;

    file >> ap.begin_pos_x >> ap.begin_pos_y >> ap.offset_x >> ap.offset_y >> ap.frame_duration >> ap.looped >> ap.count_of_frames;
    anim_settigns_[AnimStates::STAY_ANIM] = ap;
    file >> ap.begin_pos_x >> ap.begin_pos_y >> ap.offset_x >> ap.offset_y >> ap.frame_duration >> ap.looped >> ap.count_of_frames;
    anim_settigns_[AnimStates::LEFT_RUN_ANIM] = ap;
    file >> ap.begin_pos_x >> ap.begin_pos_y >> ap.offset_x >> ap.offset_y >> ap.frame_duration >> ap.looped >> ap.count_of_frames;
    anim_settigns_[AnimStates::RIGHT_RUN_ANIM] = ap;
    file >> ap.begin_pos_x >> ap.begin_pos_y >> ap.offset_x >> ap.offset_y >> ap.frame_duration >> ap.looped >> ap.count_of_frames;
    anim_settigns_[AnimStates::DEATH_ANIM] = ap;
    file >> ap.begin_pos_x >> ap.begin_pos_y >> ap.offset_x >> ap.offset_y >> ap.frame_duration >> ap.looped >> ap.count_of_frames;
    anim_settigns_[AnimStates::ATTACK_ANIM] = ap;
    file >> ap.begin_pos_x >> ap.begin_pos_y >> ap.offset_x >> ap.offset_y >> ap.frame_duration >> ap.looped >> ap.count_of_frames;
    anim_settigns_[AnimStates::JUMP_ANIM] = ap;

    anim_settigns_[AnimStates::PARTICLE_ATTACK] = anim_settigns_[AnimStates::ATTACK_ANIM];

    if (!file.eof()) {
        file >> ap.begin_pos_x >> ap.begin_pos_y >> ap.offset_x >> ap.offset_y >> ap.frame_duration >> ap.looped >> ap.count_of_frames;
        anim_settigns_[AnimStates::GET_DAMMAGE] = ap;
    }

    file.close();
}

Animation::~Animation() {
}

bool Animation::isLeftRun() const {
    return is_left_run;
}

void Animation::updateSpriteSize(const sf::Vector2f &size_of_sprite) {
    size_of_sprite_ = size_of_sprite;
}

AnimStates Animation::getCurrentState() const {
    return current_state_;
}

void Animation::changeAnimation(AnimStates current_state) { 
    if (current_state_ == AnimStates::DEATH_ANIM && current_state == AnimStates::DEATH_ANIM)
        return;

    if (is_playing_ && current_state_ == AnimStates::ATTACK_ANIM && current_state != AnimStates::GET_DAMMAGE)
            return;

    if (is_playing_ && current_state_ == AnimStates::GET_DAMMAGE && current_state != AnimStates::GET_DAMMAGE) {
        return;
    }

    if (is_playing_ && current_state_ == AnimStates::JUMP_ANIM && current_state != AnimStates::ATTACK_ANIM) {
            if (current_state == AnimStates::LEFT_RUN_ANIM)
                    is_left_run = true;
            else if (current_state == AnimStates::RIGHT_RUN_ANIM)
                    is_left_run = false;
            return;
    }

    current_state_ = current_state;

    switch (current_state_)
    {
    case AnimStates::LEFT_RUN_ANIM:
            setLeftRunAnimation();
            break;
    case AnimStates::RIGHT_RUN_ANIM:
            setRightRunAnimation();
            break;
    case AnimStates::JUMP_ANIM:
            setJumpAnimation();
            break;
    case AnimStates::STAY_ANIM:
            setStayAnimation();
            break;
    case AnimStates::DEATH_ANIM:
            setDeathAnimation();
            break;
    case AnimStates::ATTACK_ANIM:
    case AnimStates::PARTICLE_ATTACK:
            setAttackAnimation();
            break;
    case AnimStates::GET_DAMMAGE:
            setDamageTakenAnimation();
            break;
    default:        
            break;
    }
    is_playing_ = true;
}

void Animation::update(float delta_time) {
    if (!is_playing_ && !current_animation_.looped)
        return;

    current_frame_ += current_animation_.frame_duration * delta_time;
    if (uint8_t(current_frame_) > current_animation_.count_of_frames) {
            current_frame_ = 0;
            is_playing_ = false;
    }

    switch (current_state_)
    {
    case AnimStates::LEFT_RUN_ANIM:
            playLeftRunAnimation(current_frame_);
            break;
    case AnimStates::RIGHT_RUN_ANIM:
            playRightRunAnimation(current_frame_);
            break;
    default:
            playAnimation(current_frame_);
            break;
    }
}

sf::Sprite Animation::getSpriteAnimation() const {
    sf::Sprite total_sprite = sprite_of_animation_;

    total_sprite.setScale(size_of_sprite_.x / total_sprite.getGlobalBounds().width,
            size_of_sprite_.y / total_sprite.getGlobalBounds().height);

    return total_sprite;
}

void Animation::setStayAnimation() {
    current_animation_ = anim_settigns_[AnimStates::STAY_ANIM];
}

void Animation::setLeftRunAnimation() {
    current_animation_ = anim_settigns_[AnimStates::LEFT_RUN_ANIM];
    is_left_run = true;
}

void Animation::setRightRunAnimation() {
    current_animation_ = anim_settigns_[AnimStates::RIGHT_RUN_ANIM];
    is_left_run = false;
}

void Animation::setDeathAnimation() {
    current_animation_ = anim_settigns_[AnimStates::DEATH_ANIM];
    current_frame_ = 0;
}

void Animation::setAttackAnimation() {
    current_animation_ = anim_settigns_[AnimStates::ATTACK_ANIM];
    current_frame_ = 0;
}

void Animation::setJumpAnimation() {
    current_animation_ = anim_settigns_[AnimStates::JUMP_ANIM];
    current_frame_ = 0;
}

void Animation::setDamageTakenAnimation() {
    current_animation_ = anim_settigns_[AnimStates::GET_DAMMAGE];
    current_frame_ = 0;
}

void Animation::playAnimation(float delta_time) {
    if (is_left_run)
        sprite_of_animation_.setTextureRect(sf::IntRect(current_animation_.begin_pos_x + current_animation_.offset_x + current_offset_ * int(current_frame_),
                                        current_animation_.begin_pos_y, 0 - current_animation_.offset_x, current_animation_.offset_y));
    else
        sprite_of_animation_.setTextureRect(sf::IntRect(current_animation_.begin_pos_x + current_offset_ * int(current_frame_),
                                        current_animation_.begin_pos_y, current_animation_.offset_x, current_animation_.offset_y));
}

void Animation::playLeftRunAnimation(float delta_time) { 
    sprite_of_animation_.setTextureRect(sf::IntRect(current_animation_.begin_pos_x + current_offset_ * int(current_frame_), 
                                        current_animation_.begin_pos_y, current_animation_.offset_x, current_animation_.offset_y));
}

void Animation::playRightRunAnimation(float delta_time) {
    sprite_of_animation_.setTextureRect(sf::IntRect(current_animation_.begin_pos_x + current_offset_ * int(current_frame_), 
                                        current_animation_.begin_pos_y, current_animation_.offset_x, current_animation_.offset_y));
}
