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
}

Location::~Location() {}

void Location::load_level(int const level)
{
    std::string resource_path = "resources/locations/location" + std::to_string(level) + ".txt";

    std::fstream file;

    file.open(resource_path, std::ios_base::in);
    if (!file.is_open())
        throw std::runtime_error("error to open \n");

    file >> _start_pose.x;
    file >> _start_pose.y;

    file >> _finish_pose.x;
    file >> _finish_pose.y;

    // _layout.resize(ROWS);

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

    _layout.size();
    sf::Texture texture;
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
    _sprites[position_y][position_x].scale(_scaling, _scaling);
}

void Location::set_stairs()
{
    _start_stairs.setTexture(_stair_texture);
    _finish_stairs.setTexture(_stair_texture);
    _start_stairs.rotate(180);
    _start_stairs.setOrigin(_stair_texture.getSize().x, _stair_texture.getSize().y);

    _start_stairs.setPosition(_start_pose.x * _tile_size * _scaling * 2, _start_pose.y * _tile_size * _scaling * 2);
    _finish_stairs.setPosition(_finish_pose.x * _tile_size * _scaling * 2, _finish_pose.y * _tile_size * _scaling * 2);

    _start_stairs.scale(_scaling, _scaling);
    _finish_stairs.scale(_scaling, _scaling);
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
    int tile_x = position.x / (_tile_size * _scaling);
    int tile_y = position.y / (_tile_size * _scaling);
    return _layout[tile_y][tile_x];
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
    sf::FloatRect light_bound;
    light_bound.top    = boundary.top - boundary.height * 2;
    light_bound.left   = boundary.left - boundary.width * 2;
    light_bound.width  = boundary.width * 5;
    light_bound.height = boundary.height * 5;

    // auto n = get_tile_number({light_bound.top, light_bound.left});
    // _sprites[n.x][n.y].setColor(sf::Color::Black);
    for (int y = 0; y < _sprites.size(); ++y) {
        for (int x = 0; x < _sprites[0].size(); ++x) {
            if (light_bound.intersects(_sprites[y][x].getGlobalBounds())) {
                _sprites[y][x].setColor(sf::Color::White);
            }
            else {
                _sprites[y][x].setColor(sf::Color::Black);
            }
        }
    }
    // _sprites[n.y][n.x].setColor(sf::Color::Transparent);
}

}  // namespace explorer
