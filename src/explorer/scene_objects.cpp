#include "explorer/scene_objects.hpp"

namespace explorer {

Torch::Torch(sf::Vector2u const& spawn_pose)
{
    if (!_texture.loadFromFile("resources/graphics/props_items/torch_anim_f2.png")) {
        throw std::runtime_error("Failed to load texture: ");
    }
    _sprite.setTexture(_texture);
    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(spawn_pose.x, spawn_pose.y);
}

Health::Health(sf::Vector2u const& spawn_pose)
{
    if (!_texture.loadFromFile("resources/graphics/props_items/potion_red.png")) {
        throw std::runtime_error("Failed to load texture: ");
    }
    _sprite.setTexture(_texture);
    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(spawn_pose.x, spawn_pose.y);
}

}  // namespace explorer