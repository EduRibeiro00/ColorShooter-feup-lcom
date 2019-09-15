#ifndef _HIGHSCORES_H_
#define _HIGHSCORES_H_

#include <stdbool.h>
#include <stdint.h>

/** @defgroup Highscores Highscores
 * @{
 * Functions for manipulating an object of type Highscores, that keeps the highscores of the game and when they were obtained
 */

#define HIGHSCORES_ALLOC_FAILED     NULL

/* struct that keeps the date and time informations */
struct date_t;
typedef struct date_t Date;


struct highscores_t;
typedef struct highscores_t Highscores;


/**
 * @brief Initiates the highscores for the game, reading them from a text file
 * 
 * @return Pointer to object of type Highscores
 */
Highscores* init_highscores();


/**
 * @brief Loads the highscores from a text file
 * 
 * @param hs Pointer to object of type Highscores
 * @param fileName The name of the text file where the highscores are stored
 */
void load_highscores(Highscores* hs, char* fileName);


/**
 * @brief Saves the highscores in a text file
 * 
 * @param hs Pointer to object of type Highscores
 * @param fileName The name of the text file where the highscores are going to be stored
 */
void save_highscores(Highscores* hs, char* fileName);


/**
 * @brief Saves the highscores in a text file, and deletes the highscores, freeing all the memory
 * 
 * @param hs Pointer to object of type Highscores
 */
void delete_highscores(Highscores* hs);


/**
 * @brief Extracts the current date and time from the RTC, for a certain highscore
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore
 */
void extract_date_and_hour(Highscores* hs, int number);


/**
 * @brief Receives a new score, and updates the leaderboard if needed
 * 
 * @param hs Pointer to object of type Highscores
 * @param newScore New score obtained
 */
void update_highscores(Highscores* hs, int newScore);


/**
 * @brief Returns a certain highscore
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore
 * 
 * @return The selected highscore value
 */
int get_highscore(Highscores* hs, int number);


/**
 * @brief Tells if a certain highscore exists
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore 
 * 
 * @return True if the highscore exists, false otherwise
 */
bool get_hs_exists(Highscores* hs, int number);


/**
 * @brief Gets the year in which a certain highscore was obtained
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore
 *  
 * @return The year of the select highscore
 */
uint32_t get_year(Highscores* hs, int number);


/**
 * @brief Gets the month in which a certain highscore was obtained
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore
 *  
 * @return The month of the select highscore
 */
uint32_t get_month(Highscores* hs, int number);


/**
 * @brief Gets the day in which a certain highscore was obtained
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore
 *  
 * @return The day of the select highscore
 */
uint32_t get_day(Highscores* hs, int number);


/**
 * @brief Gets the hour in which a certain highscore was obtained
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore
 *  
 * @return The hour of the select highscore
 */
uint32_t get_hours(Highscores* hs, int number);


/**
 * @brief Gets the minutes in which a certain highscore was obtained
 * 
 * @param hs Pointer to object of type Highscores
 * @param number Number from 1 to 5, indicating the selected highscore
 *  
 * @return The minutes of the select highscore
 */
uint32_t get_minutes(Highscores* hs, int number);


/** @} end of Highscores */

#endif
