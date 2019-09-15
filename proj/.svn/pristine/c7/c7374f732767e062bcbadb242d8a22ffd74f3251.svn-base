#ifndef _ENEMY_H_
#define _ENEMY_H_

/** @defgroup Enemy Enemy
 * @{
 * Functions for manipulating an object of type Enemy
 */

#define ENEMY_ALLOC_FAILED  NULL


/* enum type, specificating all the different possible colors (does not include white) */
typedef enum{ COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW, COLOR_SIZE} Color;

struct enemy_t;
typedef struct enemy_t Enemy;


/**
 * @brief Creates a new enemy (the 5 images are to create an animation)
 * 
 * @param spaceship0 Image of the spaceship number 0, of the right color
 * @param spaceship1 Image of the spaceship number 1, of the right color
 * @param spaceship2 Image of the spaceship number 2, of the right color
 * @param spaceship3 Image of the spaceship number 3, of the right color
 * @param spaceship4 Image of the spaceship number 4, of the right color
 * @param x Initial X coordinate for the enemy
 * @param y Initial Y coordinate for the enemy
 * @param xspeed Speed of the enemy in the X axis
 * @param yspeed Speed of the enemy in the Y axis
 * @param c Color of the enemy spaceship
 * 
 * @return Pointer to an object of type Enemy
 */
Enemy* create_enemy(xpm_image_t spaceship0, xpm_image_t spaceship1, xpm_image_t spaceship2, xpm_image_t spaceship3, xpm_image_t spaceship4, int x, int y, int xspeed, int yspeed, Color c);


/**
 * @brief Deletes an enemy, freeing all the memory previously allocated
 * 
 * @param enemy Pointer to object of type Enemy
 */
void delete_enemy(Enemy* enemy);


/**
 * @brief Draws an enemy on the double buffer, at the right coordinates
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 */
void draw_enemy(Enemy* enemy);


/**
 * @brief Updates the position of the enemy
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 * @param move_down Tells if the enemy is supposed to move down
 */
void update_enemy(Enemy* enemy, bool move_down);


/**
 * @brief Changes the current pixmap of the enemy, in order to animate the spaceship
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 */
void animate_enemy(Enemy* enemy);


/**
 * @brief Returns the enemy's x coordinate
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 * 
 * @return The enemy's X coordinate
 */
int get_enemy_x(Enemy* enemy);


/**
 * @brief Returns the enemy's y coordinate
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 * 
 * @return The enemy's Y coordinate
 */
int get_enemy_y(Enemy* enemy);


/**
 * @brief Returns the enemy's width
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 * 
 * @return The enemy's width
 */
int get_enemy_width(Enemy* enemy);


/**
 * @brief Returns the enemy's height
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 * 
 * @return The enemy's height 
 */
int get_enemy_height(Enemy* enemy);


/**
 * @brief Returns the enemy's color
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 * 
 * @return The color of the enemy spaceship
 */
Color get_enemy_color(Enemy* enemy);


/**
 * @brief Returns the enemy's current pixmap
 * 
 * @param enemy Pointer to object of type Enemy, that was previously initialized
 * 
 * @return The current pixmap
 */
char* get_enemy_current_pixmap(Enemy* enemy);


/** @} end of Enemy */

#endif
