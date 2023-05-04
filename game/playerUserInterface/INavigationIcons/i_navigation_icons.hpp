#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <vector>
#include <map>

class INavigationIcons {
public:
    virtual std::vector<sf::Sprite> getIcons() = 0;
    virtual ~INavigationIcons();
    INavigationIcons();

protected:
    std::vector<sf::Sprite> nav_sprites_;
    std::map<std::string, std::string> symbol_nd_values_;
};
