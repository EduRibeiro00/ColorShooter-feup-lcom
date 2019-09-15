#ifndef _BUTTON_H_
#define _BUTTON_H_

/** @defgroup Button Button
 * @{
 * Functions for manipulating an object of type Button
 */

#define BUTTON_ALLOC_FAILED  NULL

struct button_t;
typedef struct button_t Button;


/**
 * @brief Creates a new button object
 * 
 * @param normal XPM representing the normal button
 * @param highlighted XPM representing the highlighted button, when the cursor is over it
 * @param x X coordinate for the button
 * @param y Y coordinate for the button
 * 
 * @return Pointer for object of type Button
 */
Button* create_button(xpm_string_t normal[], xpm_string_t highlighted[], int x, int y);


/**
 * @brief Deletes a button object, freeing all the memory previously allocated
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 */
void delete_button(Button* bt);


/**
 * @brief To call when the cursor is over a button; highlights the button, switching the active pixmap
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 */
void highlight_button(Button* bt);


/**
 * @brief To call when the cursor is not over a certain button; unhighlights the button, switching the active pixmap
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 */
void unhighlight_button(Button* bt);


/**
 * @brief Draws a button on the double buffer
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 */
void draw_button(Button* bt);


/**
 * @brief Gets the x coordinate of the topleft pixel of the button
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 * 
 * @return X coordinate of the button
 */
int get_bt_x(Button* bt);


/**
 * @brief Gets the y coordinate of the topleft pixel of the button
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 * 
 * @return Y coordinate of the button
 */
int get_bt_y(Button* bt);


/**
 * @brief Gets the width of the button
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 * 
 * @return Width of the button
 */
int get_bt_width(Button* bt);


/**
 * @brief Gets the height of the button
 * 
 * @param bt Pointer to object of type Button, that was previously initialized
 * 
 * @return Height of the button
 */
int get_bt_height(Button* bt);


/** @} end of Button */

#endif
