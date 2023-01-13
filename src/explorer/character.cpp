#include "explorer/character.hpp"

namespace explorer {

Character::Character() {}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}

std::string Character::get_name()
{
    return _name;
}

int Character::get_max_speed() const
{
    return _max_speed;
}

sf::Vector2i Character::get_current_velocity() const
{
    return _current_velocity;
}

void Character::set_current_velocity(sf::Vector2i updated_velocity)
{
    _current_velocity = updated_velocity;
}

sf::Vector2i Character::get_current_acc() const
{
    return _current_acc;
}

void Character::set_current_acc(sf::Vector2i updated_acc)
{
    _current_acc = updated_acc;
}

void Character::move(sf::Vector2i direction, int speed)
{
    _sprite.move(direction.x * speed, direction.y * speed);
}

sf::FloatRect Character::get_boundaries() const
{
    return _sprite.getGlobalBounds();
}

}  // namespace explorer