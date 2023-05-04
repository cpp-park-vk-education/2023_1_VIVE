#include <gtest/gtest.h>

#include "enemy.hpp"

TEST(GetSetPositionEnemyTest, GetEqualSetTo)
{
    Enemy enemy(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));

    sf::Vector2f set_to(5.f, 10.f);
    enemy.setPosition(set_to.x, set_to.y);

    sf::Vector2f actual = enemy.getPosition();
    sf::Vector2f expected = set_to;

    EXPECT_EQ(actual, expected);
}

TEST(MoveEnemyTest, MoveDiagonally)
{
    Enemy enemy(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(1.f, 1.f);
    enemy.move(displacement);

    sf::Vector2f actual = enemy.getPosition();
    sf::Vector2f expected(1.f, 1.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveEnemyTest, NoMove)
{
    Enemy enemy(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 0.f);
    enemy.move(displacement);

    sf::Vector2f actual = enemy.getPosition();
    sf::Vector2f expected(0.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveEnemyTest, MoveAlongX)
{
    Enemy enemy(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(5.f, 0.f);
    enemy.move(displacement);

    sf::Vector2f actual = enemy.getPosition();
    sf::Vector2f expected(5.f, 0.f);

    EXPECT_EQ(actual, expected);
}

TEST(MoveEnemyTest, MoveAlongY)
{
    Enemy enemy(sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 0.f));
    sf::Vector2f displacement(0.f, 5.f);
    enemy.move(displacement);

    sf::Vector2f actual = enemy.getPosition();
    sf::Vector2f expected(0.f, 5.f);

    EXPECT_EQ(actual, expected);
}
