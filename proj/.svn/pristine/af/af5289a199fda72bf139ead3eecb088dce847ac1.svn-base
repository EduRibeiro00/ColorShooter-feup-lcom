#include <lcom/lcf.h>
#include "StateMachine.h"

struct st_machines_t{

  player_state playerState; ///< current player state
  player_events playerEvent; ///< current player event
  game_state gameState; ///< current game state
  game_events gameEvent; ///< current game event
};


StateMachines* create_st_machine(){

  StateMachines* st = (StateMachines *) malloc(sizeof(StateMachines));
  
  if(st == ST_MACHINE_ALLOC_FAILED)
    return ST_MACHINE_ALLOC_FAILED;

    //sets the initial states
    st->playerState = NEW_GAME;
    st->gameState = MAIN_MENU;

    return st;
}

//-------------------

void delete_st_machine(StateMachines* st){

  if(st == NULL)
    return;

  free(st);
  st = NULL;
}

//-------------------

player_state get_player_state(StateMachines* st){
  
  return st->playerState;
}

//-------------------

game_state get_game_state(StateMachines* st){

  return st->gameState;
}

//-------------------

void set_game_event(StateMachines* st, game_events event){

  st->gameEvent = event;
}

//-------------------

void set_player_event(StateMachines* st, player_events event){

  st->playerEvent = event;
}

//-------------------

void game_event_handler(StateMachines* st){

  switch(st->gameState){

    case MAIN_MENU:
      if(st->gameEvent == START_SP)
        st->gameState = GAME;

      if(st->gameEvent == LEAVE)
        st->gameState = EXIT;

      if(st->gameEvent == GO_INSTS)
        st->gameState = INSTRUCTIONS;

      if(st->gameEvent == GO_HS)
        st->gameState = HIGHSCORES;

      break;

    case GAME:
      if(st->gameEvent == GO_GAMEOVER)
        st->gameState = GAME_OVER;

      break;

    case GAME_OVER:
      if(st->gameEvent == START_SP)
        st->gameState = GAME;

      if(st->gameEvent == RETURN_MM)
        st->gameState = MAIN_MENU;

      break;

    case INSTRUCTIONS:
      if(st->gameEvent == BACK)
        st->gameState = MAIN_MENU;

      break;

    case HIGHSCORES:
      if(st->gameEvent == BACK)
        st->gameState = MAIN_MENU;
      
      break;
  
    default:
      break;
  
  }
}

//-------------------

void player_event_handler(StateMachines* st){

  switch(st->playerState){

    case NEW_GAME:
      if(st->playerEvent == START)
        st->playerState = PLAY;
      
      break;

    case PLAY:
      if(st->playerEvent == LOST)
        st->playerState = END;

      break;

    case END:
      if(st->playerEvent == RESET)
        st->playerState = NEW_GAME;

      break;

    default:
      break;
  }
}
