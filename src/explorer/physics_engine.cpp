#include "explorer/physics_engine.hpp"

namespace explorer {
PhysicsEngine::PhysicsEngine() {}

PhysicsEngine::~PhysicsEngine() {}

void PhysicsEngine::init(std::shared_ptr<Location> location)
{
    _location = location;
}

void PhysicsEngine::try_moving(sf::Vector2i const& direction, std::shared_ptr<Character> character)
{
    auto rect = character->get_boundaries();
    sf::Vector2i corner1;
    sf::Vector2i corner2;

    if (direction.x == 1) {
        corner1.x = rect.left + rect.width + direction.x * character->get_max_speed();
        corner1.y = rect.top;
        corner2.x = corner1.x;
        corner2.y = rect.top + rect.height;
    }
    else if (direction.x == -1) {
        corner1.x = rect.left + direction.x * character->get_max_speed();
        corner1.y = rect.top;
        corner2.x = corner1.x;
        corner2.y = rect.top + rect.height;
    }
    else if (direction.y == 1) {
        corner1.x = rect.left;
        corner1.y = rect.top + rect.height + direction.y * character->get_max_speed();
        corner2.x = rect.left + rect.width;
        corner2.y = corner1.y;
    }
    else if (direction.y == -1) {
        corner1.x = rect.left;
        corner1.y = rect.top + direction.y * character->get_max_speed();
        corner2.x = rect.left + rect.width;
        corner2.y = corner1.y;
    }
    else {
        return;
    }

    if (_location->is_position_free(corner1) && _location->is_position_free(corner2)) {
        character->move(direction * character->get_max_speed());
    }
}

void PhysicsEngine::update(sf::Vector2i const& direction, std::shared_ptr<Character> character)
{
    auto new_acc      = character->get_current_acc();
    auto new_velocity = character->get_current_velocity();
    if (std::abs(character->get_current_velocity().x) != character->get_max_speed())
        const auto new_acc = character->get_current_acc() + direction;

    if (direction.x == 0) {
        new_acc.-=
    }

    new_velocity      = new_acc * _dt;
    auto displacement = new_velocity * _dt;
    try_moving(displacement, character)
    // for (unsigned int i = 0; i < m_players.size(); ++i) {

    //     setBodyPositionInfo(i);

    //     m_players[i]->SetMovementX(0);
    //     m_players[i]->SetMovementY(0);

    //     float movementY = m_players[i]->GetVelocityY() * delta;
    //     float movementX = m_players[i]->GetVelocityX() * delta;
    // }
}

}  // namespace explorer