#include "session.h"

void restart_session_game_state(Session *session){
    init_game_state(&session->current_game_state);    // initialization of a game state
}

void init_session(Session *session){
    session->best_score = 0;    // setting best score to 0
    restart_session_game_state(session);    // restarting the state game of the session
}

