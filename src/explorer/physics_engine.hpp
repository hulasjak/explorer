#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <memory>

#include "explorer/location.hpp"
#include "explorer/character.hpp"
#include "explorer/player.hpp"

namespace explorer {
class PhysicsEngine
{
public:
    PhysicsEngine();
    ~PhysicsEngine() = default;

    void init(std::shared_ptr<Location> location);
    void update_motion(sf::Vector2i const& direction, std::shared_ptr<Character> character);
    bool update_scene(std::shared_ptr<Player> player);

private:
    void check_collision(sf::Vector2i& displacement, sf::FloatRect const& character_boundary);

    int sign_of(float const number);
    std::shared_ptr<Location> _location;

    // dt at 30fps in s
    static constexpr float _dt{0.033};
};

}  // namespace explorer
