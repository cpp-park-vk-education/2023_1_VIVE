#include <gtest/gtest.h>

#include "hit_box.hpp"

TEST(GetSetPositionHitBoxTest, GetEqualSetTo)
{
    HitBox hit_box(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));

    sf::Vector2f set_to(5.f, 10.f);
    hit_box.setPosition(set_to.x, set_to.y);

    sf::Vector2f actual = hit_box.getPosition();
    sf::Vector2f expected = set_to;

    EXPECT_EQ(actual, expected);
}

TEST(GetGlobalBoundsHitBoxTest, CheckGlobalBoundsAfterInit)
{
    sf::Vector2f size(1.f, 2.f);
    HitBox hit_box(size, sf::Vector2f(0.f, 0.f));

    sf::FloatRect actual_float_rect = hit_box.getGlobalBounds();
    sf::Vector2f actual(actual_float_rect.width, actual_float_rect.height);
    sf::Vector2f expected = size;

    EXPECT_EQ(actual, expected);
}