#ifndef _PROJMACROS_H_
#define _PROJMACROS_H_

//initial cursor position
#define CURSOR_INIT_X_POS    400
#define CURSOR_INIT_Y_POS    300

//title word position
#define TITLE_X_POS             60
#define TITLE_Y_POS             150

//game over word position
#define GAME_OVER_WORD_X_POS    155
#define GAME_OVER_WORD_Y_POS    100


//macros for the gun/aim
#define GUN_X_POS    369
#define GUN_Y_POS    547

#define AIM_X_INIT_POS    370
#define AIM_Y_INIT_POS    450
#define AIM_X_MIN_VAL     200
#define AIM_X_MAX_VAL     600


//macros for the display of the score
#define SCORE_X_VAL             10
#define SCORE_Y_VAL             550
#define SCORE_G_OVER_X_VAL      300
#define SCORE_G_OVER_Y_VAL      270

#define NUM_1ST_X_VAL           110
#define NUM_1ST_Y_VAL           540
#define NUM_1ST_G_OVER_X_VAL    410
#define NUM_1ST_G_OVER_Y_VAL    260

#define NUM_2ND_X_VAL           145
#define NUM_2ND_Y_VAL           540
#define NUM_2ND_G_OVER_X_VAL    445
#define NUM_2ND_G_OVER_Y_VAL    260

#define NUM_3RD_X_VAL           180
#define NUM_3RD_Y_VAL           540
#define NUM_3RD_G_OVER_X_VAL    480
#define NUM_3RD_G_OVER_Y_VAL    260


//initial position for the bullets
#define BULLET_INIT_X_POS    386
#define BULLET_INIT_Y_POS    515

//makecodes of the keys that change the current color of the ammo
#define RED_AMMO_MAKE       0x11  //W key
#define GREEN_AMMO_MAKE     0x1E  //A key
#define BLUE_AMMO_MAKE      0x20  //D key
#define YELLOW_AMMO_MAKE    0x1F  //S key

//macros for the button positions in the main menu
#define SP_BUTTON_X       315
#define SP_BUTTON_Y       350
#define EXIT_BUTTON_X     565
#define EXIT_BUTTON_Y     450
#define HS_BUTTON_X       315
#define HS_BUTTON_Y       450
#define INSTS_BUTTON_X    65
#define INSTS_BUTTON_Y    450

//macros for the button positions in the highscores/instructions
#define BACK_BUTTON_X     20
#define BACK_BUTTON_Y     530

//macros for the button positions in the game over screen
#define P_AGAIN_BUTTON_X  162
#define P_AGAIN_BUTTON_Y  400
#define RET_MM_BUTTON_X   462
#define RET_MM_BUTTON_Y   400


#define ENEMY_X_MIN_VAL    80   //minimum x value for the enemy
#define ENEMY_X_MAX_VAL    720  //maximum x value for the enemy
#define ENEMY_SPAWN_Y      -60  //y coordinate for the spawn point

#define ENEMY_XSPEED_MIN   3    //minimum x speed value for the enemy
#define ENEMY_XSPEED_MAX   6    //maximum x speed value for the enemy

#define ENEMY_YSPEED_INIT  1    //initial y speed value for the enemy
#define ENEMY_Y_LOST       515  //if any enemy has this y value or higher, player loses the game

#define MAX_NUM_SHIPS           15   //maximum number of ships on the screen at the same time
#define MAX_NUM_BULLETS_LB      50   //maximum number of bullets on the screen at the same time, when performing the light beam special atack
#define MAX_NUM_BULLETS_NORMAL  10   //maximum number of bullets on the screen at the same time, in normal mode
#define BULLET_REFRESH_TIME     10 //after launching one bullet, need to wait 10 timer interrupts to launch the next one 
#define INITIAL_SPAWN_RATE  180   //initial spawn rate for the enemy spaceships

#define SHIP_ANIMATION_RATE   5 //number of timer interrupts needed to advance to the next pixmap                                     of the enemy spaceships/explosions

#define BULLET_ANIMATION_RATE 8 //number of timer interrupts needed to advance to the next pixmap                                     of the bullets


#define EMPTY_BAR_X     590 //x position for the light beam progress bar
#define EMPTY_BAR_Y     540 //y position for the light beam progress bar

#define LB_PROG_POINTS  5 //number of points necessary to increase the light beam progress bar by one stage
#define LB_LAUNCH_RATE  2 //in light beam mode, white bullets are launched every 2 interrupts

#define LB_DURATION     3 //light beam mode last 3 seconds (to be multiplied by sys_hz())


//macros for the highscores

