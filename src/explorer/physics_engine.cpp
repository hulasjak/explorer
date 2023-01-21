#include "explorer/physics_engine.hpp"

namespace explorer {
PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::init(std::shared_ptr<Location> location)
{
    _location = location;
}

void PhysicsEngine::can_move(sf::Vector2i& displacement, sf::FloatRect const& character_boundary)
{
    sf::Vector2i corner1;
    sf::Vector2i corner2;

    // todo alow to slide
    // check pure x movement
    if (displacement.x > 0) {
        corner1.x = character_boundary.left + character_boundary.width + displacement.x;
        corner1.y = character_boundary.top;
        corner2.x = corner1.x;
        corner2.y = corner1.y + character_boundary.height;
    }
    else if (displacement.x < 0) {
        corner1.x = character_boundary.left + displacement.x;
        corner1.y = character_boundary.top;
        corner2.x = corner1.x;
        corner2.y = corner1.y + character_boundary.height;
    }
    if (!_location->is_position_free(corner1) || !_location->is_position_free(corner2)) {
        displacement.x = 0;
    }

    if (displacement.y > 0) {
        corner1.x = character_boundary.left + displacement.x;
        corner1.y = character_boundary.top + character_boundary.height + displacement.y;
        corner2.x = corner1.x + character_boundary.width;
        corner2.y = corner1.y;
    }
    else if (displacement.y < 0) {
        corner1.x = character_boundary.left + displacement.x;
        corner1.y = character_boundary.top + displacement.y;
        corner2.x = corner1.x + character_boundary.width;
        corner2.y = corner1.y;
    }

    if (!_location->is_position_free(corner1) || !_location->is_position_free(corner2)) {
        displacement.y = 0;
    }
}

void PhysicsEngine::update(sf::Vector2i const& direction, std::shared_ptr<Character> character)
{
    auto new_velocity  = character->get_current_velocity();
    const auto max_acc = character->get_max_acc();

    // slowing down
    if (sign_of(direction.x) != sign_of(new_velocity.x) && std::abs(new_velocity.x) > 0.0001) {
        new_velocity.x -= sign_of(new_velocity.x) * max_acc;
    }
    // accelerating
    else if (direction.x != 0 && std::abs(new_velocity.x) < character->get_max_speed()) {
        new_velocity.x += sign_of(direction.x) * max_acc;
    }

    if (sign_of(direction.y) != sign_of(new_velocity.y) && std::abs(new_velocity.y) > 0.0001) {
        new_velocity.y -= sign_of(new_velocity.y) * max_acc;
    }
    else if (direction.y != 0 && std::abs(new_velocity.y) < character->get_max_speed()) {
        new_velocity.y += sign_of(direction.y) * max_acc;
    }

    // otherwise speed unchanged

    auto displacement = static_cast<sf::Vector2i>(new_velocity * _dt);

    can_move(displacement, character->get_boundaries());
    character->move(displacement);
    character->set_current_velocity(new_velocity);
    character->animate();
}

// find some std lib to do this...
int PhysicsEngine::sign_of(float const number)
{
    if (std::abs(number) > 0.0001)
        return std::abs(number) / number;
    else
        return 0;
}

}  // namespace explorer