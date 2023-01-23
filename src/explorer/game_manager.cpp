#include <iostream>

#include <explorer/game_manager.hpp>

using namespace std::chrono_literals;

namespace explorer {
GameManager::GameManager(/* args */)
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1700, 1000),
                                                 "explorer",
                                                 sf::Style::Close | sf::Style::Titlebar);
    _window->setFramerateLimit(30);
    _current_location = std::make_shared<Location>();
    _player           = std::make_shared<Player>();
    _goblin           = std::make_shared<Enemy>();
    _panel            = std::make_shared<SidePanel>();
    new_turn();
}

void GameManager::poll_events()
{
    sf::Event ev;
    while (_window->pollEvent(ev)) {
        switch (ev.type) {
            case sf::Event::Closed:
                _window->close();
                _game_running = false;
                break;

            default:
                break;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        _command_move.y += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        _command_move.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _command_move.x += -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _command_move.x += 1;
    }
}

void GameManager::update()
{
    poll_events();

    _physics.update(_command_move, _player);
    _command_move.x = 0;
    _command_move.y = 0;

    _current_location->light_up(_player->get_boundaries());
    _panel->update(_player->get_lives(), _current_level);

    // TODO clean up the game logic, move _spawned to class
    if (_enemy_spawed) {
        auto gb        = _current_location->get_tile_number(_goblin->get_center());
        auto pl        = _current_location->get_tile_number(_player->get_center());
        auto next_move = _astar->aStarSearch(gb, pl);
        _physics.update(next_move, _goblin);
        _goblin->light_up(_current_location->get_light_boundary());
        if (_player->check_contact(_goblin->get_kill_boundaries())) {
            _goblin->spawn(
                sf::Vector2i{_current_location->get_start_position().x, _current_location->get_start_position().y});
            _start_time   = std::chrono::system_clock::now();
            _enemy_spawed = false;

            if (!_player->try_to_kill()) {
                _window->close();
                _game_running = false;
            }
        }
    }

    if (_current_location->is_on_finish(_player->get_boundaries())) {
        new_turn();
    }

    // give head start
    if (!_enemy_spawed && std::chrono::system_clock::now() - _start_time > 5s) {
        _goblin->spawn(
            sf::Vector2i{_current_location->get_start_position().x, _current_location->get_start_position().y});
        _enemy_spawed = true;
    }
}

void GameManager::new_turn()
{
    _current_location->load_level(_current_level);
    _player->spawn(_current_location->get_start_position());

    _physics.init(_current_location);
    _astar        = make_shared<AStar<ROWS, COLS>>(_current_location->get_layout());
    _start_time   = std::chrono::system_clock::now();
    _enemy_spawed = false;

    _current_level++;
}

void GameManager::render()
{
    _window->clear();
    _window->draw(*_current_location.get());
    _window->draw(*_player.get());
    _window->draw(*_goblin.get());
    _window->draw(*_panel.get());

    _window->display();
}

bool GameManager::is_running() const
{
    return _game_running;
}

}  // namespace explorer