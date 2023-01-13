#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace explorer {

class Location : public sf::Drawable
{
    enum TILE_TYPE { WALL, FLOOR, END };

public:
    Location(/* args */);
    ~Location();

    void load_level(int const level);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    auto get_start_position() const -> sf::Vector2i;
    auto get_finish_position() const -> sf::Vector2i;

    bool is_position_free(sf::Vector2i const& position) const;
    bool is_on_finish(sf::FloatRect const& position) const;

private:
    void set_tile(int position_x, int position_y, int size, TILE_TYPE type);
    void set_stairs();

    std::vector<sf::Texture> _floor_textures;
    std::vector<sf::Texture> _wall_textures;
    sf::Texture _stair_texture;

    int _size_x;
    int _size_y;

    static constexpr float _scaling{2.0};
    static constexpr int _tile_size{16};

    sf::Vector2i _start_pose;
    sf::Vector2i _finish_pose;

    sf::Font font;

    std::vector<std::vector<TILE_TYPE> > _layout;
    std::vector<std::vector<sf::Sprite> > _sprites;
    sf::Sprite _start_stairs;
    sf::Sprite _finish_stairs;
};

}  // namespace explorer