#include "collision_handler.hpp"

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{
}

void CollisionHandler::checkPlayerTilesCollision(PlayerShPtr player,
                                                 std::vector<TileShPtr> &tiles)
{
    for (const auto &tile : tiles)
    {
        handleCollision(player, tile);
    }
}

void CollisionHandler::checkParticleTileCollision(ParticleShPtr particle,
                                                  std::vector<TileShPtr> &tiles)
{
    for (const auto &tile : tiles)
    {
        handleCollision(particle, tile);
    }
}

void CollisionHandler::checkParticleSetTileCollision(ParticleSetShPtr particles, std::vector<TileShPtr> &tiles)
{
    for (auto &particle : *particles.get())
    {
        checkParticleTileCollision(particle, tiles);
    }
}

void CollisionHandler::checkEnemyTileCollision(EnemyShPtr enemy,
                                               std::vector<TileShPtr> &tiles)
{
    for (const auto &tile : tiles)
    {
        handleCollision(enemy, tile);
        if (!enemy->isDead())
        {
        }
        else
        {
            ParticleSetShPtr coin_particles = enemy->getCoinParticles();
            ParticleSetShPtr exp_particles = enemy->getExpParticles();

            checkParticleSetTileCollision(coin_particles, tiles);
            checkParticleSetTileCollision(exp_particles, tiles);
        }
    }
}

void CollisionHandler::checkPlayerParticleCollision(PlayerShPtr player,
                                                    ParticleShPtr particle)
{
    if (particle->getVelocity() == sf::Vector2f(0, 0) &&
        checkAABBCollision(player, particle))
    {
        particle->pop();
        switch (particle->getType())
        {
        case ParticeType::COIN:
            player->updateCoinsCount(1);
            break;
        case ParticeType::EXP:
            player->updateExp(1);
            break;

        default:
            break;
        }
    }
}

void CollisionHandler::checkBossTileCollision(BossShPtr boss, std::vector<TileShPtr> &tiles)
{
    for (const auto &tile : tiles)
    {
        handleCollision(boss, tile);
        if (boss->fireBallOut())
        {
            // std::cout << "Collision" << std::endl;
            handleCollision(boss->getFireBall(), tile);
        }
    }
}

void CollisionHandler::checkBossFireBallPlayerCollision(BossShPtr boss, PlayerShPtr player)
{
    if (boss->fireBallOut() &&
        intersects(boss->getFireBall()->getHitBox(), player->getHitBox()))
    {
        player->updateDamageTaken(boss->getDamage());
        boss->getFireBall()->pop();
    }
}

void CollisionHandler::run(std::vector<PlayerShPtr> &players,
                           std::vector<TileShPtr> &tiles,
                           //    ParticleSetShPtrparticles,
                           std::vector<EnemyShPtr> &enemies)
{
    // Cheking Player/Tile collision
    for (auto &player : players)
    {
        checkPlayerTilesCollision(player, tiles);
    }

    // Checking Particle/Tile collision
    // checkParticleSetTileCollision(particles, tiles);

    // Checking Enemy/Tile and Player/Particle collisions
    for (auto &enemy : enemies)
    {
        checkEnemyTileCollision(enemy, tiles);
        if (enemy->isDead())
        {
            ParticleSetShPtr coin_particles = enemy->getCoinParticles();
            ParticleSetShPtr exp_particles = enemy->getExpParticles();

            for (auto &coin_particle : *coin_particles.get())
            {
                checkParticleTileCollision(coin_particle, tiles);
                for (auto &player : players)
                {
                    checkPlayerParticleCollision(player, coin_particle);
                }
            }
            for (auto &exp_particle : *exp_particles.get())
            {
                checkParticleTileCollision(exp_particle, tiles);
                for (auto &player : players)
                {
                    checkPlayerParticleCollision(player, exp_particle);
                }
            }
        }
    }
}

void CollisionHandler::run(std::vector<PlayerShPtr> &players,
                           std::vector<TileShPtr> &tiles,
                           std::vector<EnemyShPtr> &enemies,
                           BossShPtr boss)
{
    run(players, tiles, enemies);

    // check Boss collision
    checkBossTileCollision(boss, tiles);
    for (auto &player : players)
    {
        checkBossFireBallPlayerCollision(boss, player);
    }
}

bool CollisionHandler::checkAABBCollision(const PhysicalObjectShPtr obj1,
                                          const PhysicalObjectShPtr obj2)
{
    HitBox hitbox1 = obj1->getHitBox();
    HitBox hitbox2 = obj2->getHitBox();

    if (hitbox1.doesExist() && hitbox2.doesExist())
    {
        return intersects(hitbox1, hitbox2);
    }
    else
    {
        return false;
    }
}

void CollisionHandler::handleCollision(MovableObjectShPtr movable_obj,
                                       const PhysicalObjectShPtr static_obj)
{
    if (checkAABBCollision(movable_obj, static_obj))
    {
        float delta = movable_obj->getPosition().y +
                      movable_obj->getGlobalBounds().height -
                      static_obj->getPosition().y;

        sf::Vector2f movable_obj_pos = movable_obj->getPosition();

        movable_obj_pos.y -= delta;

        movable_obj->setPosition(movable_obj_pos);

        movable_obj->setVelocity(sf::Vector2f(movable_obj->getVelocity().x, 0));
        movable_obj->slowDown();
    }
}
