#include <gtest/gtest.h>

#include "collision_handler.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "enemy.hpp"
#include "boss.hpp"
#include "particle.hpp"

TEST(CheckCollisonTest, PlayerCollidesWithPlayer)
{
    CollisionHandler collision_handler;

    Player player_1(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Player player_2(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player_1, player_2);

    EXPECT_TRUE(actual);
}

TEST(CheckCollisonTest, PlayerCollidesWithTile)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Tile tile(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, tile);

    EXPECT_TRUE(actual);
}

TEST(CheckCollisonTest, PlayerCollidesWithParticle)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Particle particle(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, particle);

    EXPECT_TRUE(actual);
}

TEST(CheckCollisonTest, PlayerCollidesWithEnemy)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Enemy enemy(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, enemy);

    EXPECT_TRUE(actual);
}

TEST(CheckCollisonTest, PlayerCollidesWithBoss)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f));
    Boss boss(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));

    bool actual = collision_handler.checkCollision(player, boss);

    EXPECT_TRUE(actual);
}

TEST(CheckCollisonTest, PlayerNotCollidesWithTile)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(2.f, 2.f));
    Tile tile(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.0f, 0.0f));

    bool actual = collision_handler.checkCollision(player, tile);

    EXPECT_TRUE(actual);
}

TEST(CheckCollisonTest, PlayerCollidesWithTileFullIn)
{
    CollisionHandler collision_handler;

    Player player(sf::Vector2f(1.f, 1.f), sf::Vector2f(0.5f, 0.5f));
    Tile tile(sf::Vector2f(2.f, 2.f), sf::Vector2f(0.f, 0.f));

    bool actual = collision_handler.checkCollision(player, tile);

    EXPECT_TRUE(actual);
}

