#include "main.h"
#include "game.h"

void run_game(Session *session){
    // main function which runs the current game
    GameState *game_state = &session->current_game_state;

    bool finish_game; 

    do{
        // 1. Print data
        printf("Best score: %d\n", session->best_score);
        print_game_state(game_state);

        // 2. Select a move
        int game_option;
        do{
            print_options();
            printf("Enter a game option: ");
            game_option = read_int();
        }while(!is_valid_option(game_option));
        
        // 3.a Quit game
        if(game_option == QUIT_GAME)
            return;
        // 3.b Show best move
        if(game_option == SHOW_BEST_MOVE){
            // ToDo in Lab 3
            continue;
        }

        // 3.c Run one turn with the given option
        run_turn(game_state, game_option);

        // 4. Update scores
        session->best_score = max(session->best_score, game_state->score);
        
        // 5. Add new number
        finish_game = is_terminal(game_state);  // is_terminal gets only game_state
    }while(!finish_game);

    printf("*** GAME OVER ***\n");
    print_game_state(game_state);
}

void new_game(Session *session){
    // starts a new game
    restart_session_game_state(session);
    run_game(session);
}

void save_game(Session *session){
    // saves current game in a file, so it can be accessed in future
    char save_file_name[30];  // file's name
    printf("Enter the file name: ");
    scanf("%s", save_file_name);
    FILE *file = fopen(save_file_name, "w");  // open file to write the data inside
    fprintf(file, "Score: %d\n", session->current_game_state.score);
    fprintf(file, "PieceInfo:\n");
    fprintf(file, "at_row: %d\n", session->current_game_state.current_piece.at_row);
    fprintf(file, "at_col: %d\n", session->current_game_state.current_piece.at_col);
    fprintf(file, "name: %c\n", session->current_game_state.current_piece.p.name);
    fprintf(file, "rows: %d\n", session->current_game_state.current_piece.p.rows);
    fprintf(file, "cols: %d\n", session->current_game_state.current_piece.p.cols);
    for (int i = 0; i<session->current_game_state.current_piece.p.rows; ++i) {
        fprintf(file, "%s\n", session->current_game_state.current_piece.p.board[i]);
    }
    fprintf(file, "Board:\n");
    fprintf(file, "rows: %d\n", session->current_game_state.rows);
    fprintf(file, "cols: %d\n", session->current_game_state.columns);
    for (int i = 0; i<session->current_game_state.rows; ++i) {
        fprintf(file, "%s\n", session->current_game_state.board[i]);
    }
    fclose(file);  // close the file after writing the data into the file
}

void load_game(Session *session){
    // loads the game from an existing file, to continue playing it
    char load_file_name[30];  // name of the file to be loaded
    printf("Enter the file name: ");
    scanf("%s", load_file_name);
    FILE *file = fopen(load_file_name, "r");  // open file in read-only mode
    fscanf(file, "Score: %d\n\n", &session->current_game_state.score);
    fscanf(file, "PieceInfo:\nat_row: %d\n", &session->current_game_state.current_piece.at_row);
    fscanf(file, "at_col: %d\n", &session->current_game_state.current_piece.at_col);
    fscanf(file, "name: %c\n", &session->current_game_state.current_piece.p.name);
    fscanf(file, "rows: %d\n", &session->current_game_state.current_piece.p.rows);
    fscanf(file, "cols: %d\n", &session->current_game_state.current_piece.p.cols);
    for (int i = 0; i<session->current_game_state.current_piece.p.rows; ++i) {
        fscanf(file, "%s\n", &(*session->current_game_state.current_piece.p.board[i]));
    }
    fscanf(file, "Board:\nrows: %d\n", &session->current_game_state.rows);
    fscanf(file, "cols: %d\n", &session->current_game_state.columns);
    // allocating the memory for the board
    session->current_game_state.board = malloc(sizeof(char*) * session->current_game_state.rows);
    for (int i=0;i<session->current_game_state.rows; ++i) {
        session->current_game_state.board[i] = malloc(sizeof(char) * session->current_game_state.columns);
    }

    // loading board data from the file
    for (int i = 0; i<session->current_game_state.rows; ++i) {
        fscanf(file, "%s\n", session->current_game_state.board[i]);
    }
    fclose(file);  // close the file after reading and loading the data from the file
}

void resume_game(Session *session){
    // to resume the game loaded or not into the game_state from the file
    run_game(session);
}

void print_menu(){
    printf("Menu options:\n");
    printf("\t1. New game.\n");  // LAB1 - basic lab for creating board, pieces and movements
                                 // LAB1 - extend game with GameState data structure, current score, best score
                                 //      - also add standard (4x4) with a possible extension, read board from command line  
    printf("\t2. Save game.\n"); // LAB2 - Writing file
    printf("\t3. Load game.\n"); // LAB2 - Reading file
    printf("\t4. Resume game.\n"); // LAB2 - Continue game after reading file
    printf("\t5. Exit.\n");  // Free all reserved memory!
}


void run(Session *session){
    // manipulates which game should be loaded, stored or resumed, or created a new game
    int option;
    do{
        print_menu();
        do{
            printf("Enter an integer (%d-%d): ", NEW_GAME, EXIT);
            option = read_int();
        }while(option < NEW_GAME || option > EXIT);

        switch (option){
        case NEW_GAME:
            new_game(session);
            break;
        case SAVE_GAME:
            save_game(session);
            break;
        case LOAD_GAME:
            load_game(session);
            break;
        case RESUME_GAME:
            resume_game(session);
            break;
        case EXIT:
            free_game_state(&session->current_game_state);  // release dynamically allocated memory during the session
            break;
        }
    }while(option != EXIT);
}

int main(){
    Session session;
    init_session(&session);
    run(&session);
}
