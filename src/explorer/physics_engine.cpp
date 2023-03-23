#include "explorer/physics_engine.hpp"

namespace explorer {
PhysicsEngine::PhysicsEngine() {}

void PhysicsEngine::init(std::shared_ptr<Location> location)
{
    _location = location;
}

void PhysicsEngine::check_collision(sf::Vector2i& displacement, sf::FloatRect const& character_boundary)
{
    sf::Vector2i corner1;
    sf::Vector2i corner2;

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

void PhysicsEngine::update_motion(sf::Vector2i const& direction, std::shared_ptr<Character> character)
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

    check_collision(displacement, character->get_boundaries());
    character->move(displacement);
    character->set_current_velocity(new_velocity);
    character->animate();
}

bool PhysicsEngine::update_scene(std::shared_ptr<Player> player)
{
    for (auto&& spike : _location->get_spikes()) {
        spike->update_state();
        if (spike->check_contact(player->get_boundaries())) {
            return false;
        }
    }
    for (auto&& health : _location->get_health()) {
        if (health->check_contact(player->get_boundaries())) {
            player->add_life();
            _location->remove_object(health);
        }
    }

    for (auto&& torch : _location->get_torches()) {
        if (torch->check_contact(player->get_boundaries())) {
            _location->boost_light();
            _location->remove_object(torch);
        }
    }
    return true;
}

// find std lib to do this...
int PhysicsEngine::sign_of(float const number)
{
    if (std::abs(number) > 0.0001)
        return std::abs(number) / number;
    else
        return 0;
}

}  // namespace explorer