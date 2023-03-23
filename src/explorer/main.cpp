#include <explorer/game_manager.hpp>
#include <signal.h>
#include <atomic>

std::atomic_bool keep_running{true};

void signal_handler(int s)
{
    keep_running = false;
}

int main()
{
    auto game = explorer::GameManager();

    signal(SIGINT, signal_handler);

    while (game.is_running() && keep_running) {
        game.update();
        game.render();
    }

    return 0;
}
