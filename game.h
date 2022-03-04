#pragma once

/// Represents a single game of tic tac toe
typedef struct {
    /**
     * \brief Storage for the playable area.
     *
     * - one dimensional array where rows are stored one after the other
     * - a single element represents a single cell in the field
     *
     * Example:
     * field = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }
     * would represent the following field;
     * 1 2 3
     * 4 5 6
     * 7 8 9
     *
     * To get element "8" which is in the third row and second column:
     * (field + 2 * line_size)[1]
     *
     * A cell's value of 0 means there is no player symbol on it.
     * A value of 1 or 2 indicates which player has placed a symbol in
     * the cell.
     */
    unsigned char     *field;
    /// The number of cells in a row/column.
    unsigned long long line_size;
    /// The overall cell count (size of field).
    unsigned long long cell_count;
    /// Which player won the round.
    unsigned char      winner;
    /// How many turns have been played until now.
    unsigned long long turns_played;
} ttt_game;

/**
 * \brief Create game based on program arguments.
 *
 * \param game the ttt_game instance to initialize
 * \param argc the number of arguments passed to the program (size of argv)
 * \param argv array of provided arguments as const char*
 * \returns 1 iff the game was created successfully, 0 otherwise
 */
int  game_create(ttt_game *game, int argc, const char **argv);

/**
 * \brief Run the game until either one player wins or no cells are left.
 *
 * After this function game->winner may be populated and game->turns_played
 * indicates how many turns were played.
 *
 * \param game the ttt_game instance to run
 */
void game_run(ttt_game *game);

/**
 * \brief Reset game state.
 *
 * Will reset aspects like played turns, the winner etc, clear the field, etc.
 *
 * \param game the ttt_game instance to reset
 */
void game_reset(ttt_game *game);

/**
 * \brief Properly cleanup the game state.
 *
 * Will free the playing field.
 *
 * \param game the ttt_game instance to shutdown
 */
void game_shutdown(ttt_game *game);
