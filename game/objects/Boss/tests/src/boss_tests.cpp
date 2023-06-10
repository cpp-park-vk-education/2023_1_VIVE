#include <gtest/gtest.h>

#include "boss.hpp"

TEST(GetSetPositionBossTest, GetEqualSetTo)
{
    Boss boss(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));

    sf::Vector2f set_to(5.f, 10.f);
    boss.setPosition(set_to.x, set_to.y);

    sf::Vector2f actual = boss.getPosition();
    sf::Vector2f expected = set_to;

    EXPECT_EQ(actual, expected);
}

TEST(MoveBossTest, MoveDiagonally)
{
    Boss boss(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(1.f, 1.f);
    boss.move(displacement);

    sf::Vector2f actual = boss.getPosition();
    sf::Vector2f expected(1.f, 1.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveBossTest, NoMove)
{
    Boss boss(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 0.f);
    boss.move(displacement);

    sf::Vector2f actual = boss.getPosition();
    sf::Vector2f expected(0.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveBossTest, MoveAlongX)
{
    Boss boss(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(5.f, 0.f);
    boss.move(displacement);

    sf::Vector2f actual = boss.getPosition();
    sf::Vector2f expected(5.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveBossTest, MoveAlongY)
{
    Boss boss(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 5.f);
    boss.move(displacement);

    sf::Vector2f actual = boss.getPosition();
    sf::Vector2f expected(0.f, 5.f);

    EXPECT_EQ(actual, expected);
}