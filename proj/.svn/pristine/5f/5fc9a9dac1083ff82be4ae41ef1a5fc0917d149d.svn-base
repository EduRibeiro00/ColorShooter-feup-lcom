#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

/** @defgroup Explosion Explosion
 * @{
 * Functions for manipulating an object of type Explosion
 */

#define EXPLOSION_ALLOC_FAILED   NULL

struct explosion_t;
typedef struct explosion_t Explosion;


/**
 * @brief Creates a new explosion
 * 
 * @param explosions Array with all the explosion images (in order to animate the explosion)
 * @param arraySize Size of the images array
 * @param x X coordinate of the explosion
 * @param y Y coordinate of the explosion
 * 
 * @return Pointer to object of type Explosion
 */
Explosion* create_explosion(xpm_image_t explosions[], int arraySize, int x, int y);


/**
 * @brief Deletes an explosion, freeing all the memory previously allocated
 * 
 * @param exp Pointer to object of type Explosion
 */
void delete_explosion(Explosion* exp);


/**
 * @brief Changes the current pixmap of the explosion, in order to animate it
 * 
 * @param exp Pointer to object of type Explosion, that was previously initialized
 * 
 * @return True if the animation already "used" all of the explosion images, meaning the explosion is over and the object should be deleted. False otherwise
 */
bool animate_explosion(Explosion* exp);


/**
 * @brief Draws the current pixmap of the explosion on the double buffer, on the right coordinates
 * 
 * @param exp Pointer to object of type Explosion, that was previously initialized
 */
void draw_explosion(Explosion* exp);


/** @} end of Explosion */

#endif
