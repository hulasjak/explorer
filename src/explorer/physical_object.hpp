#pragma once

#include <SFML/Graphics.hpp>

namespace explorer {

class PhysicalObject : public sf::Drawable
{
public:
    PhysicalObject(/* args */);
    virtual ~PhysicalObject();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect get_boundaries() const;
    sf::Vector2i get_center() const;

    virtual bool check_contact(sf::FloatRect const& external_boundary) const;

protected:
    void set_animation(std::string const& base_path, std::vector<sf::Texture>& textures);
    /* data */
    sf::Sprite _sprite;
};

}  // namespace explorer