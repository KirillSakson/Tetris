#include "pieces.h"

void init_piece(Piece *p){
	// ToDo in LAB 1
}

void print_piece(Piece p){
    printf("Name: %c; Size: %dx%d\n", p.name, p.rows, p.cols);
    for(int i=0; i<PIECE_SIZE; ++i){
        for(int j=0; j<PIECE_SIZE; ++j){
            printf("%c", p.board[i][j]);
        }
        printf("\n");
    }
}

void rotate_clockwise(Piece *p){
    // ToDo in LAB 1
}

void rotate_counter_clockwise(Piece *p){
    // ToDo in LAB 1
}

Piece make_O(){
    // ToDo in LAB 1
}

Piece make_I(){
    // ToDo in LAB 1
}


Piece make_S(){
	// ToDo in LAB 1
}


Piece make_Z(){
    // ToDo in LAB 1
}

Piece make_L(){
    // ToDo in LAB 1
}

Piece make_J(){
    // ToDo in LAB 1
}

Piece make_T(){
    // ToDo in LAB 1
}

