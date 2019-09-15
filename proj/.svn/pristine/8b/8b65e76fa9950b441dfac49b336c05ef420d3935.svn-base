/**
 *  @author Joao Cardoso (jcard@fe.up.pt) ????
 *  Added by pfs@fe.up.pt
 */

#ifndef _SPRITE_H_
#define _SPRITE_H_

/** @defgroup sprite sprite
 * @{
 *
 * Functions for manipulating an object of type Sprite
 */

#define SPRITE_ALLOC_FAILED   NULL

struct sprite_t;
typedef struct sprite_t Sprite;


/**
 * @brief Creates a new Sprite object, allocating all the necessary memory
 * 
 * @param pic XPM of the sprite image
 * @param x X coordinate for the sprite
 * @param y Y coordinate for the sprite
 * @param xspeed Speed of the sprite in the X axis
 * @param yspeed Speed of the sprite in the Y axis
 * 
 * @return Pointer to object of type Sprite
 */
Sprite *create_sprite(xpm_string_t pic[], int x, int y, int xspeed, int yspeed);


/**
 * @brief Draws a sprite on the double buffer
 * 
 * @param sp Pointer to object of type Sprite, that was previously initialized
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int draw_sprite(Sprite* sp);


/**
 * @brief Draws a sprite on the double buffer, at the coordinates specified in the arguments
 * 
 * @param sp Pointer to object of type Sprite, that was previously initialized
 * @param x X coordinate of where we want to draw the sprite
 * @param y Y coordinate of where we want to draw the sprite
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int draw_sprite_coords(Sprite* sp, int x, int y);


/**
 * @brief Function only used for the aim sprite; updates the aim position, based on the horizontal mouse movements
 * 
 * @param aim Aim sprite
 * @param pp Last mouse packet received
 * 
 * @return 0, indicating no error ocurred
 */
int update_aim(Sprite* aim, struct packet pp);


/**
 * @brief Returns the sprite's x coordinate
 * 
 * @param st Pointer to object of type Sprite, that was previously initialized
 * 
 * @return The sprite's x coordinate
 */
int get_st_x(Sprite* st);


/**
 * @brief Returns the sprite's y coordinate
 * 
 * @param st Pointer to object of type Sprite, that was previously initialized
 * 
 * @return The sprite's y coordinate
 */
int get_st_y(Sprite* st);


/**
 * @brief Returns the sprite's width
 * 
 * @param st Pointer to object of type Sprite, that was previously initialized
 * 
 * @return The sprite's width
 */
int get_st_width(Sprite* st);


/**
 * @brief Returns the sprite's height
 * 
 * @param st Pointer to object of type Sprite, that was previously initialized
 * 
 * @return The sprite's height
 */
int get_st_height(Sprite* st);


/**
 * @brief Returns the sprite's pixmap
 * 
 * @param st Pointer to object of type Sprite, that was previously initialized
 * 
 * @return The sprite's pixmap
 */
char* get_st_map(Sprite* st);


/**
 * @brief Deletes a sprite variable, freeing all the memory previously allocated
 * 
 * @param sp Pointer to object of type Sprite
 */
void destroy_sprite(Sprite* sp);


/** @} end of sprite */

#endif
