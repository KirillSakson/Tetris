#include "game.h"

/**** LAB 1 - given functions ****/
void print_game_state(GameState *gs){
    printf("*** Game State ***\n");
    printf("Score=%d\n", gs->score);
    print_board(gs);
}

void print_options(){
    printf("Options:\n");
    printf("\t%d. Move left\n", MOVE_LEFT);
    printf("\t%d. Move right\n", MOVE_RIGHT);
    printf("\t%d. Rotate clockwise\n", ROTATE_CW);
    printf("\t%d. Rotate counter clockwise\n", ROTATE_CCW);
    printf("\t%d. None\n", NONE);
    printf("\t%d. Show best move\n", SHOW_BEST_MOVE);
    printf("\t%d. Quit game\n", QUIT_GAME);
}

bool is_valid_option(int option){
    return ((MOVE_LEFT <= option) && (option<=QUIT_GAME));
}


void print_line(int columns){
    for(int c=-1; c<columns+1; ++c) 
    	printf("-");    
    printf("\n");
}

void print_board(GameState *game_state){
    Piece *piece = &game_state->current_piece.p;
    int p_row_size = piece->rows;
    int p_col_size = piece->cols;
    int current_row = game_state->current_piece.at_row;
    int current_col = game_state->current_piece.at_col;
    print_line();
    for(int r = 0; r < MAX_ROWS; ++r){
        if(r == 4) print_line();
        printf("|");
        for(int c=0; c < MAX_COLUMNS; ++c){
            if((game_state->board[r][c] == '.') &&
               (current_row <= r) && (r < current_row + p_row_size) && 
               (current_col <= c) && (c < current_col + p_col_size)){
                printf("%c", piece->board[r-current_row][c-current_col]);
            }
            else printf("%c", game_state->board[r][c]);
        }
        printf("|\n");
    }
    print_line();
    printf("\n");
}

void get_new_random_piece(GameState *game_state){
    // Random piece
    switch (rand()%MAX_NUM_PIECES){
    case 0:
        game_state->current_piece.p = make_I();
        break;    
    case 1:
        game_state->current_piece.p = make_J();
        break;
    case 2:
        game_state->current_piece.p = make_L();
        break;
    case 3:
        game_state->current_piece.p = make_O();
        break;
    case 4:
        game_state->current_piece.p = make_S();
        break;
    case 5:
        game_state->current_piece.p = make_T();
        break;
    case 6:
        game_state->current_piece.p = make_Z();
        break;
    default:
        break;
    }

    // Random orientation
    int rotations = rand()%3;
    for(int r = 0; r < rotations; ++r)
        rotate_clockwise(&(game_state->current_piece.p));

    // Random location
    game_state->current_piece.at_row = 4 - game_state->current_piece.p.rows;
    game_state->current_piece.at_col = rand() % (MAX_COLUMNS + 1 - game_state->current_piece.p.cols);
}

void block_current_piece(GameState *game_state){
    Piece *piece = &game_state->current_piece.p;
    int row = game_state->current_piece.at_row;
    int col = game_state->current_piece.at_col;
    for(int i=0; i<piece->rows; ++i)
        for(int j=0; j<piece->cols; ++j)
            if(piece->board[i][j] == '#')
                game_state->board[row+i][col+j] = 'X';
}

bool is_collision(GameState *game_state){
    PieceInfo *piece_info = &(game_state->current_piece);
    Piece *piece = &piece_info->p;
    int p_row_size = piece->rows;
    int p_col_size = piece->cols;
    int row = piece_info->at_row;
    int col = piece_info->at_col;

    if((row < 0) || (col < 0) || (row+p_row_size-1 >= game_state->rows) || (col+p_col_size-1 >= game_state->columns)){
    	return true; // piece is out of the grid bounds
    }
    
    for(int i=0; i<piece->rows; ++i)
        for(int j=0; j<piece->cols; ++j)
            if((piece->board[i][j] == '#') && (game_state->board[row+i][col+j] == 'X'))
            	return true; // piece collides with another structure in the board
    
    return false;
}

void make_board(GameState *game_state) {
    // Allocate/Reallocate a board, assuming the rows and cols are already given
    if(game_state->board == NULL) {
        game_state->board = (char**) malloc(sizeof(char*) * game_state->rows);
        // saving memory in heap for the pointers that point to each row
        for (int r=0; r<game_state->rows; ++r) {
            game_state->board[r] = (char *) malloc(sizeof(char) * game_state->columns);
            // saving memory in heap for the pointers that point to each element in each column
            // these pointers are pointed by the pointers of the rows (that point to the rows)
        }
    }
    else {
        game_state->board = (char**) realloc(game_state->board, sizeof(char*) * game_state->rows);
        for (int r=0; r<game_state->rows; ++r) {
            game_state->board[r] = (char*) malloc(sizeof(char) * game_state->columns);
        }
    }
}

