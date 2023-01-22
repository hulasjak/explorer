#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>

namespace explorer {

class Character : public sf::Drawable
{
public:
    Character();
    virtual ~Character(){};

    virtual void spawn(sf::Vector2i const& start_pose) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    int get_max_speed() const;
    int get_max_acc() const;

    sf::Vector2f get_current_velocity() const;
    void set_current_velocity(sf::Vector2f const& updated_velocity);

    void move(sf::Vector2i const& direction);

    sf::FloatRect get_boundaries() const;
    sf::Vector2i get_center() const;

    bool check_contact(sf::FloatRect const& external_boundary) const;
    void animate();

protected:
    virtual void set_sprite(sf::Vector2i const& start_pose) = 0;
    void set_animation(std::string const& base_path, size_t number);

    std::chrono::time_point<std::chrono::system_clock> _last_animation;
    int _animated_texture{0};

    int _max_speed;
    int _max_acc;
    sf::Sprite _sprite;
    std::vector<sf::Texture> _idle_textures;
    std::vector<sf::Texture> _active_textures;

    sf::Vector2f _current_velocity;
    sf::Vector2i _current_acc;

    sf::Vector2i _start_pose;
};

}  // namespace explorer
