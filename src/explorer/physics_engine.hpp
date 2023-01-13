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

    void try_moving(sf::Vector2i const& direction, std::shared_ptr<Character> character);
    void update(sf::Vector2i const& direction, std::shared_ptr<Character> character);

private:
    /// Logical level representation
    std::shared_ptr<Location> _location;

    // dt at 60fps in ms
    int const _dt{17};
};

}  // namespace explorer
