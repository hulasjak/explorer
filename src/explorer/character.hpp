#pragma once

#include <SFML/Graphics.hpp>
#include <explorer/physical_object.hpp>
#include <chrono>

namespace explorer {

class Character : public PhysicalObject
{
public:
    Character();
    virtual ~Character(){};

    virtual void spawn(sf::Vector2i const& start_pose) = 0;

    int get_max_speed() const;
    int get_max_acc() const;

    sf::Vector2f get_current_velocity() const;
    void set_current_velocity(sf::Vector2f const& updated_velocity);

    void move(sf::Vector2i const& direction);

    void animate();

protected:
    std::chrono::time_point<std::chrono::system_clock> _last_animation;
    int _animated_texture{0};

    int _max_speed;
    int _max_acc;
    std::vector<sf::Texture> _idle_textures;
    std::vector<sf::Texture> _active_textures;

    sf::Vector2f _current_velocity;
    sf::Vector2i _current_acc;

    sf::Vector2i _start_pose;
};

}  // namespace explorer
