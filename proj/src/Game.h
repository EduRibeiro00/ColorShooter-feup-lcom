#ifndef _GAME_H_
#define _GAME_H_

#define GAME_ALLOC_FAILED   NULL
#include "Bullet.h"
#include "sprite.h"
#include "Cursor.h"
#include "Button.h"
#include "Ships.h"
#include "Enemy.h"
#include "Highscores.h"
#include "StateMachine.h"

/** @defgroup Game Game
 * @{
 * Functions for manipulating an object of type Game, that is in control of the main part/core of the game
 */

struct game_t;
typedef struct game_t Game;


/**
 * @brief Creates an object of type Game, alocates space, initializes all of its fields, and subscribes the timer, mouse and keyboard, in order to start the game
 * 
 * @return Pointer to an object of type Game
 */
Game* start_game();


/**
 * @brief Terminates the game, freeing all the memory that was allocated and unsubscribing the devices
 * 
 * @param g Pointer to an object of type Game
 */
void end_game(Game* g);


/**
 * @brief Main function of the game; contains the interrupt cycle that keeps updating the game
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void play_game(Game* g);


/**
 * @brief Manages every thing related/triggered by timer interrupts
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void timeManager(Game* g);


/**
 * @brief Manages every thing related/triggered by keyboard interrupts
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void kbdManager(Game* g);


/**
 * @brief Manages every thing related/triggered by mouse interrupts
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized 
 */
void mouseManager(Game* g);


/**
 * @brief Increases the score of the game
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized 
 */
void increase_score(Game* g);


/**
 * @brief Increases the difficulty of the game, making the enemies appear more frequently, and move faster
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized 
 */
void increase_difficulty(Game* g);


/**
 * @brief Function that increases the difficulty of the game in the right circumstances, given the current score
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized 
 */
void handle_difficulty(Game* g);


/**
 * @brief Increases the light beam special atack progress, in the current game
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized 
 */
void increase_lb_progress(Game* g);


/**
 * @brief Draws the correct background on screen, given the menu option that the game is currently in (highscores, main menu, etc)
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void draw_background(Game* g);


/**
 * @brief Draws the right portion of the background on screen, to make it look like it is moving; updates the index for the moving background, for the next time the function is invoked
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void draw_moving_background(Game* g);


/**
 * @brief Function that associates a number to a number sprite
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 * @param number Number for which we want the associated sprite 
 * 
 * @return The sprite which is associated to a certain number (from 0 to 9)
 */
Sprite* num_to_sprite(Game* g, int number);


/**
 * @brief Function that, given the current score and the menu option the game is currently in, draws in the double buffer the right pixmaps, in order to display the score
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void display_score(Game* g);


/**
 * @brief Function that returns a value depending on which button the cursor is clicking on (if any). The buttons checked depend on the menu option the game is currently in (highscores, main menu, etc)
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 * 
 * @return A value, from 1 to 4, that indicates the clicked button, or 0 if no button was clicked
 */
int mouse_check_clicks(Game* g);


/**
 * @brief Checks if the mouse is hovering over any buttons (if it is, highlights that button). The buttons checked depend on the menu option the game is currently in (highscores, main menu, etc)
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void highlight_buttons(Game * g);


/**
 * @brief Does a coordinate check; checks if there was collision between a bullet and an enemy
 * 
 * @param b Pointer to object of type Bullet, that may have collided with the enemy
 * @param enemy Pointer to object of type Enemy, that may have collided with the bullet
 * 
 * @return 1 if the objects collided, 0 if not
 */
int check_pixmap_collision(Bullet* b, Enemy* enemy);


/**
 * @brief Compares the pixmaps, in order to see if there is any overlaid pixels (checks if there was any real collision)
 * 
 * @param b Pointer to object of type Bullet, that may have collided with the enemy
 * @param enemy Pointer to object of type Enemy, that may have collided with the bullet
 * 
 * @return 1 if the objects collided, 0 if not
 */
int check_pixel_collision(Bullet* b, Enemy* enemy);


/**
 * @brief Checks collisions with bullets for one specific enemy spaceship
 * 
 * @param g Pointer to an object of type Game, containing the array with all the exiting bullets
 * @param enemy Pointer to object of type Enemy, that may have collided with a bullet
 * 
 * @return Returns true if there was collision, and if the bullet destroyed the enemy
 */
bool check_ship_collisions(Game* g, Enemy* enemy);


/**
 * @brief Performs a collision check for all enemies, updating the enemies array accordingly and creating explosions for destroyed enemies
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void check_all_collisions(Game * g);


/**
 * @brief Draws/updates a new frame, on the double buffer, given the current game state
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void update_frame(Game* g);


/**
 * @brief Draws on the double buffer the current progress bar (for the light beam special atack)
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void display_progress_bar(Game* g);


/**
 * @brief Draws on the double buffer the highscores
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void display_highscores(Game* g);


/**
 * @brief Uses/activates the light beam ability (if it is fully charged)
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void use_light_beam_ability(Game* g);


/**
 * @brief Ends the effects of the light beam ability, returning the game to normal
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 */
void end_light_beam_ability(Game* g);


/**
 * @brief Changes the color of the current ammo, based on the keyboard input
 * 
 * @param g Pointer to an object of type Game, that was previously inicialized
 * @param key_code Last keycode received from the keyboard
 */
void change_current_ammo(Game* g, uint8_t key_code);



//--------------- functions for the bullets array ---------------//


/**
 * @brief Changes the color only of the bullet that was not launched
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 * @param key_code Last keycode received from the keyboard
 */
void change_ammo_array(Game* g, uint8_t key_code);


/**
 * @brief Resets the bullets array, by deleting all the bullets
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
void delete_bullets(Game* g);


/**
 * @brief Creates a new bullet, and adds it to the bullets array
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
void add_bullet(Game* g);


/**
 * @brief Draws all the bullets in the double buffer
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
void draw_bullets(Game* g);


/**
 * @brief Updates all the bullet positions in the array
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
void update_bullets_array(Game* g);


/**
 * @brief Animates all the bullets in the array, by changing their current active pixmap
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
void animate_bullets_array(Game* g);


/**
 * @brief Removes a bullet from the array
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 * @param index index of that bullet in the bullets array
 */
void remove_bullet(Game* g, int index);


/**
 * @brief Launches the bullet, in the bullets array, that was not launched yet
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
void launch_bullet_array(Game* g);


/**
 * @brief Checks if there is a bullet in the array that was not launched
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
bool check_if_static_bullet(Game* g);


/**
 * @brief Removes from the array bullets that are out of bounds (off the screen)
 * 
 * @param g Pointer to an object of type Game, containing the bullets array
 */
void remove_oob_bullets(Game* g);


/** @} end of Game */

#endif
