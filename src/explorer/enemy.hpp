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

    bool is_spawned() const;
    void is_spawned(bool spawned);

private:
    virtual void set_sprite(sf::Vector2i const& start_pose) override;
    bool _spawned{false};
};

}  // namespace explorer
