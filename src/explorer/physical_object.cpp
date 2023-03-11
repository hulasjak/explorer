#include "explorer/physical_object.hpp"

namespace explorer {

PhysicalObject::PhysicalObject(/* args */) {}

PhysicalObject::~PhysicalObject() {}

void PhysicalObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite);
}

void PhysicalObject::set_animation(std::string const& base_path, std::vector<sf::Texture>& textures)
{
    if (textures.size() == 0) {
        return;
    }

    unsigned int i = 0;
    for (auto& texture : textures) {
        if (!texture.loadFromFile(base_path + std::to_string(i) + ".png")) {
            throw std::runtime_error("Failed to load texture: " + base_path);
        }
        i++;
    }
}

bool PhysicalObject::check_contact(sf::FloatRect const& external_boundary) const
{
    return _sprite.getGlobalBounds().intersects(external_boundary);
}

sf::FloatRect PhysicalObject::get_boundaries() const
{
    auto bound = _sprite.getGlobalBounds();
    bound.left += 10;
    bound.top += 10;
    bound.width -= 20;
    bound.height -= 20;
    return bound;
}

sf::Vector2i PhysicalObject::get_center() const
{
    sf::Vector2i center;
    center.x = get_boundaries().left + get_boundaries().width / 2;
    center.y = get_boundaries().top + get_boundaries().height / 2;
    return center;
}

}  // namespace explorer