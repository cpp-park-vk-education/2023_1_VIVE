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
        if (checkAABBCollision(*player, *tile))
        {
            // std::cout << "Collision" << std::endl;

            // std::cout << "Tile upper bound coord = " << tile->getPosition().y << std::endl;
            // std::cout << "Player lower bound coord = " << player->getPosition().y + player->getGlobalBounds().height << std::endl;

            float delta = player->getPosition().y +
                          player->getGlobalBounds().height -
                          tile->getPosition().y;
            
            // std::cout << "delta =" << delta << std::endl;

            sf::Vector2f player_pos = player->getPosition();
            // std::cout << "player_pos_y = " << player_pos.y << std::endl;

            player_pos.y -= delta;
            // std::cout << "player_new_pos_y = " << player_pos.y << std::endl;

            player->setPosition(player_pos);
            // std::cout << "player_pos_y = " << player->getPosition().y << std::endl;
            
            player->setVelocity(sf::Vector2f(player->getVelocity().x, 0));
        }
    }
}

void CollisionHandler::run(std::vector<Player *> &players,
                           std::vector<Tile *> &tiles,
                           std::vector<Enemy *> &enemies)
{
    // Cheking Player/tile collision
    for (auto &player : players)
    {
        checkPlayerTilesCollision(player, tiles);
    }
}

bool CollisionHandler::checkAABBCollision(const PhysicalObject &obj1,
                                          const PhysicalObject &obj2)
{
    HitBox hitbox1 = obj1.getHitBox();
    HitBox hitbox2 = obj2.getHitBox();

    return intersects(hitbox1, hitbox2);
}
