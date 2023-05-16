#include "Player.hpp"

void Player::initShape(sf::Vector2f size)
{
    shape.setFillColor(sf::Color::White);
    shape.setSize(size);
}

void Player::initPhysics()
{
    speed = 50;
    max_speed = 400;
    gravity_acceleration = 1000;
    jump_speed = 200;
    moving = false;
    is_jumping = false;
    jump_time = 0;
    max_jump_time = 0.1;

    displacement = sf::Vector2(0.f, 0.f);
    velocity = sf::Vector2(0.f, 0.f);
    acceleration = sf::Vector2(0.f, gravity_acceleration);
}

Player::Player(sf::Vector2f hit_box_size, sf::Vector2f hit_box_position)
    : Entity(hit_box_size, hit_box_position)
{
    initShape(hit_box_size);
    initPhysics();
}

void Player::setPosition(float const x, float const y)
{
    hit_box.setPosition(x, y);
    shape.setPosition(x, y);
}

void Player::move(sf::Vector2f velocity)
{
    shape.move(velocity);
    hit_box.move(velocity);
}

void Player::updateMovement(const float delta_time, sf::RenderWindow &window)
{
    displacement = sf::Vector2f(0, 0);

    // Получаем время, прошедшее с предыдущего кадра
    bool moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        acceleration.x = -speed / delta_time;

        // Ограничиваем скорость персонажа
        if (velocity.x < -max_speed)
        {
            velocity.x = -max_speed;
        }
        moving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        acceleration.x = speed / delta_time;

        // Ограничиваем скорость персонажа
        if (velocity.x > max_speed)
        {
            velocity.x = max_speed;
        }
        moving = true;
    }

    // Обрабатываем торможение персонажа
    if (!moving)
    {
        velocity.x = 0;
    }

    // Обрабатываем прыжок персонажа
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_jumping)
    {
        // Проверяем, находится ли персонаж на земле
        if (getPosition().y + getGlobalBounds().height >= window.getSize().y)
        {
            is_jumping = true;
            jump_time = 0;
            velocity.y = -jump_speed;
        }
    }

    if (is_jumping)
    {
        jump_time += delta_time;
        if (jump_time < max_jump_time)
        {
            acceleration.y = gravity_acceleration - jump_speed / max_jump_time;
        }
        else
        {
            is_jumping = false;
            acceleration.y = gravity_acceleration;
        }
    }

    // Обновляем ускорение, скорость и позицию персонажа
    velocity += acceleration * delta_time;
    displacement = velocity * delta_time;

    move(displacement);

    acceleration.x = 0;
}

void Player::updateCollision(sf::RenderWindow &window)
{
    // Ограничиваем движение персонажа по горизонтали
    if (getPosition().x < 0)
    {
        setPosition(0, getPosition().y);
    }
    if (getPosition().x + getGlobalBounds().width > window.getSize().x)
    {
        setPosition(window.getSize().x - getGlobalBounds().width, getPosition().y);
    }

    // Ограничиваем движение персонажа по вертикали
    if (getPosition().y + getGlobalBounds().height > window.getSize().y)
    {
        setPosition(getPosition().x, window.getSize().y - getGlobalBounds().height);
        is_jumping = false;
        velocity.y = 0.f;
    }
    if (getPosition().y < 0)
    {
        setPosition(getPosition().x, 0);
    }
}

void Player::update(const float delta_time, sf::RenderWindow &window)
{
    updateMovement(delta_time, window);
    updateCollision(window);
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(shape);
    target.draw(hit_box);
}
