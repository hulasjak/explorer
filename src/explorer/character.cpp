#include "explorer/character.hpp"

using namespace std::chrono_literals;
namespace explorer {

Character::Character() {}

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

void Character::animate()
{
    auto now = std::chrono::system_clock::now();

    if (now - _last_animation > 100ms) {
        if (_current_velocity.x || _current_velocity.y) {
            _sprite.setTexture(_active_textures[_animated_texture]);
        }
        else {
            _sprite.setTexture(_idle_textures[_animated_texture]);
        }
        if (++_animated_texture >= _idle_textures.size()) {
            _animated_texture = 0;
        }
        _last_animation = std::chrono::system_clock::now();
    }
}

}  // namespace explorer