#pragma once

#include <SFML/Graphics.hpp>

#include "explorer/character.hpp"

namespace explorer {

class Player : public Character
{
public:
    Player();
    ~Player() = default;

    virtual void spawn(sf::Vector2i const& start_pose) override;
    bool try_to_kill();
    int get_lives() const;

private:
    int _lives;
};

}  // namespace explorer
