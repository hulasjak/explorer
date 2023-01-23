#include "explorer/enemy.hpp"
namespace explorer {

Enemy::Enemy() {}

void Enemy::spawn(sf::Vector2i const& start_pose)
{
    set_sprite(start_pose);
    _max_speed = 100;
    _max_acc   = 10;
}

void Enemy::set_sprite(sf::Vector2i const& start_pose)
{
    set_animation("resources/graphics/enemies/goblin/goblin", 5);

    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(start_pose.x * 64, start_pose.y * 64);
}

void Enemy::light_up(sf::FloatRect const& boundary)
{
    if (boundary.intersects(_sprite.getGlobalBounds())) {
        _sprite.setColor(sf::Color::White);
    }
    else {
        _sprite.setColor(sf::Color::Black);
    }
}

sf::FloatRect Enemy::get_kill_boundaries() const
{
    auto boundary   = _sprite.getGlobalBounds();
    boundary.top    = boundary.top - 10;
    boundary.left   = boundary.left - 10;
    boundary.width  = boundary.width + 20;
    boundary.height = boundary.height + 20;
    return boundary;
}

}  // namespace explorer