#include "game.h"

int main(int argc, const char **argv) {
    ttt_game game;
    if (!game_create(&game, argc, argv)) {
        return -1;
    }
    game_run(&game);
    game_shutdown(&game);
}
