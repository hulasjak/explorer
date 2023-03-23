#include "explorer/spikes.hpp"
#include <iostream>
using namespace std::chrono_literals;
namespace explorer {

Spikes::Spikes(sf::Vector2u const& spawn_pose)
{
    _idle_textures.resize(1);
    _active_textures.resize(1);

    if (!_idle_textures[0].loadFromFile("resources/graphics/tiles/floor/spikes_anim_f1.png")) {
        throw std::runtime_error("Failed to load texture: ");
    }
    if (!_active_textures[0].loadFromFile("resources/graphics/tiles/floor/spikes_anim_f8.png")) {
        throw std::runtime_error("Failed to load texture: ");
    }
    _sprite.setTexture(_idle_textures[0]);
    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(spawn_pose.x, spawn_pose.y);
}

Spikes::~Spikes() {}

void Spikes::update_state()
{
    auto now = std::chrono::system_clock::now();

    if (now - _last_state_change > 3s) {
        _active            = !_active;
        _last_state_change = now;
    }
    animate();
}

bool Spikes::is_active()
{
    return _active;
}

void Spikes::animate()
{
    if (!_active && _sprite.getTexture() == &_active_textures[0]) {
        _sprite.setTexture(_idle_textures[0]);
    }
    if (_active && _sprite.getTexture() == &_idle_textures[0]) {
        _sprite.setTexture(_active_textures[0]);
    }
}

bool Spikes::check_contact(sf::FloatRect const& external_boundary) const
{
    if (!_active) {
        return false;
    }
    return _sprite.getGlobalBounds().intersects(external_boundary);
}

}  // namespace explorer
