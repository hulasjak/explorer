#include <iostream>
#include <fstream>

#include "explorer/location.hpp"

namespace explorer {

Location::Location(/* args */)
{
    _floor_textures.resize(9);
    for (size_t i = 0; i < 9; i++) {
        _floor_textures[i].loadFromFile("resources/graphics/tiles/floor/floor_" + std::to_string(i + 1) + ".png");
    }
    _wall_textures.resize(2);
    for (size_t i = 0; i < 2; i++) {
        _wall_textures[i].loadFromFile("resources/graphics/tiles/wall/wall_" + std::to_string(i + 1) + ".png");
    }
    _stair_texture.loadFromFile("resources/graphics/tiles/floor/stair_nextlevel.png");

    for (int y = 0; y < _sprites.size(); ++y) {
        for (int x = 0; x < _sprites[0].size(); ++x) {
            _sprites[y][x].scale(_scaling, _scaling);
        }
    }
    _start_stairs.scale(_scaling, _scaling);
    _finish_stairs.scale(_scaling, _scaling);
}

Location::~Location() {}

void Location::load_level(int const level)
{
    std::string resource_path = "resources/locations/location" + std::to_string(level) + ".txt";

    std::fstream file;

    file.open(resource_path, std::ios_base::in);
    if (!file.is_open())
        throw std::runtime_error("error to open location file \n");

    file >> _start_pose.x;
    file >> _start_pose.y;

    file >> _finish_pose.x;
    file >> _finish_pose.y;

    int raw;
    // find better way to scale the map
    for (unsigned int i = 0; i < ROWS; ++i) {
        if (i % 2 != 0) {
            _layout[i] = _layout[i - 1];
            for (unsigned int j = 0; j < COLS; ++j) {
                set_tile(j, i, _tile_size * _scaling, _layout[i][j]);
            }
        }
        else {
            for (unsigned int j = 0; j < COLS; ++j) {
                if (j % 2 == 0) {
                    file >> raw;
                }
                _layout[i][j] = raw;
                set_tile(j, i, _tile_size * _scaling, _layout[i][j]);
            }
        }
    }
    set_stairs();
}

void Location::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int y = 0; y < _sprites.size(); ++y) {
        for (int x = 0; x < _sprites[0].size(); ++x) {
            target.draw(_sprites[y][x]);
        }
    }
    target.draw(_start_stairs);
    target.draw(_finish_stairs);
}

void Location::set_tile(int position_x, int position_y, int size, int type)
{
    switch (type) {
        case 1:
            _sprites[position_y][position_x].setTexture(_floor_textures[rand() % 8]);
            break;

        case 0:
            _sprites[position_y][position_x].setTexture(_wall_textures[rand() % 2]);
            break;

        default:
            break;
    };
    _sprites[position_y][position_x].setPosition(position_x * size, position_y * size);
}

void Location::set_stairs()
{
    _start_stairs.setTexture(_stair_texture);
    _finish_stairs.setTexture(_stair_texture);
    _start_stairs.rotate(180);
    _start_stairs.setOrigin(_stair_texture.getSize().x, _stair_texture.getSize().y);

    _start_stairs.setPosition(_start_pose.x * _tile_size * _scaling * 2, _start_pose.y * _tile_size * _scaling * 2);
    _finish_stairs.setPosition(_finish_pose.x * _tile_size * _scaling * 2, _finish_pose.y * _tile_size * _scaling * 2);
}

auto Location::get_start_position() const -> sf::Vector2i
{
    return _start_pose;
}

auto Location::get_finish_position() const -> sf::Vector2i
{
    return _finish_pose;
}

bool Location::is_position_free(sf::Vector2i const& position) const
{
    auto n = get_tile_number(position);
    return _layout[n.y][n.x];
}

sf::Vector2i Location::get_tile_number(sf::Vector2i const& position) const
{
    sf::Vector2i n;
    n.x = position.x / (_tile_size * _scaling);
    n.y = position.y / (_tile_size * _scaling);
    return n;
}

bool Location::is_on_finish(sf::FloatRect const& position) const
{
    return _finish_stairs.getGlobalBounds().intersects(position);
}

std::array<std::array<int, COLS>, ROWS> Location::get_layout() const
{
    return _layout;
}

void Location::light_up(sf::FloatRect const& boundary)
{
    _light_boundary.top    = boundary.top - (_tile_size * _scaling) * 4;
    _light_boundary.left   = boundary.left - (_tile_size * _scaling) * 4;
    _light_boundary.width  = (_tile_size * _scaling) * 8;
    _light_boundary.height = (_tile_size * _scaling) * 8;

    for (int y = 0; y < _sprites.size(); ++y) {
        for (int x = 0; x < _sprites[0].size(); ++x) {
            if (_light_boundary.intersects(_sprites[y][x].getGlobalBounds())) {
                _sprites[y][x].setColor(sf::Color::White);
            }
            else {
                _sprites[y][x].setColor(sf::Color::Black);
            }
        }
    }
}

sf::FloatRect Location::get_light_boundary() const
{
    return _light_boundary;
}

}  // namespace explorer
