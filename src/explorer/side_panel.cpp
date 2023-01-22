#include "explorer/side_panel.hpp"
namespace explorer {

SidePanel::SidePanel()
{
    _font.loadFromFile("resources/Growland.otf");
    _level_txt.setFont(_font);
    _level_txt.setCharacterSize(25);
    _level_txt.setPosition(1500, 50);
    _level_txt.setFillColor(sf::Color::White);
    _lives_txt.setFont(_font);
    _lives_txt.setCharacterSize(25);
    _lives_txt.setPosition(1500, 200);
    _lives_txt.setFillColor(sf::Color::White);
}

void SidePanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_level_txt);
    target.draw(_lives_txt);
}

void SidePanel::update(int lives, int level)
{
    _level_txt.setString("LEVEL: " + level);
    _lives_txt.setString("LIVES: " + lives);
}

}  // namespace explorer