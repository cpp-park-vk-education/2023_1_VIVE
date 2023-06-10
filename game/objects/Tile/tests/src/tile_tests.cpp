#include <gtest/gtest.h>

#include "tile.hpp"

TEST(GetSetPositionPlayerTest, GetEqualSetTo)
{
    Tile tile(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));

    sf::Vector2f set_to(5.f, 10.f);
    tile.setPosition(set_to.x, set_to.y);

    sf::Vector2f actual = tile.getPosition();
    sf::Vector2f expected = set_to;

    EXPECT_EQ(actual, expected);
}
