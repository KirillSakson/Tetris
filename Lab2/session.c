#include "session.h"

void restart_session_game_state(Session *session){
    // restarts current game state of the session
    restart_game_state(&(session->current_game_state));
}

void init_session(Session *session){
    // initialises a new session
    session->best_score = 0;    // setting best score to 0
    init_game_state(&(session->current_game_state));
}
