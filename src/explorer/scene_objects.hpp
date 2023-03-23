#pragma once

#include "explorer/physical_object.hpp"
#include <chrono>

namespace explorer {

class Torch : public PhysicalObject
{
public:
    Torch(sf::Vector2u const& spawn_pose);
    ~Torch() = default;

private:
    sf::Texture _texture;
};

class Health : public PhysicalObject
{
public:
    Health(sf::Vector2u const& spawn_pose);
    ~Health() = default;

private:
    sf::Texture _texture;
};

}  // namespace explorer
