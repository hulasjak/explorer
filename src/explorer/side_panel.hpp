#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace explorer {
class SidePanel : public sf::Drawable
{
public:
    SidePanel();
    ~SidePanel() = default;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(int lives, int level);

private:
    sf::Font _font;
    sf::Text _txt;
};

}  // namespace explorer
