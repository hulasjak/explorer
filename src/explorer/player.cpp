#include <explorer/player.hpp>

namespace explorer {

Player::Player() {}

void Player::spawn(sf::Vector2i const& start_pose)
{
    set_sprite(start_pose);
    _max_speed = 200;
    _max_acc   = 30;
    _lives     = 3;
}

void Player::set_sprite(sf::Vector2i const& start_pose)
{
    set_animation("resources/graphics/heroes/knight/knight", 5);
    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(start_pose.x * 64, start_pose.y * 64);
    _start_pose = start_pose;
}

bool Player::get_win() const
{
    return _won;
}

void Player::set_win(bool state)
{
    _won = state;
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

}  // namespace explorer