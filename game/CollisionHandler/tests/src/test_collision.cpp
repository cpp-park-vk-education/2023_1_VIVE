#include <gtest/gtest.h>

#include "collision_handler.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "enemy.hpp"
#include "boss.hpp"
#include "particle.hpp"

TEST(CheckCollisonTest, PlayerWithPlayerTrue)
{
    CollisionHandler collision_handler;

    Player player_1(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Player player_2(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player_1, player_2);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST(CheckCollisonTest, PlayerWithTileTrue)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Tile tile(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, tile);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST(CheckCollisonTest, PlayerWithParticleTrue)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, particle);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST(CheckCollisonTest, PlayerWithEnemyTrue)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Enemy enemy(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, enemy);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST(CheckCollisonTest, PlayerWithBossTrue)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Boss boss(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, boss);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST(CheckCollisonTest, PlayerWithTileFalse)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(2.f, 2.f));
    Tile tile(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.0f, 0.0f));

    bool actual = collision_handler.checkCollision(player, tile);
    bool expected = true;

    EXPECT_EQ(actual, expected);
}

TEST(CheckCollisonTest, PlayerWithTileFullIn)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));
    Tile tile(sf::Vector2f(2.f, 2.f), sf::Vector2f(0.f, 0.f));

    bool actual = collision_handler.checkCollision(player, tile);
    bool expected = false;

    EXPECT_EQ(actual, expected);
}

