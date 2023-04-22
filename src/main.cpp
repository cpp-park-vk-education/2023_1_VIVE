#include "Game.hpp"

int main() {
    // Init game
    Game game;

    // Game loop
    while (game.getWindow().isOpen())
    {
        // Update
        game.update();

        // Render
        game.render();
    }

    return 0;
}
