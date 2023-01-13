#include <explorer/game_manager.hpp>
#include <explorer/location.hpp>

int main()
{
    auto game = explorer::GameManager();

    while (game.is_running()) {
        game.update();
        game.render();
    }

    return 0;
}
