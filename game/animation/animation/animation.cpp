#include "animation.hpp"
#include <iostream>

Animation::Animation(const std::string& name_of_animation_object, float frame_duration)
    : current_frame_(0), frame_duration_(frame_duration), elapsed_time_(0), 
    looped_(false), is_playing_(false), current_state_('s'), count_of_frames_(0), is_left_run(false) {
        sprite_of_animation_.setTexture(AssetManager::getInstance()->getTexture(name_of_animation_object));
        sprite_of_animation_.setTextureRect(sf::IntRect(6,4,17,27));
        size_of_sprite_ = sf::Vector2f(sprite_of_animation_.getGlobalBounds().width, sprite_of_animation_.getGlobalBounds().height);
        setStayAnimation();
}

Animation::~Animation() {
}

bool Animation::isLeftRun() const {
        return is_left_run;
}

void Animation::updateSpriteSize(const sf::Vector2f &size_of_sprite) {
        size_of_sprite_ = size_of_sprite;
}

void Animation::changeAnimation(char current_state) {
        if (is_playing_ && current_state == 's' && current_state_ != 's')
                return;

        if (is_playing_ && current_state_ == 'j') {
                if (current_state == 'l')
                        is_left_run = true;
                else if (current_state == 'r')
                        is_left_run = false;
                return;
        }

        current_state_ = current_state;

        switch (current_state_)
        {
        case 'l':
                setLeftRunAnimation();
                break;
        case 'r':
                setRightRunAnimation();
                break;
        case 'j':
                setJumpAnimation();
                break;
        case 's':
                setStayAnimation();
                break;
        case 'd':
                setDeathAnimation();
                break;
        case 'a':
                setAttackAnimation();
                break;
        default:        
                break;
        }
        is_playing_ = true;
}

void Animation::update(float delta_time) {
        if (!is_playing_ && !looped_)
                return;

        current_frame_ += frame_duration_ * delta_time;
        if (int(current_frame_) > count_of_frames_) {
                current_frame_ = 0;
                is_playing_ = false;
        }

        switch (current_state_)
        {
        case 'l':
                playLeftRunAnimation(current_frame_);
                break;
        case 'r':
                playRightRunAnimation(current_frame_);
                break;
        case 'j':
                playJumpAnimation(current_frame_);
                break;
        case 's':
                playStayAnimation(current_frame_);
                break;
        case 'd':
                playDeathAnimation(current_frame_);
                break;
        case 'a':
                playAttackAnimation(current_frame_);
                break;
        default:        
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
        frame_duration_ = 7.5f;
        looped_ = true;
        count_of_frames_ = 1;
}

void Animation::setLeftRunAnimation() {
        current_frame_ = 0;
        frame_duration_ = 10.0f;
        is_left_run = true;
        looped_ = true;
        count_of_frames_ = 3;
}

void Animation::setRightRunAnimation() {
        current_frame_ = 0;
        frame_duration_ = 10.0f;
        is_left_run = false;
        looped_ = true;
        count_of_frames_ = 3;
}

void Animation::setDeathAnimation() {
        current_frame_ = 0;
        looped_ = false;
        count_of_frames_ = 4;
}

void Animation::setAttackAnimation() {
        current_frame_ = 0;
        frame_duration_ = 40.0f;
        looped_ = false;
        count_of_frames_ = 7;
}

void Animation::setJumpAnimation() {
        current_frame_ = 0;
        frame_duration_ = 10.0f;
        looped_ = false;
        count_of_frames_ = 7;
}

void Animation::playStayAnimation(float delta_time) {
        if (is_left_run)
                sprite_of_animation_.setTextureRect(sf::IntRect(24 + 32 * int(current_frame_), 4, -17, 27));
        else
                sprite_of_animation_.setTextureRect(sf::IntRect(7 + 32 * int(current_frame_), 4, 17, 27));
}

void Animation::playLeftRunAnimation(float delta_time) { 
        sprite_of_animation_.setTextureRect(sf::IntRect(23 + 32 * int(current_frame_), 68, -17, 27));
}

void Animation::playRightRunAnimation(float delta_time) {
        sprite_of_animation_.setTextureRect(sf::IntRect(6 + 32 * int(current_frame_), 68, 17, 27));
}

void Animation::playJumpAnimation(float delta_time) {
        if (is_left_run)
                sprite_of_animation_.setTextureRect(sf::IntRect(24 + 32 * int(current_frame_), 162, -17, 29));
        else
                sprite_of_animation_.setTextureRect(sf::IntRect(7 + 32 * int(current_frame_), 162, 17, 29));
}

void Animation::playAttackAnimation(float delta_time) {
        if (is_left_run)
                sprite_of_animation_.setTextureRect(sf::IntRect(24 + 32 * int(current_frame_), 260, -17, 27));
        else
                sprite_of_animation_.setTextureRect(sf::IntRect(7 + 32 * int(current_frame_), 260, 17, 27));
}

void Animation::playDeathAnimation(float delta_time) {
        if (is_left_run)
                sprite_of_animation_.setTextureRect(sf::IntRect(24 + 32 * int(current_frame_), 196, -17, 27));
        else
                sprite_of_animation_.setTextureRect(sf::IntRect(7 + 32 * int(current_frame_), 196, 17, 27));
}
