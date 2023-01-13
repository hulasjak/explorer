#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "explorer/location.hpp"
#include "explorer/player.hpp"
#include "explorer/character.hpp"
#include "explorer/physics_engine.hpp"
#include "explorer/enemy.hpp"

namespace explorer {
class GameManager
{
public:
    GameManager(/* args */);
    ~GameManager() = default;

    void update();
    void render();

    void poll_events();

    bool is_running() const;

private:
    void new_turn();

    std::shared_ptr<Location> _current_location;
    std::shared_ptr<Player> _player;
    // std::vector<Character> _enemies;
    std::shared_ptr<Enemy> _goblin;
    PhysicsEngine _physics;

    sf::Event _event;
    sf::Vector2<int> _command_move;

    bool _game_running{true};
    int _current_level{0};
    std::shared_ptr<sf::RenderWindow> _window;
};

}  // namespace explorer