#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <list>

#include "explorer/physical_object.hpp"
#include "explorer/spikes.hpp"
#include "explorer/scene_objects.hpp"

#define ROWS 30
#define COLS 42

namespace explorer {

class Location : public sf::Drawable
{
public:
    Location(/* args */);
    ~Location();

    void load_level(int level);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2i get_start_position() const;
    sf::Vector2i get_finish_position() const;

    bool is_position_free(sf::Vector2i const& position) const;
    bool is_on_finish(sf::FloatRect const& position) const;

    std::array<std::array<unsigned int, COLS>, ROWS> get_layout() const;
    sf::Vector2i get_tile_number(sf::Vector2i const& position) const;

    void light_up(sf::FloatRect const& boundary);
    sf::FloatRect get_light_boundary() const;
    void boost_light();

    std::list<std::shared_ptr<Spikes>> get_spikes() const;
    std::list<std::shared_ptr<Torch>> get_torches() const;
    std::list<std::shared_ptr<Health>> get_health() const;

    void remove_object(std::shared_ptr<Torch> const& torch);
    void remove_object(std::shared_ptr<Health> const& health);

private:
    void set_tile(sf::Vector2u const& position, int size, int type);
    void set_stairs();

    std::vector<sf::Texture> _floor_textures;
    std::vector<sf::Texture> _wall_textures;
    sf::Texture _stair_texture;

    static constexpr float _scaling{2.0};
    static constexpr int _tile_size{16};
    static constexpr int _floor_texture_num{9};
    static constexpr int _wall_texture_num{2};

    sf::Vector2i _start_pose;
    sf::Vector2i _finish_pose;

    std::array<std::array<unsigned int, COLS>, ROWS> _layout;
    std::array<std::array<sf::Sprite, COLS>, ROWS> _sprites;
    std::list<std::shared_ptr<Spikes>> _spikes;
    std::list<std::shared_ptr<Health>> _healths;
    std::list<std::shared_ptr<Torch>> _torches;

    sf::Sprite _start_stairs;
    sf::Sprite _finish_stairs;
    sf::FloatRect _light_boundary;

    int _light_scaling{4};
};

}  // namespace explorer