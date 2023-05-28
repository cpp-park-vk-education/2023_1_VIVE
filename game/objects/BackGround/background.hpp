#pragma once

#include "asset_manager.hpp"
#include "unordered_map"
#include "object.hpp"
#include <string>

enum TextureMap {
    GREEN_WORLD_TEMPLE = 2,
    GREEN_WORLD_TEMPLE_BACK_MOUNATIN = 200,
    GREEN_WORLD_TEMPLE_MIDDLE_MOUNTAIN = 201,
    GREEN_WORLD_TEMPLE_BACK_GRASS = 202,
};

class BackGround : public Object
{
private:
    std::unordered_map<TextureMap, std::string> maps_;
    sf::Vector2u window_size_;

    void update(const sf::Event &event, const float delta_time) {}

public:
    BackGround(const sf::Vector2u& window_size);
    ~BackGround();
    
    void move(sf::Vector2f goal_coor);

    void loadLevelMap(TextureMap level_map);

};

using BackGroundShPtr = std::shared_ptr<BackGround>;
