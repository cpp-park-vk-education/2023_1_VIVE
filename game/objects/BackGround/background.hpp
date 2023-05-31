#pragma once

#include "asset_manager.hpp"
#include "unordered_map"
#include "object.hpp"
#include <string>

enum TextureMap {
    GREEN_WORLD_TEMPLE = 2,
    GREEN_WORLD_TEMPLE_BACK_MOUNATIN = 200,
    GREEN_WORLD_TEMPLE_FRONT_MOUNTAIN = 201,
    GREEN_WORLD_TEMPLE_BACK_BACK_GRASS = 202,
    GREEN_WORLD_TEMPLE_BACK_FRONT_GRASS = 203,
    GREEN_WORLD_TEMPLE_FRONT_BACK_GRASS = 204,
    GREEN_WORLD_TEMPLE_FRONT_FRONT_GRASS = 205,
};

class BackGround : public Object
{
private:
    std::unordered_map<TextureMap, std::string> maps_;
    std::vector<sf::Sprite> sprites_;
    bool is_parallax_;
    sf::Vector2u window_size_;

    void update(const sf::Event &event, const float delta_time) {}
    virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const override;

public:
    BackGround(const sf::Vector2u& window_size, bool parallax_effect = false);
    ~BackGround();
    
    void move(sf::Vector2f goal_coor);
};

using BackGroundShPtr = std::shared_ptr<BackGround>;
