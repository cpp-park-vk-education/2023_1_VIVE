#include "background.hpp"

BackGround::BackGround(const sf::Vector2u &window_size, bool parallax_effect) : window_size_(window_size), is_parallax_(parallax_effect)
{

    priority_ = PRIORITY::BACKGROUND;


    if (!is_parallax_) {
        sprites_.resize(1, sf::Sprite());

        maps_[GREEN_WORLD_TEMPLE] = "green_world_temple";
        sf::Texture texture = AssetManager::getInstance()->getTexture(maps_[GREEN_WORLD_TEMPLE]);
        sprites_[0].setTexture(AssetManager::getInstance()->getTexture(maps_[GREEN_WORLD_TEMPLE]));
        sprites_[0].setScale(static_cast<float>(window_size_.x) / texture.getSize().x, 
                        static_cast<float>(window_size_.y) / texture.getSize().y);
    } else {
        sprites_.resize(7);

        maps_[GREEN_WORLD_TEMPLE] = "green_world_temple";
        maps_[GREEN_WORLD_TEMPLE_BACK_MOUNATIN] = "green_world_temple_mt_1";
        maps_[GREEN_WORLD_TEMPLE_FRONT_MOUNTAIN] = "green_world_temple_mt_2";
        maps_[GREEN_WORLD_TEMPLE_BACK_BACK_GRASS] = "green_world_temple_gr_1";
        maps_[GREEN_WORLD_TEMPLE_BACK_FRONT_GRASS] = "green_world_temple_gr_2";
        maps_[GREEN_WORLD_TEMPLE_FRONT_BACK_GRASS] = "green_world_temple_gr_3";
        maps_[GREEN_WORLD_TEMPLE_FRONT_FRONT_GRASS] = "green_world_temple_gr_4";

        int i = 0;

        for (auto& iter : maps_) {
            sf::Texture texture = AssetManager::getInstance()->getTexture(iter.second);
            sprites_[i].setTexture(AssetManager::getInstance()->getTexture(iter.second));
            sprites_[i].setScale(static_cast<float>(window_size_.x) / texture.getSize().x, 
                        static_cast<float>(window_size_.y) / texture.getSize().y);
            ++i;
        }
    }
}

void BackGround::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    for (int i = sprites_.size() - 1; i >= 0; --i) {
        target.draw(sprites_[i]);
    }
}

void BackGround::move(sf::Vector2f goal_coor) {
    for (int i = sprites_.size() - 1; i >= 0; --i) {
        sprites_[i].setPosition(goal_coor);
    }
}

BackGround::~BackGround() {
}
