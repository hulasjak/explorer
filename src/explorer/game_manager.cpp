#include <iostream>

#include <explorer/game_manager.hpp>

namespace explorer {
GameManager::GameManager(/* args */)
{
    // _current_location = std::make_shared<Location>();
    _window           = std::make_shared<sf::RenderWindow>(sf::VideoMode(1600, 1000),
                                                 "explorer",
                                                 sf::Style::Close | sf::Style::Titlebar);
    _current_location = std::make_shared<Location>();
    _player           = std::make_shared<Player>();
    _goblin           = std::make_shared<Enemy>();

    _current_location->load_level(_current_level);
    _player->spawn("bobo", _current_location->get_start_position());
    _goblin->spawn("goblin", _current_location->get_start_position());
    _physics.init(_current_location);
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

            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Up) {
                    _command_move.y += -1;
                }
                if (ev.key.code == sf::Keyboard::Down) {
                    _command_move.y += 1;
                }
                if (ev.key.code == sf::Keyboard::Left) {
                    _command_move.x += -1;
                }
                if (ev.key.code == sf::Keyboard::Right) {

                    _command_move.x += 1;
                }
                break;

            default:
                break;
        }
    }
}

void GameManager::update()
{
    poll_events();
    if (_command_move.x || _command_move.y) {
        _physics.try_moving(_command_move, _player);
        _command_move.x = 0;
        _command_move.y = 0;
    }
    if (_current_location->is_on_finish(_player->get_boundaries())) {
        new_turn();
    }
}

void GameManager::new_turn()
{
    _current_location->load_level(++_current_level);
    _player->spawn("ba", _current_location->get_start_position());
}

void GameManager::render()
{
    // for (size_t i = 0; i < _players.size(); i++) {
    //     _ui.update_players(prepare_players(i).str(), i == _active_player, i);
    // }
    _window->draw(*_current_location.get());
    _window->draw(*_player.get());
    // for (auto&& enemy : _enemies) {
    _window->draw(*_goblin.get());
    // }

    // _ui.update_used_letters(_word.get_used_letters());
    _window->display();
    // _ui.render();
}

bool GameManager::is_running() const
{
    return _game_running;
}

}  // namespace explorer