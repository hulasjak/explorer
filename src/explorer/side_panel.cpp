#include "explorer/side_panel.hpp"
namespace explorer {

SidePanel::SidePanel()
{
    _font.loadFromFile("resources/Growland.otf");
    _txt.setFont(_font);
    _txt.setCharacterSize(30);
    _txt.setPosition(1450, 30);
    _txt.setFillColor(sf::Color{128, 64, 0});
}

void SidePanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_txt);
}

void SidePanel::update(int lives, int level)
{
    _txt.setString(
        std::string(" EXPLORER \n\n LEVEL: " + std::to_string(level) + " \n LIVES: " + std::to_string(lives)));
}

}  // namespace explorer