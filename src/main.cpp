// #include "Game.hpp"

// int main() {
//     // Init game
//     Game game;

//     // Game loop
//     while (game.getWindow().isOpen())
//     {
//         // Update
//         game.update();

//         // Render
//         game.render();
//     }

//     return 0;
// }

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main()
{
    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Platformer");
    window.setFramerateLimit(60);

    // Создаем персонажа
    sf::RectangleShape player(sf::Vector2f(50, 50));
    player.setFillColor(sf::Color::Green);
    player.setPosition(100, 100);

    // Устанавливаем скорость персонажа
    float playerSpeed = 10;
    float maxSpeed = 100;

    // Устанавливаем силу трения
    float friction = 300;

    // Устанавливаем гравитацию
    float gravityAcceleration = 500;

    // Устанавливаем скорость прыжка
    float jumpSpeed = 200;

    // Устанавливаем состояние прыжка
    bool isJumping = false;

    // Устанавливаем время прыжка
    float jumpTime = 0;

    // Устанавливаем максимальное время прыжка
    float maxJumpTime = 0.1;

    // Устанавливаем таймер
    sf::Clock clock;

    // float horizontalSpeed = 0.f;

    // Устанавливаем смещение, скорость и ускорение
    sf::Vector2f displacement(0.f, 0.f);
    sf::Vector2f velocity(0.f, 0.f);
    sf::Vector2f acceleration(0.f, gravityAcceleration);

    // Запускаем игровой цикл
    while (window.isOpen())
    {
        // Обрабатываем события в цикле
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Если нажата клавиша "Выход", закрываем окно
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        displacement = sf::Vector2f(0, 0);
        // Получаем время, прошедшее с предыдущего кадра
        float deltaTime = clock.restart().asSeconds();

        bool moving = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            acceleration.x = -playerSpeed / deltaTime;

            // Вычитаем силу трения, если персонаж движется в противоположную сторону
            // if (velocity.x > 0)
            // {
            //     velocity.x -= friction * deltaTime;
            //     if (velocity.x < 0)
            //     {
            //         velocity.x = 0;
            //     }
            // }

            // Ограничиваем скорость персонажа
            if (velocity.x < -maxSpeed)
            {
                velocity.x = -maxSpeed;
            }
            moving = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            acceleration.x = playerSpeed / deltaTime;

            // Вычитаем силу трения, если персонаж движется в противоположную сторону
            // if (velocity.x < 0)
            // {
            //     velocity.x += friction * deltaTime;
            //     if (velocity.x > 0)
            //     {
            //         velocity.x = 0;
            //     }
            // }

            // Ограничиваем скорость персонажа
            if (velocity.x > maxSpeed)
            {
                velocity.x = maxSpeed;
            }
            moving = true;
        }

        // Обрабатываем торможение персонажа
        if (!moving)
        {
            velocity.x = 0;

            // Вычитаем силу торможения, если персонаж движется вправо
            // if (velocity.x > 0)
            // {
            //     acceleration.x -= friction / deltaTime;
            //     if (velocity.x - acceleration.x * deltaTime < 0)
            //     {
            //         velocity.x = 0;
            //         acceleration.x = 0;
            //     }
            // }
            // // Вычитаем силу торможения, если персонаж движется влево
            // if (velocity.x < 0)
            // {
            //     acceleration.x += friction / deltaTime;
            //     if (velocity.x + acceleration.x * deltaTime > 0)
            //     {
            //         velocity.x = 0;
            //         acceleration.x = 0;
            //     }
            // }
        }

        // Обрабатываем прыжок персонажа
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
        {
            // Проверяем, находится ли персонаж на земле
            if (player.getPosition().y + player.getSize().y >= window.getSize().y)
            {
                isJumping = true;
                jumpTime = 0;
                velocity.y = -jumpSpeed;
            }
        }
        if (isJumping)
        {
            jumpTime += deltaTime;
            if (jumpTime < maxJumpTime)
            {
                acceleration.y = gravityAcceleration - jumpSpeed / maxJumpTime;
            }
            else
            {
                isJumping = false;
                acceleration.y = gravityAcceleration;
            }
        }

        // Обновляем скорость и позицию персонажа
        // acceleration.x = horizontalSpeed / deltaTime;
        velocity += acceleration * deltaTime;
        displacement = velocity * deltaTime;
        player.move(displacement);

        acceleration.x = 0;

        // Ограничиваем движение персонажа по горизонтали
        if (player.getPosition().x < 0)
        {
            player.setPosition(0, player.getPosition().y);
        }
        if (player.getPosition().x + player.getSize().x > window.getSize().x)
        {
            player.setPosition(window.getSize().x - player.getSize().x, player.getPosition().y);
        }

        // Ограничиваем движение персонажа по вертикали
        if (player.getPosition().y + player.getSize().y > window.getSize().y)
        {
            player.setPosition(player.getPosition().x, window.getSize().y - player.getSize().y);
            isJumping = false;
            velocity.y = 0.f;
        }
        if (player.getPosition().y < 0)
        {
            player.setPosition(player.getPosition().x, 0);
        }

        // Отрисовываем персонажа и окно
        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}