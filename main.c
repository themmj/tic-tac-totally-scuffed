#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int field_size = 3;
const char symbols[3] = { '-', 'X', 'O' }; 

void render_field_line(char field_line[field_size]) {
    for (int j = 0; j < field_size; ++j) {
        printf("|%c", symbols[field_line[j]]);
    }
    printf("|\n");
}

void render_field_separator(){
    for (int j = 0; j < field_size; ++j) {
        printf("--");
    }
    printf("-\n");
}

void render_field(char field[field_size][field_size]) {
    for (int i = 0; i < field_size; ++i) {
        render_field_separator();
        render_field_line(field[i]);
    }
    render_field_separator();
}

int get_coordinate_input(const char *name) {
    int ret = field_size;
    while (ret >= field_size) {
        printf("please input a %s:\n", name);
        scanf("%d", &ret);
    }
    return ret;
}

enum patterns {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_TD,
    DIAGONAL_BU,
    MAX_PATTERN
};

int check_win(char field[field_size][field_size]) {
    int matches[MAX_PATTERN + 1];
    matches[MAX_PATTERN] = 0;
    for (int i = 0; i < field_size; ++i) {
        matches[HORIZONTAL] = field[i][0];
        matches[VERTICAL] = field[0][i];
        matches[DIAGONAL_TD] = field[0][0];
        matches[DIAGONAL_BU] = field[field_size - 1][0];
        for (int j = 1; j < field_size; ++j) {
            matches[HORIZONTAL] &= field[i][0] == field[i][j];
            matches[VERTICAL] &= field[0][i] == field[j][i];
            matches[DIAGONAL_TD] &= field[0][0] == field[j][j];
            matches[DIAGONAL_BU] &= field[field_size - 1][0] == field[field_size - j - 1][j];
        }
        matches[MAX_PATTERN] |= matches[HORIZONTAL];
        matches[MAX_PATTERN] |= matches[VERTICAL];
        matches[MAX_PATTERN] |= matches[DIAGONAL_TD];
        matches[MAX_PATTERN] |= matches[DIAGONAL_BU];
    }
    return matches[MAX_PATTERN];
}

int main(int argc, char **argv) {
    char field[field_size][field_size];
    memset(field, 0, sizeof(field));
    int cur_player = 1;
    int max_turns = field_size * field_size;
    int cur_turn = 0;

    while (cur_turn < max_turns) {
        printf("%c's turn:\n", symbols[cur_player]);
        render_field(field);
        int r = get_coordinate_input("row");
        int c = get_coordinate_input("column");
        if (field[r][c]) {
            printf("you cannot overwrite this tile\n");
            continue;
        }
        field[r][c] = cur_player;
        if (check_win(field)) {
            printf("player %c won the game\n", symbols[cur_player]);
            break;
        }
        cur_player ^= 3;
        ++cur_turn;
    }
    printf("final board state:\n");
    render_field(field);
}

