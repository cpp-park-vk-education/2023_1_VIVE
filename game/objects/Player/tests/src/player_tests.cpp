#include <gtest/gtest.h>

#include "player.hpp"

TEST(GetSetPositionPlayerTest, GetEqualSetTo)
{
    Player player(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));

    sf::Vector2f set_to(5.f, 10.f);
    player.setPosition(set_to.x, set_to.y);

    sf::Vector2f actual = player.getPosition();
    sf::Vector2f expected = set_to;

    EXPECT_EQ(actual, expected);
}

TEST(MovePlayerTest, MoveDiagonally)
{
    Player player(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(1.f, 1.f);
    player.move(displacement);

    sf::Vector2f actual = player.getPosition();
    sf::Vector2f expected(1.f, 1.f);

    EXPECT_EQ(actual, expected);
}

TEST(MovePlayerTest, NoMove)
{
    Player player(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 0.f);
    player.move(displacement);

    sf::Vector2f actual = player.getPosition();
    sf::Vector2f expected(0.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MovePlayerTest, MoveAlongX)
{
    Player player(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(5.f, 0.f);
    player.move(displacement);

    sf::Vector2f actual = player.getPosition();
    sf::Vector2f expected(5.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MovePlayerTest, MoveAlongY)
{
    Player player(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 5.f);
    player.move(displacement);

    sf::Vector2f actual = player.getPosition();
    sf::Vector2f expected(0.f, 5.f);

    EXPECT_EQ(actual, expected);
}