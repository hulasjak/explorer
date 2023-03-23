#include <explorer/player.hpp>

namespace explorer {

Player::Player()
{
    _active_textures.resize(5);
    _idle_textures.resize(5);
    set_animation("resources/graphics/heroes/knight/knight_idle_anim_f", _idle_textures);
    set_animation("resources/graphics/heroes/knight/knight_run_anim_f", _active_textures);
    _sprite.setScale(2.0, 2.0);
}

void Player::spawn(sf::Vector2i const& start_pose)
{
    _sprite.setPosition(start_pose.x * 64, start_pose.y * 64);
    _start_pose = start_pose;
    _max_speed  = 200;
    _max_acc    = 30;
    _lives      = 3;
}

bool Player::try_to_kill()
{
    if (_lives > 0) {
        _lives -= 1;
        _sprite.setPosition(_start_pose.x * 64, _start_pose.y * 64);
        return true;
    }
    return false;
}

int Player::get_lives() const
{
    return _lives;
}

void Player::add_life()
{
    _lives++;
}

}  // namespace explorer