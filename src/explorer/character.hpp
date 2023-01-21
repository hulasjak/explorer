#pragma once

#include <SFML/Graphics.hpp>

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

protected:
    virtual void set_sprite(sf::Vector2i const& start_pose) = 0;

    int _max_speed;
    int _max_acc;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Vector2f _current_velocity;
    sf::Vector2i _current_acc;
};

}  // namespace explorer
