#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char symbols[3] = {'-', 'X', 'O'};

enum patterns {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_TD,
    DIAGONAL_BU,
    MAX_PATTERN
};

unsigned char game_get_field_value(ttt_game *game, unsigned long long x, unsigned long long y);
void          game_set_field_value(ttt_game *game, unsigned long long x, unsigned long long y, unsigned char value);

void render_field(ttt_game *game);
void render_field_line(unsigned char *field_line, unsigned long long line_size);
void render_field_separator(unsigned long long line_size);

unsigned long long get_coordinate_input(const char *name, unsigned long long limit);

int check_win(ttt_game *game);

int game_create(ttt_game *game, int argc, const char **argv) {
    // defaults
    game->line_size = 3;

    // overwriting defaults
    for (int i = 1; i + 1 < argc; i += 2) {
        const char *flag  = argv[i];
        const char *value = argv[i + 1];
        switch (*flag) {
            case 's':
                game->line_size = strtoll(value, NULL, 10);
                break;
        }
    }
    game->cell_count = game->line_size * game->line_size;
    if (game->cell_count)
        game->field = malloc(sizeof(unsigned char) * game->cell_count);
    else
        game->field = NULL;
    game_reset(game);
    return 1;
}

unsigned char game_get_field_value(ttt_game *game, unsigned long long x, unsigned long long y) {
    return (game->field + y * game->line_size)[x];
}

void game_set_field_value(ttt_game *game, unsigned long long x, unsigned long long y, unsigned char value) {
    (game->field + y * game->line_size)[x] = value;
}

void game_run(ttt_game *game) {
    unsigned char cur_player = 1;
    while (game->turns_played < game->cell_count) {
        printf("%c's turn:\n", symbols[cur_player]);
        render_field(game);
        int r = get_coordinate_input("row", game->line_size);
        int c = get_coordinate_input("column", game->line_size);
        if (game_get_field_value(game, c, r)) {
            printf("you cannot overwrite this tile\n");
            continue;
        }
        game_set_field_value(game, c, r, cur_player);
        if (check_win(game)) {
            printf("player %c won the game\n", symbols[cur_player]);
            game->winner = cur_player;
            break;
        }
        cur_player ^= 3;
        ++game->turns_played;
    }
    printf("final board state:\n");
    render_field(game);
}

void game_reset(ttt_game *game) {
    game->winner       = 0;
    game->turns_played = 0;
    if (game->field)
        memset(game->field, 0, game->cell_count);
}

void game_shutdown(ttt_game *game) {
    if (game->field)
        free(game->field);
}

void render_field(ttt_game *game) {
    for (int i = 0; i < game->line_size; ++i) {
        render_field_separator(game->line_size);
        render_field_line(game->field + i * game->line_size, game->line_size);
    }
    render_field_separator(game->line_size);
}

void render_field_line(unsigned char *field_line, unsigned long long line_size) {
    for (int j = 0; j < line_size; ++j) {
        printf("|%c", symbols[field_line[j]]);
    }
    printf("|\n");
}

void render_field_separator(unsigned long long line_size) {
    for (int j = 0; j < line_size; ++j) {
        printf("--");
    }
    printf("-\n");
}

unsigned long long get_coordinate_input(const char *name, unsigned long long limit) {
    unsigned long long ret = limit;
    while (ret >= limit) {
        printf("please input a %s:\n", name);
        scanf("%lld", &ret);
    }
    return ret;
}

int check_win(ttt_game *game) {
    int matches[MAX_PATTERN + 1];
    matches[MAX_PATTERN] = 0;
    for (int i = 0; i < game->line_size; ++i) {
        matches[HORIZONTAL]  = game_get_field_value(game, 0, i);
        matches[VERTICAL]    = game_get_field_value(game, i, 0);
        matches[DIAGONAL_TD] = game_get_field_value(game, 0, 0);
        matches[DIAGONAL_BU] = game_get_field_value(game, 0, game->line_size - 1);
        for (int j = 1; j < game->line_size; ++j) {
            matches[HORIZONTAL] &= game_get_field_value(game, 0, i) == game_get_field_value(game, j, i);
            matches[VERTICAL] &= game_get_field_value(game, i, 0) == game_get_field_value(game, i, j);
            matches[DIAGONAL_TD] &= game_get_field_value(game, 0, 0) == game_get_field_value(game, j, j);
            matches[DIAGONAL_BU] &= game_get_field_value(game, 0, game->line_size - 1)
                                 == game_get_field_value(game, j, game->line_size - j - 1);
        }
        for (int i = 0; i < MAX_PATTERN; ++i) {
            matches[MAX_PATTERN] |= matches[i];
        }
    }
    return matches[MAX_PATTERN];
}
