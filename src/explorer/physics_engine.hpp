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
    PhysicsEngine();
    ~PhysicsEngine() = default;

    void init(std::shared_ptr<Location> location);
    void update(sf::Vector2i const& direction, std::shared_ptr<Character> character);

private:
    void check_collision(sf::Vector2i& displacement, sf::FloatRect const& character_boundary);

    int sign_of(float const number);
    std::shared_ptr<Location> _location;

    // dt at 30fps in s
    static constexpr float _dt{0.033};
};

}  // namespace explorer
