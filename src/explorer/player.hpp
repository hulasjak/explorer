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
    bool get_win() const;
    void set_win(bool state);
    bool try_to_kill();

private:
    void set_sprite(sf::Vector2i const& start_pose) override;
    bool _won{false};
    int _lives;
};

}  // namespace explorer
