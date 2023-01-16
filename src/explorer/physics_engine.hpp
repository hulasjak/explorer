#pragma once

#include "explorer/location.hpp"
#include "explorer/character.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <memory>

namespace explorer {
class PhysicsEngine
{
public:
    const int TILE_SIZE = 64;

    PhysicsEngine();
    ~PhysicsEngine();

    void init(std::shared_ptr<Location> location);

    void update(sf::Vector2i const& direction, std::shared_ptr<Character> character);

private:
    bool can_move(sf::Vector2i const& displacement, sf::FloatRect const& character_boundary);

    int sign_of(float const number);
    /// Logical level representation
    std::shared_ptr<Location> _location;

    // dt at 30fps in s
    float const _dt{0.033};
};

}  // namespace explorer
