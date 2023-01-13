#include "explorer/enemy.hpp"

namespace explorer {

Enemy::Enemy() {}

void Enemy::spawn(std::string name, sf::Vector2i const& start_pose)
{
    set_sprite(start_pose);
    _name       = name;
    _move_speed = 1;
}

void Enemy::set_sprite(sf::Vector2i const& start_pose)
{
    if (!_texture.loadFromFile("resources/graphics/enemies/goblin/goblin_idle_anim_f0.png")) {
        throw std::runtime_error("Failed to load enemy texture");
    };
    _sprite.setTexture(_texture, true);
    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(start_pose.x * 64, start_pose.y * 64);
}

}  // namespace explorer