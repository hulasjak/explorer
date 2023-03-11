#pragma once

#include "explorer/physical_object.hpp"
#include <chrono>

namespace explorer {

class Spikes : public PhysicalObject
{
public:
    Spikes(sf::Vector2u const& spawn_pose);
    ~Spikes();
    operator sf::Sprite() { return _sprite; }

    void update_spikes_state();
    bool is_active();
    void set_color(sf::Color const& color);

    void animate();
    bool check_contact(sf::FloatRect const& external_boundary) const override;

private:
    bool _active{false};
    std::vector<sf::Texture> _active_textures;
    std::vector<sf::Texture> _idle_textures;
    std::chrono::time_point<std::chrono::system_clock> _last_state_change;
};

}  // namespace explorer
