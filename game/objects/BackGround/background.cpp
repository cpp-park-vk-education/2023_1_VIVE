#include "background.hpp"

BackGround::BackGround(const sf::Vector2u &window_size, bool parallax_effect) : 
                        window_size_(window_size), is_parallax_(parallax_effect), is_first_entry_(true) {    
    priority_ = Priority::BACKGROUND;

    if (!is_parallax_) {
        layers_speed_.resize(1, 0);
        sprites_.resize(1, sf::Sprite());

        maps_[GREEN_WORLD_TEMPLE] = "green_world_temple";
        sf::Texture texture = AssetManager::getInstance()->getTexture(maps_[GREEN_WORLD_TEMPLE]);
        sprites_[0].setTexture(AssetManager::getInstance()->getTexture(maps_[GREEN_WORLD_TEMPLE]));
        sprites_[0].setScale(static_cast<float>(window_size_.x) / texture.getSize().x, 
                        static_cast<float>(window_size_.y) / texture.getSize().y);
    } else {
        layers_speed_.resize(7, 0);
        sprites_.resize(13);

        maps_[GREEN_WORLD_TEMPLE_FRONT_FRONT_GRASS] = "green_world_temple_gr_4";
        maps_[GREEN_WORLD_TEMPLE_FRONT_BACK_GRASS] = "green_world_temple_gr_3";
        maps_[GREEN_WORLD_TEMPLE_BACK_FRONT_GRASS] = "green_world_temple_gr_2";
        maps_[GREEN_WORLD_TEMPLE_BACK_BACK_GRASS] = "green_world_temple_gr_1";
        maps_[GREEN_WORLD_TEMPLE_FRONT_MOUNTAIN] = "green_world_temple_mt_2";
        maps_[GREEN_WORLD_TEMPLE_BACK_MOUNATIN] = "green_world_temple_mt_1";
        maps_[GREEN_WORLD_TEMPLE] = "green_world_temple";

        int i = 0;

        for (auto& iter : maps_) {
            sf::Texture texture = AssetManager::getInstance()->getTexture(iter.second);
            sprites_[i].setTexture(AssetManager::getInstance()->getTexture(iter.second));
            sprites_[i].setScale(static_cast<float>(window_size_.x) / texture.getSize().x, 
                        static_cast<float>(window_size_.y) / texture.getSize().y);

            ++i;

            if (iter.first != GREEN_WORLD_TEMPLE) {
                texture = AssetManager::getInstance()->getTexture(iter.second);
                sprites_[i].setTexture(AssetManager::getInstance()->getTexture(iter.second));
                sprites_[i].setScale(static_cast<float>(window_size_.x) / texture.getSize().x, 
                        static_cast<float>(window_size_.y) / texture.getSize().y);
            } else {
                continue;
            }
            
            ++i;
        }

        layers_speed_[0] = 0.0f;
        layers_speed_[1] = 0.05f;
        layers_speed_[2] = 0.10f;
        layers_speed_[3] = 0.35f;
        layers_speed_[4] = 0.75f;
        layers_speed_[5] = 1.15f;
        layers_speed_[6] = 2.00f;
    }
}

void BackGround::update(const sf::Event &event, const float delta_time) {
}

void BackGround::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    for (int i = 0; i < sprites_.size(); ++i) {
        target.draw(sprites_[i]);
    }
}

void BackGround::restart() {
    is_first_entry_ = true;
}

void BackGround::move(sf::Vector2f goal_coor, char current_state) {
    if (!is_parallax_) {
        sprites_[0].setPosition(goal_coor);
        return;
    }

    if (is_first_entry_) {
        for (int i = 0; i < sprites_.size(); ++i) {
            sprites_[i].setPosition(goal_coor);
        }

        is_first_entry_ = false;
        last_offset_ = goal_coor;

        return;
    }

    sprites_[0].setPosition(goal_coor);

    int8_t factor = 0;

    if (current_state == 'l') {
        factor = 1;
    } else if (current_state == 'r') {
        factor = -1;
    }

    if (last_offset_.x - goal_coor.x != 0) {
        for (int i = 1; i < sprites_.size(); i += 2) {
            sprites_[i].setPosition(sprites_[i].getPosition().x + (layers_speed_[i / 2 + 1] * factor), goal_coor.y);
            if (sprites_[i].getPosition().x >= goal_coor.x) {
                sprites_[i + 1].setPosition(sprites_[i].getPosition().x - sprites_[i].getGlobalBounds().width, goal_coor.y);
            }
            if (sprites_[i].getPosition().x >= goal_coor.x + window_size_.x) {
                sprites_[i].setPosition(sprites_[i + 1].getPosition().x - sprites_[i].getGlobalBounds().width, goal_coor.y);
                std::swap(sprites_[i], sprites_[i + 1]);
            }
            if (sprites_[i].getPosition().x + sprites_[i].getGlobalBounds().width < goal_coor.x + window_size_.x) {
                sprites_[i].setPosition(goal_coor.x + window_size_.x, goal_coor.y);
                sprites_[i + 1].setPosition(sprites_[i].getPosition().x - sprites_[i].getGlobalBounds().width, goal_coor.y);
            }
        }
    }

    last_offset_ = goal_coor;
}

BackGround::~BackGround() {
}
