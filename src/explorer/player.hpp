#pragma once

#include <SFML/Graphics.hpp>

#include "explorer/character.hpp"

namespace explorer {

class Player : public Character
{
public:
    Player();
    ~Player() = default;

    virtual void spawn(std::string name, sf::Vector2i const& start_pose) override;
    bool get_win() const;
    void set_win(bool state);

private:
    void set_sprite(sf::Vector2i const& start_pose) override;
    bool _won{false};
};

}  // namespace explorer
