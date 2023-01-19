#include "explorer/enemy.hpp"
namespace explorer {

Enemy::Enemy() {}

void Enemy::spawn(sf::Vector2i const& start_pose)
{
    set_sprite(start_pose);
    _max_speed = 100;
    _max_acc   = 10;
}

void Enemy::set_sprite(sf::Vector2i const& start_pose)
{
    if (!_texture.loadFromFile("resources/graphics/enemies/goblin/goblin_idle_anim_f0.png")) {
        throw std::runtime_error("Failed to load enemy texture");
    };
    _sprite.setTexture(_texture, true);
    _sprite.setScale(2.0, 2.0);
    _sprite.setPosition(start_pose.x * 64, start_pose.y * 64);
}

void Enemy::follow_player(sf::Vector2i const& player_pose)
{

    // array<array<int, 10>, 9> grid{{{{1, 0, 1, 1, 1, 1, 0, 1, 1, 1}},
    //                                {{1, 1, 1, 0, 1, 1, 1, 0, 1, 1}},
    //                                {{1, 1, 1, 0, 1, 1, 0, 1, 0, 1}},
    //                                {{0, 0, 1, 0, 1, 0, 0, 0, 0, 1}},
    //                                {{1, 1, 1, 0, 1, 1, 1, 0, 1, 0}},
    //                                {{1, 0, 1, 1, 1, 1, 0, 1, 0, 0}},
    //                                {{1, 0, 0, 0, 0, 1, 0, 0, 0, 1}},
    //                                {{1, 0, 1, 1, 1, 1, 0, 1, 1, 1}},
    //                                {{1, 1, 1, 0, 0, 0, 1, 0, 0, 1}}}};

    // // Source is the left-most bottom-most corner
    // Pair src(8, 0);

    // // Destination is the left-most top-most corner
    // Pair dest(0, 0);
    // // Vector2i next_move{0, 0};
    // // while (src.first != dest.first && src.first != dest.second) {
    // for (size_t i = 0; i < 5; i++) {
    //     aStarSearch(_layout, src, dest);
    //     // src.first += next_move.first;
    //     // src.second += next_move.second;
    //     cout << "\n currnet " << src.first << " " << src.second;
    // }
}

}  // namespace explorer