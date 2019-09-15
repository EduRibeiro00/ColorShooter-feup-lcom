#ifndef _CURSOR_H_
#define _CURSOR_H_

/** @defgroup Cursor Cursor
 * @{
 * Functions for manipulating an object of type Cursor
 */


//constants
#define CURSOR_ALLOC_FAILED   NULL
#define LB_NOT_PRESSED       0
#define LB_PRESSED           1

struct cursor_t;
typedef struct cursor_t Cursor;


/**
 * @brief Creates a cursor object
 * 
 * @param cursor XPM image of the cursor arrow
 * @param x Initial X coordinate of the cursor
 * @param y Initial Y coordinate of the cursor
 * 
 * @return Pointer to object of type cursor
 */
Cursor* create_cursor(xpm_string_t cursor[], int x, int y);


/**
 * @brief Deletes the cursor object, freeing all the memory previously allocated
 * 
 * @param csr Pointer to object of type Cursor
 */
void delete_cursor(Cursor* csr);


/**
 * @brief Updates the cursor status and position, with the information from the mouse packet
 * 
 * @param csr Pointer to object of type Cursor, that was previously inicialized
 * @param pp Last mouse packet received
 * 
 * @return 0, indicating there was no error
 */
int updateCursor(Cursor* csr, struct packet pp);


/**
 * @brief Draws the cursor on the double buffer, on the right coordinates
 * 
 * @param csr Pointer to object of type Cursor, that was previously inicialized
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int drawCursor(Cursor* csr);


/**
 * @brief Gets the cursor's X coordinate
 * 
 * @param csr Pointer to object of type Cursor, that was previously inicialized
 * 
 * @return The cursor's X coordinate
 */
int get_cursor_x(Cursor* csr);


/**
 * @brief Gets the cursor's Y coordinate
 * 
 * @param csr Pointer to object of type Cursor, that was previously inicialized
 * 
 * @return The cursor's Y coordinate
 */
int get_cursor_y(Cursor* csr);


/**
 * @brief Tells if the left button is being pressed or not
 * 
 * @param csr Pointer to object of type Cursor, that was previously inicialized
 * 
 * @return True if the left button is being pressed, false otherwise
 */
bool get_lb_status(Cursor* csr);


/** @} end of Cursor */

#endif
