#ifndef _BULLET_H_
#define _BULLET_H_

#include "sprite.h"
#include "Enemy.h"

/** @defgroup Bullet Bullet
 * @{
 * Functions for manipulating an object of type Bullet
 */

#define BULLET_ALLOC_FAILED   NULL

struct bullet_t;
typedef struct bullet_t Bullet;


/**
 * @brief Creates a bullet object, with all the images associated with all the possible colored ammo (when creating a light beam bullet, all the images will be of white bullets, and the color will not matter)
 * 
 * @param red Array with the red bullet images
 * @param green Array with the green bullet images
 * @param blue Array with the blue bullet images
 * @param yellow Array with the yellow bullet imagesx
 * @param arraySize Size of the arrays
 * @param x Initial X coordinate for the bullet
 * @param y Initial Y coordinate for the bullet
 * @param xspeed Initial bullet speed in the X axis
 * @param yspeed Initial bullet speed in the Y axis
 * @param initialColor Initial bullet color
 * @param anim_start Initial animation index for the bullet
 * 
 * @return Pointer to object of type Bullet
 */
Bullet* create_bullet(xpm_image_t red[], xpm_image_t green[], xpm_image_t blue[], xpm_image_t yellow[], int arraySize, int x, int y, int xspeed, int yspeed, Color initialColor, int anim_start);


/**
 * @brief Deletes a bullet object, freeing all the previously allocated space
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 */
void delete_bullet(Bullet* b);


/**
 * @brief Draws the bullet on the double buffer, based on the current ammo color and the current animation
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int draw_bullet(Bullet* b);


/**
 * @brief Changes the current ammo color, based off the key pressed
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * @param key_code Last keycode received from the keyboard
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int change_ammo(Bullet* b, uint8_t key_code);


/**
 * @brief Updates the bullet position, given its speed (to be called only after it was launched)
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return 0, indicating there was no error
 */
int update_bullet_pos(Bullet* b);


/**
 * @brief Launches a normal bullet, changing its speed, so that the bullet starts moving towards the aim
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * @param aim Object of type Sprite, representing the aim
 */
void launch_bullet(Bullet* b, Sprite* aim);


/**
 * @brief Launches a light beam bullet (to be used when the light beam ability is activated)
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * @param aim Pointer to object of type Sprite, representing the aim
 */
void launch_bullet_light_beam(Bullet* b, Sprite* aim);


/**
 * @brief Checks if the bullet is out of bounds
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return True if the bullet is out of bounds, false otherwise
 */
bool bullet_oob(Bullet* b);


/**
 * @brief Changes the current pixmap of the bullet
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 */
void animate_bullet(Bullet* b);


/**
 * @brief Returns the current bullet color
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return Current bullet color
 */
Color get_bullet_color(Bullet* b);


/**
 * @brief Returns the current x coordinate for the top leftmost pixel of the bullet
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return X coordinate of the bullet
 */
int get_x(Bullet* b);


/**
 * @brief Returns the current y coordinate for the top leftmost pixel of the bullet
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return Y coordinate of the bullet
 */
int get_y(Bullet* b);


/**
 * @brief Tells if the bullet was launched or not
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return True if the bullet was launched, false otherwise
 */
bool get_launched(Bullet* b);


/**
 * @brief Returns the bullet width
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return Width of the bullet object
 */
int get_width(Bullet* b);


/**
 * @brief Returns the bullet height
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return Height of the bullet object
 */
int get_height(Bullet* b);


/**
 * @brief Returns a number regarding the bullet's current image
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return Index of the current bullet image, in the images array
 */
int get_cur_animation(Bullet* b);


/**
 * @brief Returns the current pixmap of the bullet
 * 
 * @param b Pointer to object of type Bullet, that was previously initialized
 * 
 * @return Current active pixmap of the bullet
 */
char* get_current_pixmap(Bullet* b);


/** @} end of Bullet */

#endif
