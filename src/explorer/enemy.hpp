#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "explorer/character.hpp"

namespace explorer {
class Enemy : public Character
{
public:
    Enemy();
    ~Enemy() = default;

    virtual void spawn(sf::Vector2i const& start_pose) override;
    void light_up(sf::FloatRect const& boundary);
    sf::FloatRect get_kill_boundaries() const;

private:
    virtual void set_sprite(sf::Vector2i const& start_pose) override;
};

}  // namespace explorer