#define HS_NUMBER1_X_POS         20
#define HS_NUMBER1_Y_POS         30
#define DAY_FIRST_HS1_X_POS      110
#define DAY_FIRST_HS1_Y_POS      20
#define DAY_SECOND_HS1_X_POS     145
#define DAY_SECOND_HS1_Y_POS     20
#define FIRST_SLASH_HS1_X_POS    170
#define FIRST_SLASH_HS1_Y_POS    15
#define MONTH_FIRST_HS1_X_POS    205
#define MONTH_FIRST_HS1_Y_POS    20
#define MONTH_SECOND_HS1_X_POS   240
#define MONTH_SECOND_HS1_Y_POS   20
#define SECOND_SLASH_HS1_X_POS   270
#define SECOND_SLASH_HS1_Y_POS   15
#define YEAR_FIRST_HS1_X_POS     305
#define YEAR_FIRST_HS1_Y_POS     20
#define YEAR_SECOND_HS1_X_POS    340
#define YEAR_SECOND_HS1_Y_POS    20
#define HOUR_FIRST_HS1_X_POS     400
#define HOUR_FIRST_HS1_Y_POS     20
#define HOUR_SECOND_HS1_X_POS    435
#define HOUR_SECOND_HS1_Y_POS    20
#define TWODOTS_HS1_X_POS        465
#define TWODOTS_HS1_Y_POS        15
#define MINS_FIRST_HS1_X_POS     500
#define MINS_FIRST_HS1_Y_POS     20
#define MINS_SECOND_HS1_X_POS    535
#define MINS_SECOND_HS1_Y_POS    20
#define SCORE_HS1_X_POS          590
#define SCORE_HS1_Y_POS          30
#define FIRST_NUM_HS1_X_POS      690
#define FIRST_NUM_HS1_Y_POS      20
#define SECOND_NUM_HS1_X_POS     725
#define SECOND_NUM_HS1_Y_POS     20
#define THIRD_NUM_HS1_X_POS      760
#define THIRD_NUM_HS1_Y_POS      20

#define HS_NUMBER2_X_POS         20
#define HS_NUMBER2_Y_POS         130
#define DAY_FIRST_HS2_X_POS      110
#define DAY_FIRST_HS2_Y_POS      120
#define DAY_SECOND_HS2_X_POS     145
#define DAY_SECOND_HS2_Y_POS     120
#define FIRST_SLASH_HS2_X_POS    170
#define FIRST_SLASH_HS2_Y_POS    115
#define MONTH_FIRST_HS2_X_POS    205
#define MONTH_FIRST_HS2_Y_POS    120
#define MONTH_SECOND_HS2_X_POS   240
#define MONTH_SECOND_HS2_Y_POS   120
#define SECOND_SLASH_HS2_X_POS   270
#define SECOND_SLASH_HS2_Y_POS   115
#define YEAR_FIRST_HS2_X_POS     305
#define YEAR_FIRST_HS2_Y_POS     120
#define YEAR_SECOND_HS2_X_POS    340
#define YEAR_SECOND_HS2_Y_POS    120
#define HOUR_FIRST_HS2_X_POS     400
#define HOUR_FIRST_HS2_Y_POS     120
#define HOUR_SECOND_HS2_X_POS    435
#define HOUR_SECOND_HS2_Y_POS    120
#define TWODOTS_HS2_X_POS        465
#define TWODOTS_HS2_Y_POS        115
#define MINS_FIRST_HS2_X_POS     500
#define MINS_FIRST_HS2_Y_POS     120
#define MINS_SECOND_HS2_X_POS    535
#define MINS_SECOND_HS2_Y_POS    120
#define SCORE_HS2_X_POS          590
#define SCORE_HS2_Y_POS          130
#define FIRST_NUM_HS2_X_POS      690
#define FIRST_NUM_HS2_Y_POS      120
#define SECOND_NUM_HS2_X_POS     725
#define SECOND_NUM_HS2_Y_POS     120
#define THIRD_NUM_HS2_X_POS      760
#define THIRD_NUM_HS2_Y_POS      120

#define HS_NUMBER3_X_POS         20
#define HS_NUMBER3_Y_POS         230
#define DAY_FIRST_HS3_X_POS      110
#define DAY_FIRST_HS3_Y_POS      220
#define DAY_SECOND_HS3_X_POS     145
#define DAY_SECOND_HS3_Y_POS     220
#define FIRST_SLASH_HS3_X_POS    170
#define FIRST_SLASH_HS3_Y_POS    215
#define MONTH_FIRST_HS3_X_POS    205
#define MONTH_FIRST_HS3_Y_POS    220
#define MONTH_SECOND_HS3_X_POS   240
#define MONTH_SECOND_HS3_Y_POS   220
#define SECOND_SLASH_HS3_X_POS   270
#define SECOND_SLASH_HS3_Y_POS   215
#define YEAR_FIRST_HS3_X_POS     305
#define YEAR_FIRST_HS3_Y_POS     220
#define YEAR_SECOND_HS3_X_POS    340
#define YEAR_SECOND_HS3_Y_POS    220
#define HOUR_FIRST_HS3_X_POS     400
#define HOUR_FIRST_HS3_Y_POS     220
#define HOUR_SECOND_HS3_X_POS    435
#define HOUR_SECOND_HS3_Y_POS    220
#define TWODOTS_HS3_X_POS        465
#define TWODOTS_HS3_Y_POS        215
#define MINS_FIRST_HS3_X_POS     500
#define MINS_FIRST_HS3_Y_POS     220
#define MINS_SECOND_HS3_X_POS    535
#define MINS_SECOND_HS3_Y_POS    220
#define SCORE_HS3_X_POS          590
#define SCORE_HS3_Y_POS          230
#define FIRST_NUM_HS3_X_POS      690
#define FIRST_NUM_HS3_Y_POS      220
#define SECOND_NUM_HS3_X_POS     725
#define SECOND_NUM_HS3_Y_POS     220
#define THIRD_NUM_HS3_X_POS      760
#define THIRD_NUM_HS3_Y_POS      220

