#include <iostream>
#include <fstream>
#include <memory>

#include "explorer/location.hpp"
#include "explorer/spikes.hpp"

namespace explorer {

Location::Location(/* args */)
{
    int index{0};
    _floor_textures.resize(_floor_texture_num);
    for (auto&& texture : _floor_textures) {
        texture.loadFromFile("resources/graphics/tiles/floor/floor_" + std::to_string(++index) + ".png");
    }

    index = 0;
    _wall_textures.resize(_wall_texture_num);
    for (auto&& texture : _wall_textures) {
        texture.loadFromFile("resources/graphics/tiles/wall/wall_" + std::to_string(++index) + ".png");
    }
    _stair_texture.loadFromFile("resources/graphics/tiles/floor/stair_nextlevel.png");

    for (auto&& row : _sprites) {
        for (auto& sprite : row) {
            sprite.scale(_scaling, _scaling);
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
                set_tile(sf::Vector2u{j, i}, _tile_size * _scaling, _layout[i][j]);
            }
        }
        else {
            for (unsigned int j = 0; j < COLS; ++j) {
                if (j % 2 == 0) {
                    file >> raw;
                }
                _layout[i][j] = raw;
                set_tile(sf::Vector2u{j, i}, _tile_size * _scaling, _layout[i][j]);
            }
        }
    }
    set_stairs();
}

void Location::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto&& row : _sprites) {
        for (auto&& sprite : row) {
            target.draw(sprite);
        }
    }
    target.draw(_start_stairs);
    target.draw(_finish_stairs);
    for (auto& object : _scene_objects) {
        object->draw(target, states);
    }
}

void Location::set_tile(sf::Vector2u const& position, int size, int type)
{
    std::shared_ptr<Spikes> s;
    sf::Vector2u p{position.x * size, position.y * size};
    switch (type) {
        case 2:
            std::cout << "added spikes";
            s = std::make_shared<Spikes>(p);
            _scene_objects.push_back(s);
            std::cout << "size " << _scene_objects.size();
            break;
        case 1:
            _sprites[position.y][position.x].setTexture(_floor_textures[rand() % _floor_texture_num]);
            break;

        case 0:
            _sprites[position.y][position.x].setTexture(_wall_textures[rand() % _wall_texture_num]);
            break;

        default:
            break;
    }
    _sprites[position.y][position.x].setPosition(position.x * size, position.y * size);
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

std::array<std::array<unsigned int, COLS>, ROWS> Location::get_layout() const
{
    return _layout;
}

void Location::light_up(sf::FloatRect const& boundary)
{
    _light_boundary.top    = boundary.top - (_tile_size * _scaling) * 4;
    _light_boundary.left   = boundary.left - (_tile_size * _scaling) * 4;
    _light_boundary.width  = (_tile_size * _scaling) * 8;
    _light_boundary.height = (_tile_size * _scaling) * 8;

    for (auto&& row : _sprites) {
        for (auto& sprite : row) {
            if (_light_boundary.intersects(sprite.getGlobalBounds())) {
                sprite.setColor(sf::Color::White);
            }
            else {
                sprite.setColor(sf::Color::Black);
            }
        }
    }
    for (auto& object : _scene_objects) {
        if (_light_boundary.intersects(object->get_boundaries())) {
            object->set_color(sf::Color::White);
        }
        else {
            object->set_color(sf::Color::Black);
        }
    }
}

std::vector<std::shared_ptr<Spikes>> Location::get_scene() const
{
    return _scene_objects;
}

sf::FloatRect Location::get_light_boundary() const
{
    return _light_boundary;
}

}  // namespace explorer
