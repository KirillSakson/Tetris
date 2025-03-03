#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "utils.h"
#include "pieces.h"

#define MIN_ROWS 10  // minimum nº of rows to play the game
#define MIN_COLUMNS 6  // minimum nº of columns to play the game

typedef struct {
    Piece p;
    int at_row;
    int at_col;
} PieceInfo;

typedef struct {
    int score;
    int rows;
    int columns;
    char **board;  // refactored board
    PieceInfo current_piece;
} GameState;

/// Implemented functions
void print_game_state(GameState *game_state);
void print_options();
bool is_valid_option(int option);
void print_line(int columns);
void print_board(GameState *game_state);
void get_new_random_piece(GameState *game_state);
void block_current_piece(GameState *game_state);
bool is_collision(GameState *game_state);

/**** LAB 1 - functions to program (start here) ****/
void init_game_state(GameState *game_state);
void restart_game_state(GameState *game_state);
void free_game_state(GameState *game_state);  // free dynamically allocated memory
bool is_terminal(GameState *game_state); // True if contains X values in TOP-4 rows
void move(GameState *game_state, int option);
void rotate(GameState *game_state, int option);
/**** LAB 1 - functions to program (end here) ****/

/// Implemented functions
void run_turn(GameState *game_state, int option);

#endif
