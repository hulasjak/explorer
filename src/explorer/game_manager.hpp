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
#include "explorer/a_star_impl.hpp"
#include "explorer/side_panel.hpp"

namespace explorer {
class GameManager
{
public:
    GameManager(/* args */);
    ~GameManager() = default;

    // main game logic loop
    void update();

    // main rendering loop
    void render();

    // check if the game is still running
    bool is_running() const;

private:
    // read events
    void poll_events();

    // prepare a new level
    void new_turn();

    void kill_player();

    std::shared_ptr<Location> _current_location;
    std::shared_ptr<Player> _player;
    std::shared_ptr<Enemy> _goblin;
    std::shared_ptr<SidePanel> _panel;

    std::shared_ptr<AStar<ROWS, COLS>> _astar;
    std::shared_ptr<PhysicsEngine> _physics;

    sf::Event _event;
    sf::Vector2<int> _command_move;
    std::chrono::time_point<std::chrono::system_clock> _start_time;

    bool _game_running{true};
    int _current_level{0};
    std::shared_ptr<sf::RenderWindow> _window;
};

}  // namespace explorer