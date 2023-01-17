#include <iostream>

#include <explorer/game_manager.hpp>

namespace explorer {
GameManager::GameManager(/* args */)
{
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1600, 1000),
                                                 "explorer",
                                                 sf::Style::Close | sf::Style::Titlebar);
    _window->setFramerateLimit(30);
    _current_location = std::make_shared<Location>();
    _player           = std::make_shared<Player>();
    _goblin           = std::make_shared<Enemy>();

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

    if (_current_location->is_on_finish(_player->get_boundaries())) {
        new_turn();
    }
}

void GameManager::new_turn()
{
    _current_location->load_level(_current_level);
    _player->spawn(_current_location->get_start_position());
    _goblin->spawn(_current_location->get_start_position());
    _physics.init(_current_location);
    _current_level++;
}

void GameManager::render()
{
    _window->draw(*_current_location.get());
    _window->draw(*_player.get());
    _window->draw(*_goblin.get());

    _window->display();
}

bool GameManager::is_running() const
{
    return _game_running;
}

}  // namespace explorer