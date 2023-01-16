#pragma once

#include <SFML/Graphics.hpp>

namespace explorer {

class Character : public sf::Drawable
{
public:
    Character();
    virtual ~Character(){};

    virtual void spawn(std::string name, sf::Vector2i const& start_pose) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    int get_max_speed() const;
    sf::Vector2f get_current_velocity() const;
    void set_current_velocity(sf::Vector2f updated_velocity);
    sf::Vector2i get_current_acc() const;
    void set_current_acc(sf::Vector2i updated_acc);

    void move(sf::Vector2i direction, int speed = 2);
    std::string get_name();

    sf::FloatRect get_boundaries() const;

protected:
    virtual void set_sprite(sf::Vector2i const& start_pose) = 0;

    float _max_speed;
    sf::Sprite _sprite;
    std::string _name;
    sf::Texture _texture;
    sf::Vector2f _current_velocity;
    sf::Vector2i _current_acc;
};

}  // namespace explorer
