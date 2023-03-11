#include "explorer/enemy.hpp"
namespace explorer {

Enemy::Enemy()
{
    _active_textures.resize(5);
    _idle_textures.resize(5);
    set_animation("resources/graphics/enemies/goblin/goblin_run_anim_f", _active_textures);
    set_animation("resources/graphics/enemies/goblin/goblin_idle_anim_f", _idle_textures);
    _sprite.setScale(2.0, 2.0);
}

void Enemy::spawn(sf::Vector2i const& start_pose)
{
    _sprite.setPosition(start_pose.x * 64, start_pose.y * 64);
    _max_speed = 100;
    _max_acc   = 10;
    _spawned   = true;
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

bool Enemy::is_spawned() const
{
    return _spawned;
}
void Enemy::is_spawned(bool spawned)
{
    _spawned = spawned;

    if (!spawned)
        _sprite.setColor(sf::Color::Transparent);
}

}  // namespace explorer