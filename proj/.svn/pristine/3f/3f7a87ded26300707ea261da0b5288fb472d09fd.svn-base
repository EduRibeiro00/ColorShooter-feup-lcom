#ifndef _SHIPS_H_
#define _SHIPS_H_

#include "projMacros.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"

/** @defgroup Ships Ships
 * @{
 * Functions for manipulating an object of type Ships, containing information of the enemies and explosions
 */


#define SHIPS_ALLOC_FAILED  NULL

struct ships_t;
typedef struct ships_t Ships;


/**
 * @brief Creates a Ships variable, allocating memory and initializing all the needed fields
 * 
 * @return Pointer to object of type Ships
 */
Ships* create_ships();


/**
 * @brief Creates a random enemy, and adds it to the enemy array
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 */
void add_enemy(Ships* ships);


/**
 * @brief Adds an explosion to the explosions array, on the desired coordinates
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * @param x X coordinate for the explosion
 * @param y Y coordinate for the explosion
 */
void add_explosion(Ships* ships, int x, int y);


/**
 * @brief Draws all enemies and explosions on the double buffer
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 */
void draw_ships(Ships* ships);


/**
 * @brief Removes an enemy of the array (enemy is on the index position in the array)
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * @param index Index of that enemy, in the enemies array
 */
void remove_ship(Ships* ships, int index);


/**
 * @brief Removes an explosion of the array (explosion is on the index position of the array)
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * @param index Index of that explosion, in the explosions array
 */
void remove_explosion(Ships* ships, int index);


/**
 * @brief Checks if any enemy has gotten too close to the player ship, making him lose the game
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * 
 * @return True if the player lost, false otherwise
 */
bool player_lost(Ships* ships);


/**
 * @brief Resets the enemies and explosions array, in order to start a new game
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 */
void reset_ships(Ships* ships);


/**
 * @brief Updates the position of all the enemies
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 */
void update_ships(Ships* ships);


/**
 * @brief Updates the current pixmap of all the enemies and explosions
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 */
void animate_ships(Ships* ships);


/**
 * @brief Deletes a Ships variable, freeing all the memory previously allocated
 * 
 * @param ships Pointer to object of type Ships
 */
void delete_ships(Ships* ships);


/**
 * @brief Changes the move_down variable, that tells if the enemies should move down or not
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 */
void toggle_move_down(Ships* ships);


/**
 * @brief Resets the difficulty of the game to its initial values
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 */
void reset_difficulty(Ships* ships);


/**
 * @brief Returns the enemies array
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * @return The enemies array, containing all the enemies
 */
Enemy** get_enemies(Ships* ships);


/**
 * @brief Returns the size of the enemies array
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * @return int Size of the array
 */
int get_enemies_size(Ships* ships);


/**
 * @brief Adjusts the difficulty off the game, making the enemies spawn more frequently and move faster
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * @param dif_level Current difficulty level, that tells what fields (spawn rate, enemy speed, ect) should be changed
 */
void adjust_difficulty(Ships* ships, int dif_level);


/**
 * @brief Returns the enemies spawn rate
 * 
 * @param ships Pointer to object of type Ships, that was previously initialized
 * @return int Spawn rate
 */
int get_spawn_rate(Ships* ships);


/** @} end of Ships */

#endif
