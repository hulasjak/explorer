#include <explorer/player.hpp>

namespace explorer {

Player::Player() {}

void Player::spawn(sf::Vector2i const& start_pose)
{
    set_sprite(start_pose);
    _max_speed = 200;
    _max_acc   = 30;
}

void Player::set_sprite(sf::Vector2i const& start_pose)
{
    _texture.loadFromFile("resources/graphics/heroes/knight/knight_idle_anim_f0.png");
    _sprite.setTexture(_texture, true);
    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(start_pose.x * 64, start_pose.y * 64);
}

bool Player::get_win() const
{
    return _won;
}

void Player::set_win(bool state)
{
    _won = state;
}

}  // namespace explorer