void free_game_state(GameState *game_state) {
    if(game_state->board != NULL) {
        for (int r=0; r<game_state->rows; ++r) {
            free(game_state->board[r]); // free all columns
        }
        free(game_state->board);    // free all rows
    }
}

void set_default_game_state(GameState *game_state) {
    // set the score, initialize the board to '.', and get a new random piece
    game_state->score = 0;
    // check photos
}

void restart_game_state(GameState *game_state) {
    // get rows and columns, make the board, and set all default values
    game_stae->rows = read_int_geq(MIN_ROWS);
    // check photos
}

int remove_completed_lines(char board[MAX_ROWS][MAX_COLUMNS]){
    int lines = 0;
    bool completed_line;
    for(int r=4; r<MAX_ROWS; ++r){
        completed_line = true;
        for(int c=0; c<MAX_COLUMNS; ++c){
            if(board[r][c] != 'X'){
                completed_line = false; 
                break;
            }
        }
        if(completed_line){
            ++lines;
            // Move all rows above, once down
            for(int r2=r; r2>3; --r2){
                for(int c=0; c<MAX_COLUMNS; ++c){
                    board[r2][c] = board[r2-1][c];
                }
            }
        }
    }
    return lines;
}

/********************************************************/
/******* LAB 1 - functions to program (start here) ******/
/********************************************************/

void init_game_state(GameState *game_state){
    game_state->score = 0;		// setting score to 0
    for(int r=0; r<MAX_ROWS; r++){
        for(int c=0; c<MAX_COLUMNS; c++){
            game_state->board[r][c] = '.';	// initialize all chars in board with '.'
        }
    }
    get_new_random_piece(game_state);		// getting random piece to spawn area
}


bool is_terminal(char board[MAX_ROWS][MAX_COLUMNS]){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < game_state->columns; j++) {
            if (board[i][j] == 'X'){ 
                return true;	// a piece blocks the spawn --> end of game
            }
        }
    }
    return false;
}

void move_piece(char board[MAX_ROWS][MAX_COLUMNS], PieceInfo *piece_info, int option){
    if (option == MOVE_LEFT) {
        piece_info->at_col--;	// move left
        if (is_collision(board, piece_info)) {
            piece_info->at_col++;   // move right if there is collision
        }
    } else if (option == MOVE_RIGHT) {
        piece_info->at_col++;	// move right
        if (is_collision(board, piece_info)) {
            piece_info->at_col--;   // move left if there is collision
        }
    }
}

void rotate_piece(char board[MAX_ROWS][MAX_COLUMNS], PieceInfo *piece_info, int option){
    Piece temp = piece_info->p;
    if (option == ROTATE_CW) {
        rotate_clockwise(&temp);
    } 
    else if (option == ROTATE_CCW) {
        rotate_counter_clockwise(&temp);
    }

    PieceInfo temp_info = *piece_info;
    temp_info.p = temp;

    if (!is_collision(board, &temp_info)) {
        piece_info->p = temp;
    }
    // rotating clockwise or counter clockwise a given piece
    // creating a temporary piece to check if it collides and, if not, then rotate the given piece
}
/********************************************************/
/******* LAB 1 - functions to program (end here) ********/
/********************************************************/





void run_turn(GameState *game_state, int option){
	PieceInfo *p_inf = &(game_state->current_piece);
	if(option == MOVE_LEFT || option == MOVE_RIGHT) 
		move_piece(game_state->board, p_inf, option);
	else if(option == ROTATE_CW || option == ROTATE_CCW)
		rotate_piece(game_state->board, p_inf, option);
    else if(option == NONE){} // do nothing
    else{ printf("[ERROR] Invalid option %d.\n", option); exit(-3); }

	// Move down if possible, otherwise block the piece and remove
    // the completed lines, aggregating them to the current score.
    // If it is not in a terminal state, add a new random piece to the board.
	p_inf->at_row++;
	if(is_collision(game_state)){
		p_inf->at_row--;
		block_current_piece(game_state);
        game_state->score += remove_completed_lines(game_state);
        if(!is_terminal(game_state))
            get_new_random_piece(game_state);
	}
}