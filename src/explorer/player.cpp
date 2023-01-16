#include <explorer/player.hpp>

namespace explorer {

Player::Player() {}

void Player::spawn(std::string name, sf::Vector2i const& start_pose)
{
    set_sprite(start_pose);
    _name      = name;
    _max_speed = 100;
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