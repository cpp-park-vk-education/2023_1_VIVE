#include "collision_handler.hpp"

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::checkPlayerTilesCollision(Player *player,
                                                 std::vector<Tile *> &tiles)
{
    for (const auto &tile : tiles)
    {
        handleCollision(player, tile);
    }
}

void CollisionHandler::checkParticleTileCollision(Particle *particle,
                                                 std::vector<Tile *> &tiles)
{
    for (const auto &tile : tiles)
    {
        handleCollision(particle, tile);
    }
}

void CollisionHandler::checkParticleSetTileCollision(ParticleSet *particles, std::vector<Tile *> &tiles)
{
    for (auto &particle : *particles)
    {
        checkParticleTileCollision(particle, tiles);
    }
}

void CollisionHandler::checkEnemyTileCollision(Enemy *enemy,
                                               std::vector<Tile *> &tiles)
{
    for (const auto &tile : tiles)
    {
        if (!enemy->isDead())
        {
            handleCollision(enemy, tile);
        }
        else
        {
            ParticleSet *coin_particles = enemy->getCoinParticles();
            ParticleSet *exp_particles = enemy->getExpParticles();

            checkParticleSetTileCollision(coin_particles, tiles);
            checkParticleSetTileCollision(exp_particles, tiles);
        }
    }
}

void CollisionHandler::run(std::vector<Player *> &players,
                           std::vector<Tile *> &tiles,
                           ParticleSet *particles,
                           std::vector<Enemy *> &enemies)
{
    // Cheking Player/Tile collision
    for (auto &player : players)
    {
        checkPlayerTilesCollision(player, tiles);
    }

    // Checking Particle/Tile collision
    checkParticleSetTileCollision(particles, tiles);

    // Checking Enemy/Tile collision
    for (auto &enemy : enemies)
    {
        checkEnemyTileCollision(enemy, tiles);
    }
}

bool CollisionHandler::checkAABBCollision(const PhysicalObject *obj1,
                                          const PhysicalObject *obj2)
{
    HitBox hitbox1 = obj1->getHitBox();
    HitBox hitbox2 = obj2->getHitBox();

    return intersects(hitbox1, hitbox2);
}

void CollisionHandler::handleCollision(MovableObject *movable_obj,
                                       const PhysicalObject *static_obj)
{
    if (checkAABBCollision(movable_obj, static_obj))
        {
            // std::cout << "Collision" << std::endl;

            // std::cout << "Tile upper bound coord = " << tile->getPosition().y << std::endl;
            // std::cout << "Player lower bound coord = " << player->getPosition().y + player->getGlobalBounds().height << std::endl;

            float delta = movable_obj->getPosition().y +
                          movable_obj->getGlobalBounds().height -
                          static_obj->getPosition().y;

            // std::cout << "delta =" << delta << std::endl;

            sf::Vector2f movable_obj_pos = movable_obj->getPosition();
            // std::cout << "player_pos_y = " << player_pos.y << std::endl;

            movable_obj_pos.y -= delta;
            // std::cout << "player_new_pos_y = " << player_pos.y << std::endl;

            movable_obj->setPosition(movable_obj_pos);
            // std::cout << "player_pos_y = " << player->getPosition().y << std::endl;

            movable_obj->setVelocity(sf::Vector2f(movable_obj->getVelocity().x, 0));
            movable_obj->slowDown();
        }
}
