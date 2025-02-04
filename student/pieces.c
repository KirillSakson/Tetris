#include "pieces.h"

void init_piece(Piece *p)
{
    char initial_board[PIECE_SIZE][PIECE_SIZE] = {
        {'.', '.', '.', '.'},
        {'.', '.', '.', '.'},
        {'.', '.', '.', '.'},
        {'.', '.', '.', '.'}};    // initializing the board
    for (int i = 0; i < PIECE_SIZE; ++i)
    {
        for (int j = 0; j < PIECE_SIZE; ++j)
        {
            p->board[i][j] = initial_board[i][j];    // initial board will take the piece's shape
        }
    }
    p->rows = 0;    // piece rows to 0
    p->cols = 0;    // piece columns to 0
}

void print_piece(Piece p)
{
    printf("Name: %c; Size: %dx%d\n", p.name, p.rows, p.cols);
    for (int i = 0; i < PIECE_SIZE; ++i)
    {
        for (int j = 0; j < PIECE_SIZE; ++j)
        {
            printf("%c", p.board[i][j]);
        }
        printf("\n");
    }
}

void rotate_clockwise(Piece *p)
{
    char temp[PIECE_SIZE][PIECE_SIZE];  // temporary matrix

    // rotation --> 90º clockwise
    for (int i = 0; i < p->rows; ++i){
        for (int j = 0; j < p->cols; ++j){
            temp[j][p->rows-1-i]=p->board[i][j];
        }
    }

    // used parts of matrix are being copied
    for (int i = 0; i < p->cols; ++i) { // cols = rows of new
        for (int j = 0; j <p->rows; ++j) {  // rows = cols of new
            p->board[i][j] = temp[i][j];
        }
    }

    // changing rows for cols and cols for rows
    int temp_size = p->rows;
    p->rows = p->cols;
    p->cols = temp_size;
}

void rotate_counter_clockwise(Piece *p)
{
    for (int i = 0; i < 3; ++i) {
        rotate_clockwise(p);
        // rotating 3 times clockwise == 1 time counter clockwise;
    }
}

Piece make_O()
{
    Piece piece;
    init_piece(&piece);
    piece.name = 'O';
    piece.rows = piece.cols = 2;
    piece.board[0][0] = '#'; piece.board[0][1] = '#';
    piece.board[1][0] = '#'; piece.board[1][1] = '#';
    return piece;
}

Piece make_I()
{
    Piece piece;
    init_piece(&piece);
    piece.name = 'I';
    piece.rows = 4;
    piece.cols = 1;
    piece.board[0][0] = '#';
    piece.board[1][0] = '#';
    piece.board[2][0] = '#';
    piece.board[3][0] = '#';
    return piece;
}

Piece make_S()
{
    Piece piece;
    init_piece(&piece);
    piece.name = 'S';
    piece.rows = 2;
    piece.cols = 3;
    piece.board[0][1] = '#';
    piece.board[0][2] = '#';
    piece.board[1][0] = '#';
    piece.board[1][1] = '#';
    return piece;
}

Piece make_Z()
{
    Piece piece;
    init_piece(&piece);
    piece.name = 'Z';
    piece.rows = 2;
    piece.cols = 3;
    piece.board[0][0] = '#';
    piece.board[0][1] = '#';
    piece.board[1][1] = '#';
    piece.board[1][2] = '#';
    return piece;
}

Piece make_L()
{
    Piece piece;
    init_piece(&piece);
    piece.name = 'L';
    piece.rows = 3;
    piece.cols = 2;
    piece.board[0][0] = '#';
    piece.board[1][0] = '#';
    piece.board[2][0] = '#';
    piece.board[2][1] = '#';
    return piece;
}

Piece make_J()
{
    Piece piece;
    init_piece(&piece);
    piece.name = 'J';
    piece.rows = 3;
    piece.cols = 2;
    piece.board[0][1] = '#';
    piece.board[1][1] = '#';
    piece.board[2][0] = '#';
    piece.board[2][1] = '#';
    return piece;
}

Piece make_T()
{
    Piece piece;
    init_piece(&piece);
    piece.name = 'T';
    piece.rows = 2;
    piece.cols = 3;
    piece.board[0][0] = '#';
    piece.board[0][1] = '#';
    piece.board[0][2] = '#';
    piece.board[1][1] = '#';
    return piece;
}