#define HS_NUMBER4_X_POS         20
#define HS_NUMBER4_Y_POS         330
#define DAY_FIRST_HS4_X_POS      110
#define DAY_FIRST_HS4_Y_POS      320
#define DAY_SECOND_HS4_X_POS     145
#define DAY_SECOND_HS4_Y_POS     320
#define FIRST_SLASH_HS4_X_POS    170
#define FIRST_SLASH_HS4_Y_POS    315
#define MONTH_FIRST_HS4_X_POS    205
#define MONTH_FIRST_HS4_Y_POS    320
#define MONTH_SECOND_HS4_X_POS   240
#define MONTH_SECOND_HS4_Y_POS   320
#define SECOND_SLASH_HS4_X_POS   270
#define SECOND_SLASH_HS4_Y_POS   315
#define YEAR_FIRST_HS4_X_POS     305
#define YEAR_FIRST_HS4_Y_POS     320
#define YEAR_SECOND_HS4_X_POS    340
#define YEAR_SECOND_HS4_Y_POS    320
#define HOUR_FIRST_HS4_X_POS     400
#define HOUR_FIRST_HS4_Y_POS     320
#define HOUR_SECOND_HS4_X_POS    435
#define HOUR_SECOND_HS4_Y_POS    320
#define TWODOTS_HS4_X_POS        465
#define TWODOTS_HS4_Y_POS        315
#define MINS_FIRST_HS4_X_POS     500
#define MINS_FIRST_HS4_Y_POS     320
#define MINS_SECOND_HS4_X_POS    535
#define MINS_SECOND_HS4_Y_POS    320
#define SCORE_HS4_X_POS          590
#define SCORE_HS4_Y_POS          330
#define FIRST_NUM_HS4_X_POS      690
#define FIRST_NUM_HS4_Y_POS      320
#define SECOND_NUM_HS4_X_POS     725
#define SECOND_NUM_HS4_Y_POS     320
#define THIRD_NUM_HS4_X_POS      760
#define THIRD_NUM_HS4_Y_POS      320

#define HS_NUMBER5_X_POS         20
#define HS_NUMBER5_Y_POS         430
#define DAY_FIRST_HS5_X_POS      110
#define DAY_FIRST_HS5_Y_POS      420
#define DAY_SECOND_HS5_X_POS     145
#define DAY_SECOND_HS5_Y_POS     420
#define FIRST_SLASH_HS5_X_POS    170
#define FIRST_SLASH_HS5_Y_POS    415
#define MONTH_FIRST_HS5_X_POS    205
#define MONTH_FIRST_HS5_Y_POS    420
#define MONTH_SECOND_HS5_X_POS   240
#define MONTH_SECOND_HS5_Y_POS   420
#define SECOND_SLASH_HS5_X_POS   270
#define SECOND_SLASH_HS5_Y_POS   415
#define YEAR_FIRST_HS5_X_POS     305
#define YEAR_FIRST_HS5_Y_POS     420
#define YEAR_SECOND_HS5_X_POS    340
#define YEAR_SECOND_HS5_Y_POS    420
#define HOUR_FIRST_HS5_X_POS     400
#define HOUR_FIRST_HS5_Y_POS     420
#define HOUR_SECOND_HS5_X_POS    435
#define HOUR_SECOND_HS5_Y_POS    420
#define TWODOTS_HS5_X_POS        465
#define TWODOTS_HS5_Y_POS        415
#define MINS_FIRST_HS5_X_POS     500
#define MINS_FIRST_HS5_Y_POS     420
#define MINS_SECOND_HS5_X_POS    535
#define MINS_SECOND_HS5_Y_POS    420
#define SCORE_HS5_X_POS          590
#define SCORE_HS5_Y_POS          430
#define FIRST_NUM_HS5_X_POS      690
#define FIRST_NUM_HS5_Y_POS      420
#define SECOND_NUM_HS5_X_POS     725
#define SECOND_NUM_HS5_Y_POS     420
#define THIRD_NUM_HS5_X_POS      760
#define THIRD_NUM_HS5_Y_POS      420

#endif
