#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

/** @defgroup StateMachine StateMachine
 * @{
 * Functions for manipulating the two state machines used
 */

#define ST_MACHINE_ALLOC_FAILED  NULL


/* enum type representing all the states in the game state machine */
typedef enum{MAIN_MENU, GAME, GAME_OVER, INSTRUCTIONS, HIGHSCORES, EXIT} game_state;

/* enmu type representing all the events for the game state machine */
typedef enum{START_SP, RETURN_MM, LEAVE, GO_INSTS, GO_GAMEOVER, GO_HS, BACK} game_events; 


/* enum type representing all the states in the player state machine (the playing of the game itself) */
typedef enum{NEW_GAME, PLAY, END} player_state;

/* enum type representing all the events for the player state machine */
typedef enum{START, LOST, RESET} player_events;


struct st_machines_t;
typedef struct st_machines_t StateMachines;


/**
 * @brief Creates a new state machine object, putting the two state machines in their respective initial states
 * 
 * @return Pointer to object of type StateMachines
 */
StateMachines* create_st_machine();


/**
 * @brief Deletes a state machine object, freeing all the memory previously allocated
 * 
 * @param st Pointer to object of type StateMachines
 */
void delete_st_machine(StateMachines* st);


/**
 * @brief Returns the current player state
 * 
 * @param st Pointer to object of type StateMachines, that was previously initialized
 * 
 * @return The current player state
 */
player_state get_player_state(StateMachines* st);


/**
 * @brief Returns the current game state
 * 
 * @param st Pointer to object of type StateMachines, that was previously initialized
 * 
 * @return The current game state
 */
game_state get_game_state(StateMachines* st);


/**
 * @brief Updates the game event
 * 
 * @param st Pointer to object of type StateMachines, that was previously initialized
 * @param event New game event
 */
void set_game_event(StateMachines* st, game_events event);


/**
 * @brief Updates the player event
 * 
 * @param st Pointer to object of type StateMachines, that was previously initialized
 * @param event New player event
 */
void set_player_event(StateMachines* st, player_events event);


/**
 * @brief Handles the different game events, changing the state if needed
 * 
 * @param st Pointer to object of type StateMachines, that was previously initialized
 */
void game_event_handler(StateMachines* st);


/**
 * @brief Handles the different player events, changing the state if needed
 * 
 * @param st Pointer to object of type StateMachines, that was previously initialized
 */
void player_event_handler(StateMachines* st);


/** @} end of StateMachine */

#endif
