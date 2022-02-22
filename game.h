#pragma once

typedef struct {
    unsigned char     *field;
    unsigned long long line_size;
    unsigned long long cell_count;
    unsigned char      winner;
    unsigned long long turns_played;
} ttt_game;

int  game_create(ttt_game *game, int argc, const char **argv);
void game_run(ttt_game *game);
void game_reset(ttt_game *game);
void game_shutdown(ttt_game *game);
