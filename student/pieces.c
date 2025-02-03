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

void rotate_counter_clockwise(Piece *p)
{
    for (int i = 0; i < PIECE_SIZE; ++i)
    {
        for (int j = 0; j < PIECE_SIZE; ++j)
        {
            p->board[i][j] = p->board[-j][i];
            // rotation--> by changing coordinates and inversing the first one
        }
    }
}

void rotate_clockwise(Piece *p)
{
    for (int i = 0; i < 3; ++i)
    {
        rotate_counter_clockwise(p);
        // rotating 3 times counter clockwise == 1 time clockwise; 2 times counter clockwise == 2 times clockwise, and so on
    }
}

Piece make_O()
{
    Piece piece = {
        .name = 'O',
        .rows = 2,
        .cols = 2,
        .board = {
            {'*', '*', '.', '.'},
            {'*', '*', '.', '.'},
            {'.', '.', '.', '.'},
            {'.', '.', '.', '.'}}};
    return piece;
}

Piece make_I()
{
    Piece piece = {
        .name = 'I',
        .rows = 4,
        .cols = 1,
        .board = {
            {'*', '.', '.', '.'},
            {'*', '.', '.', '.'},
            {'*', '.', '.', '.'},
            {'*', '.', '.', '.'}}};
    return piece;
}

Piece make_S()
{
    Piece piece = {
        .name = 'S',
        .rows = 2,
        .cols = 3,
        .board = {
            {'.', '*', '*', '.'},
            {'*', '*', '.', '.'},
            {'.', '.', '.', '.'},
            {'.', '.', '.', '.'}}};
}

Piece make_Z()
{
    Piece piece = {
        .name = 'Z',
        .rows = 2,
        .cols = 3,
        .board = {
            {'*', '*', '.', '.'},
            {'.', '*', '*', '.'},
            {'.', '.', '.', '.'},
            {'.', '.', '.', '.'}}};
    return piece;
}

Piece make_L()
{
    Piece piece = {
        .name = 'L',
        .rows = 3,
        .cols = 2,
        .board = {
            {'*', '.', '.', '.'},
            {'*', '.', '.', '.'},
            {'*', '*', '.', '.'},
            {'.', '.', '.', '.'}}};
}

Piece make_J()
{
    Piece piece = {
        .name = 'J',
        .rows = 3,
        .cols = 2,
        .board = {
            {'.', '*', '.', '.'},
            {'.', '*', '.', '.'},
            {'*', '*', '.', '.'},
            {'.', '.', '.', '.'}}};
}

Piece make_T()
{
    Piece piece = {
        .name = 'T',
        .rows = 2,
        .cols = 3,
        .board = {
            {'*', '*', '*', '.'},
            {'.', '*', '.', '.'},
            {'.', '.', '.', '.'},
            {'.', '.', '.', '.'}}};
    return piece;
}
