#include "explorer/character.hpp"

namespace explorer {

Character::Character() {}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}

int Character::get_max_speed() const
{
    return _max_speed;
}

sf::Vector2f Character::get_current_velocity() const
{
    return _current_velocity;
}

void Character::set_current_velocity(sf::Vector2f const& updated_velocity)
{
    _current_velocity = updated_velocity;
}

int Character::get_max_acc() const
{
    return _max_acc;
}

void Character::move(sf::Vector2i const& direction)
{
    _sprite.move(direction.x, direction.y);
}

sf::FloatRect Character::get_boundaries() const
{
    return _sprite.getGlobalBounds();
}

bool Character::check_contact(sf::FloatRect const& external_boundary) const
{
    return _sprite.getGlobalBounds().intersects(external_boundary);
}

}  // namespace explorer