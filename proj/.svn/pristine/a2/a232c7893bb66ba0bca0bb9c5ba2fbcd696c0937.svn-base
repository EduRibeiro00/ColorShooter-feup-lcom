#include <lcom/lcf.h>
#include "Game.h"
#include "Cursor.h"
#include "Bullet.h"
#include "Button.h"
#include "video.h"
#include "mouse.h"
#include "keyboard.h"
#include "i8042.h"
#include "i8254.h"
#include "projMacros.h"
#include "xpms.h"
#include "sprite.h"
#include "Ships.h"
#include "Enemy.h"
#include "Highscores.h"
#include "Explosion.h"

#include <stdbool.h>
#include <stdint.h>
#include <minix/sysutil.h>

/* externs of the assembly interrupt handlers */
extern void (kbc_asm_ih)();
extern void timer_asm_ih();
extern void mouse_asm_ih();

/* externs of variables associated with the interrupt handlers */
extern int hook_id;
extern int hook_id_kbd;
extern int hook_id_mouse;

extern uint32_t global_int_counter;
extern uint8_t key_code;
extern uint8_t packet_byte;

extern bool ih_check;
extern bool mouse_ih_check;


struct game_t{

  /* irqs for the subscribed interrupts */
  int irq_set_timer;
  int irq_set_kbd;
  int irq_set_mouse;

  Cursor* cursor; ///< cursor object
  

  Bullet* bullets[MAX_NUM_BULLETS_LB]; ///< bullets array
  int bullets_size; ///< bullets array current size
  int bullets_limit; ///< max number of bullets allowed (will increase when performing the special attack)
  bool enable_fire; ///< true if bullet launching is enabled (cannon not "reloading")
  unsigned bullet_refresh; ///< variable used to keep track of the bullet refresh time


  /* images for the bullets (each color has 5 images, to create an animation) */
  xpm_image_t red_bullets[5];
  xpm_image_t green_bullets[5];
  xpm_image_t blue_bullets[5];
  xpm_image_t yellow_bullets[5];
  xpm_image_t lightBeamBullets[5];

  Color current_ammo; ///< color of the current bullet ammo selected
  int cur_bullet_anim; ///< indicates the current image for the bullet animation
  bool bullet_back; ///< indicates if the order of the bullet images is 0 1 2 3 4 (false) or 4 3 2 1 0 (true)

  int difficulty_level; ///< current difficulty level of the game


  Ships* ships; ///< variable containing all the enemies and explosions

  int lb_progress; ///< current progress of the player to get the light beam special atack
  bool light_beam; ///< true if the light beam special atack is being used
  unsigned light_beam_timer; ///< used to keep track of how much time has passed while the light beam ability is being used


  /* button objects */
  Button* SP_button;
  Button* insts_button;
  Button* hs_button;
  Button* exit_button;
  Button* back_button;
  Button* play_again_button;
  Button* return_mm_button;


  /* word sprites */
  Sprite* title;
  Sprite* gameOver_word;
  Sprite* score;

  /* background sprites */
  Sprite* background;
  Sprite* background_insts;

  int currentIndexForMovBack; ///< current index for the moving background

  /* sprites for the light beam ability progress bars */
  Sprite* lb_empty_bar;
  Sprite* lb_25_bar;
  Sprite* lb_50_bar;
  Sprite* lb_75_bar;
  Sprite* lb_full_bar;

  /* gun (player ship) and aim sprites */
  Sprite* gun;
  Sprite* aim;

  /* sprites for numbers and characters */
  Sprite* zero;
  Sprite* one;
  Sprite* two;
  Sprite* three;
  Sprite* four;
  Sprite* five;
  Sprite* six;
  Sprite* seven;
  Sprite* eight;
  Sprite* nine;
  Sprite* slash;
  Sprite* dois_pontos;
  Sprite* hs_number1;
  Sprite* hs_number2;
  Sprite* hs_number3;
  Sprite* hs_number4;
  Sprite* hs_number5;


  Highscores* highscores; ///< variable encapsulating all the highscores information


  struct packet pp; ///< last mouse packet
  unsigned int currentByte; ///< current byte of the mouse packet


  StateMachines* st; ///< object containing the information about the state machines


  int score_counter; ///< current score of the game
};



Game* start_game(){

  Game* game = (Game*) malloc(sizeof(Game));
  if(game == GAME_ALLOC_FAILED)
    return GAME_ALLOC_FAILED;

  uint8_t bit_no_timer;
  uint8_t bit_no_kbd;
  uint8_t bit_no_mouse;

  uint8_t ackByte;

  if(timer_subscribe_int(&bit_no_timer) != 0)
    return GAME_ALLOC_FAILED;

  if(kbd_subscribe_int(&bit_no_kbd) != 0)
    return GAME_ALLOC_FAILED;

  if(mouse_subscribe_int(&bit_no_mouse) != 0)
    return GAME_ALLOC_FAILED;
  
  game->irq_set_timer = BIT(bit_no_timer);
  game->irq_set_kbd = BIT(bit_no_kbd);
  game->irq_set_mouse = BIT(bit_no_mouse);


  if(sys_irqdisable(&hook_id_mouse) != 0)
    return GAME_ALLOC_FAILED;


  do{
      if( issue_mouse_cmd(ENB_DATA_REP, &ackByte) != 0) //enables data reporting
          return GAME_ALLOC_FAILED;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return GAME_ALLOC_FAILED;
      
  }while(ackByte != ACK);


  if(sys_irqenable(&hook_id_mouse) != 0)
    return GAME_ALLOC_FAILED;



  game->cursor = create_cursor(arrow, CURSOR_INIT_X_POS, CURSOR_INIT_Y_POS);

  game->bullets_size = 0;
  game->bullet_back = false;
  game->cur_bullet_anim = 0;

  game->current_ammo = COLOR_RED; //starts off as red
  game->difficulty_level = 1; //starts off as 1
  game->bullets_limit = MAX_NUM_BULLETS_NORMAL; //starts off in normal mode
  game->enable_fire = true; 
  game->bullet_refresh = 0;

  game->lb_progress = 0;
  game->light_beam = false;
  game->light_beam_timer = 0;

  xpm_image_t img0, img1, img2, img3, img4;

  if(xpm_load(red0_bullet_xpm, XPM_8_8_8, &img0) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(red1_bullet_xpm, XPM_8_8_8, &img1) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(red2_bullet_xpm, XPM_8_8_8, &img2) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(red3_bullet_xpm, XPM_8_8_8, &img3) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(red4_bullet_xpm, XPM_8_8_8, &img4) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  game->red_bullets[0] = img0;
  game->red_bullets[1] = img1;
  game->red_bullets[2] = img2;
  game->red_bullets[3] = img3;
  game->red_bullets[4] = img4;

  if(xpm_load(green0_bullet_xpm, XPM_8_8_8, &img0) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(green1_bullet_xpm, XPM_8_8_8, &img1) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(green2_bullet_xpm, XPM_8_8_8, &img2) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(green3_bullet_xpm, XPM_8_8_8, &img3) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(green4_bullet_xpm, XPM_8_8_8, &img4) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  game->green_bullets[0] = img0;
  game->green_bullets[1] = img1;
  game->green_bullets[2] = img2;
  game->green_bullets[3] = img3;
  game->green_bullets[4] = img4;

  if(xpm_load(blue0_bullet_xpm, XPM_8_8_8, &img0) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(blue1_bullet_xpm, XPM_8_8_8, &img1) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(blue2_bullet_xpm, XPM_8_8_8, &img2) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(blue3_bullet_xpm, XPM_8_8_8, &img3) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(blue4_bullet_xpm, XPM_8_8_8, &img4) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  game->blue_bullets[0] = img0;
  game->blue_bullets[1] = img1;
  game->blue_bullets[2] = img2;
  game->blue_bullets[3] = img3;
  game->blue_bullets[4] = img4;

  if(xpm_load(yellow0_bullet_xpm, XPM_8_8_8, &img0) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(yellow1_bullet_xpm, XPM_8_8_8, &img1) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(yellow2_bullet_xpm, XPM_8_8_8, &img2) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(yellow3_bullet_xpm, XPM_8_8_8, &img3) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(yellow4_bullet_xpm, XPM_8_8_8, &img4) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  game->yellow_bullets[0] = img0;
  game->yellow_bullets[1] = img1;
  game->yellow_bullets[2] = img2;
  game->yellow_bullets[3] = img3;
  game->yellow_bullets[4] = img4;

  if(xpm_load(white0_bullet_xpm, XPM_8_8_8, &img0) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(white1_bullet_xpm, XPM_8_8_8, &img1) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(white2_bullet_xpm, XPM_8_8_8, &img2) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(white3_bullet_xpm, XPM_8_8_8, &img3) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  if(xpm_load(white4_bullet_xpm, XPM_8_8_8, &img4) == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  game->lightBeamBullets[0] = img0;
  game->lightBeamBullets[1] = img1;
  game->lightBeamBullets[2] = img2;
  game->lightBeamBullets[3] = img3;
  game->lightBeamBullets[4] = img4;


  game->ships = create_ships();


  game->SP_button = create_button(button_single_player_xpm, button_single_playerR_xpm, SP_BUTTON_X, SP_BUTTON_Y);
  game->insts_button = create_button(button_instructions_xpm, button_instructionsR_xpm, INSTS_BUTTON_X, INSTS_BUTTON_Y);
  game->hs_button = create_button(button_highscores_xpm, button_highscoresR_xpm, HS_BUTTON_X, HS_BUTTON_Y);
  game->exit_button = create_button(button_exit_xpm, button_exitR_xpm, EXIT_BUTTON_X, EXIT_BUTTON_Y);
  game->back_button = create_button(button_back_xpm, button_backR_xpm, BACK_BUTTON_X, BACK_BUTTON_Y);
  game->play_again_button = create_button(button_play_again_xpm, button_play_againR_xpm, P_AGAIN_BUTTON_X, P_AGAIN_BUTTON_Y);
  game->return_mm_button = create_button(button_main_menu_xpm, button_main_menuR_xpm, RET_MM_BUTTON_X, RET_MM_BUTTON_Y);


  game->title = create_sprite(color_shooter_xpm, TITLE_X_POS, TITLE_Y_POS, 0, 0);
  game->gameOver_word = create_sprite(game_over_word, GAME_OVER_WORD_X_POS, GAME_OVER_WORD_Y_POS, 0, 0);

  game->background = create_sprite(nebula_background, 0, 0, 0, 0);
  game->currentIndexForMovBack = get_st_height(game->background) - 1; //first index

  game->background_insts = create_sprite(final_instructions_xpm, 0, 0, 0, 0);

  game->lb_empty_bar = create_sprite(empty_bar_xpm, EMPTY_BAR_X, EMPTY_BAR_Y, 0, 0);
  game->lb_25_bar = create_sprite(lb_25_prog_bar_xpm, EMPTY_BAR_X, EMPTY_BAR_Y, 0, 0);
  game->lb_50_bar = create_sprite(lb_50_prog_bar_xpm, EMPTY_BAR_X, EMPTY_BAR_Y + 1, 0, 0);
  game->lb_75_bar = create_sprite(lb_75_prog_bar_xpm, EMPTY_BAR_X, EMPTY_BAR_Y, 0, 0);
  game->lb_full_bar = create_sprite(full_bar_xpm, EMPTY_BAR_X, EMPTY_BAR_Y, 0, 0);


  game->gun = create_sprite(player_ship_xpm, GUN_X_POS, GUN_Y_POS, 0, 0);
  game->aim = create_sprite(target_xpm, AIM_X_INIT_POS, AIM_Y_INIT_POS, 0, 0);
  
  game->score = create_sprite(score_white_xpm, SCORE_X_VAL, SCORE_Y_VAL, 0, 0);

  game->zero = create_sprite(zerow_xpm, 0, 0, 0, 0);
  game->one = create_sprite(onew_xpm, 0, 0, 0, 0);
  game->two = create_sprite(twow_xpm, 0, 0, 0, 0);
  game->three = create_sprite(threew_xpm, 0, 0, 0, 0);
  game->four = create_sprite(fourw_xpm, 0, 0, 0, 0);
  game->five = create_sprite(fivew_xpm, 0, 0, 0, 0);
  game->six = create_sprite(sixw_xpm, 0, 0, 0, 0);
  game->seven = create_sprite(sevenw_xpm, 0, 0, 0, 0);
  game->eight = create_sprite(eightw_xpm, 0, 0, 0, 0);
  game->nine = create_sprite(ninew_xpm, 0, 0, 0, 0);
  game->slash = create_sprite(barra_xpm, 0, 0, 0, 0);
  game->dois_pontos = create_sprite(dois_pontos_xpm, 0, 0, 0, 0);

  game->hs_number1 = create_sprite(hs_number1_xpm, HS_NUMBER1_X_POS, HS_NUMBER1_Y_POS, 0, 0);
  game->hs_number2 = create_sprite(hs_number2_xpm, HS_NUMBER2_X_POS, HS_NUMBER2_Y_POS, 0, 0);
  game->hs_number3 = create_sprite(hs_number3_xpm, HS_NUMBER3_X_POS, HS_NUMBER3_Y_POS, 0, 0);
  game->hs_number4 = create_sprite(hs_number4_xpm, HS_NUMBER4_X_POS, HS_NUMBER4_Y_POS, 0, 0);
  game->hs_number5 = create_sprite(hs_number5_xpm, HS_NUMBER5_X_POS, HS_NUMBER5_Y_POS, 0, 0);
  
  //updates the highscores from a text file
  game->highscores = init_highscores();

  game->currentByte = 0;
  game->score_counter = 0;
  
  game->st = create_st_machine();

  return game;
}

//-------------------

void increase_difficulty(Game* g){
  
  adjust_difficulty(g->ships, g->difficulty_level);
  g->difficulty_level++;
}

//-------------------

void handle_difficulty(Game* g){

    if((g->score_counter == 10) && (g->difficulty_level == 1)){
      increase_difficulty(g);
    }

    if((g->score_counter == 20) && (g->difficulty_level == 2)){
      increase_difficulty(g);
    }

    if((g->score_counter == 50) && (g->difficulty_level == 3)){
      increase_difficulty(g);
    }
}

//-------------------

void change_current_ammo(Game* g, uint8_t key_code){
  switch(key_code){

    case RED_AMMO_MAKE:
      g->current_ammo = COLOR_RED;
      break;
    case BLUE_AMMO_MAKE:
      g->current_ammo = COLOR_BLUE;
      break;
    case GREEN_AMMO_MAKE:
      g->current_ammo = COLOR_GREEN;
      break;
    case YELLOW_AMMO_MAKE:
      g->current_ammo = COLOR_YELLOW;
      break;
    default:
      break;
  }
}

//-------------------

void animate_bullets_array(Game* g){

  if(g->cur_bullet_anim == 4)
    g->bullet_back = true;
  
  if(g->cur_bullet_anim == 0)
    g->bullet_back = false;

  if(g->bullet_back)
    g->cur_bullet_anim--;
  else g->cur_bullet_anim++;

  for(int i = 0; i < g->bullets_size; i++)
    animate_bullet(g->bullets[i]);
}

//-------------------

void add_bullet(Game* g){

  if(g->bullets_size == g->bullets_limit)
    return;

  Bullet* newBullet;
  
  if(!g->light_beam){ //if light beam mode is off, creates a normal bullet

      newBullet = create_bullet(g->red_bullets, g->green_bullets, g->blue_bullets, g->yellow_bullets, 5, BULLET_INIT_X_POS, BULLET_INIT_Y_POS, 0, 0, g->current_ammo, g->cur_bullet_anim);
  }
  else{ //else, creates a light beam bullet

      newBullet = create_bullet(g->lightBeamBullets, g->lightBeamBullets,               g->lightBeamBullets, g->lightBeamBullets, 5, BULLET_INIT_X_POS, BULLET_INIT_Y_POS, 0, 0, g->current_ammo, g->cur_bullet_anim);

  }

  g->bullets[g->bullets_size] = newBullet;
  g->bullets_size++;

}

//-------------------

void delete_bullets(Game* g){

  for(int i = 0; i < g->bullets_size; i++){
    delete_bullet(g->bullets[i]);
  }

  g->bullets_size = 0;
}

//-------------------

void draw_bullets(Game* g){

  for(int i = 0; i < g->bullets_size; i++){
    draw_bullet(g->bullets[i]);
  }
}

//-------------------

void remove_bullet(Game* g, int index){

  if(index >= g->bullets_size)
    return;

  for(int i = index; i < g->bullets_size - 1; i++){
    Bullet* temp = g->bullets[i];
    g->bullets[i] = g->bullets[i + 1];
    g->bullets[i + 1] = temp;
  }

  delete_bullet(g->bullets[g->bullets_size - 1]);

  g->bullets_size--;
}

//-------------------

void update_bullets_array(Game* g){

  for(int i = 0; i < g->bullets_size; i++)
    update_bullet_pos(g->bullets[i]);

}

//-------------------

void change_ammo_array(Game* g, uint8_t key_code){

  for(int i = 0; i < g->bullets_size; i++){

    if(!get_launched(g->bullets[i])) //if the bullet was not launched
      change_ammo(g->bullets[i], key_code);
  }
}

//-------------------

void launch_bullet_array(Game* g){

  for(int i = 0; i < g->bullets_size; i++){

    if(!get_launched(g->bullets[i])){ //if the bullet was not launched

      if(!g->light_beam)
        launch_bullet(g->bullets[i], g->aim);
      else launch_bullet_light_beam(g->bullets[i], g->aim);
    }
  }
}

//-------------------

bool check_if_static_bullet(Game* g){

  for(int i = 0; i < g->bullets_size; i++){

    if(!get_launched(g->bullets[i])) //if the bullet was not launched
      return true;
  }

  return false;
}

//-------------------

void remove_oob_bullets(Game* g){

  for(int i = 0; i < g->bullets_size; i++){

    if(bullet_oob(g->bullets[i])){

      remove_bullet(g, i);
      i--;
    }
  }
}

//-------------------

void use_light_beam_ability(Game* g){
  
  g->lb_progress = 0; //light beam progress resets back to 0

  //removes static bullets, if there is any
  for(int i = 0; i < g->bullets_size; i++){
    if(!get_launched(g->bullets[i])){
      remove_bullet(g, i);
      i--;
    }
  }

  g->light_beam = true;
  add_bullet(g); //adds a new white bullet

  g->bullets_limit = MAX_NUM_BULLETS_LB; //number of bullets allowed is increased
  g->light_beam_timer = global_int_counter; //in order to keep track of time
}

//-------------------

void end_light_beam_ability(Game* g){

  g->light_beam = false;
  delete_bullets(g);
  add_bullet(g); //puts a colored bullet on top of the ship
  
  g->bullets_limit = MAX_NUM_BULLETS_NORMAL;
}

//-------------------

void increase_score(Game* g){
  g->score_counter++;
}

//-------------------

void increase_lb_progress(Game* g){
  
  if(g->lb_progress < 4) //else, cannot increase more!
    g->lb_progress++;
}

//-------------------

void kbdManager(Game* g){
  
  if(get_game_state(g->st) == GAME){
    
    if(!g->light_beam){ //if the light beam ability is not being used

      change_current_ammo(g, key_code);
      change_ammo_array(g, key_code);
    }
  }
}

//-------------------

void mouseManager(Game* g){

  if(get_game_state(g->st) == MAIN_MENU){

    updateCursor(g->cursor, g->pp);

    if(mouse_check_clicks(g) == 1){ //single player button
      set_game_event(g->st, START_SP);
      game_event_handler(g->st);
    }
    else if(mouse_check_clicks(g) == 2){ //instructions button
      set_game_event(g->st, GO_INSTS);
      game_event_handler(g->st);
    }
    else if(mouse_check_clicks(g) == 3){ //exit button
      set_game_event(g->st, LEAVE);
      game_event_handler(g->st);
    }
    else if(mouse_check_clicks(g) == 4){ //highscores button
      set_game_event(g->st, GO_HS);
      game_event_handler(g->st);
    }
  }


  if(get_game_state(g->st) == GAME){
    
    update_aim(g->aim, g->pp);

      if(get_player_state(g->st) == PLAY){
    
       if(!g->light_beam){
            if(g->pp.lb){
              if(g->enable_fire){

                  launch_bullet_array(g);
                  add_bullet(g);

                  g->enable_fire = false; //cannon is refreshing
                  g->bullet_refresh = global_int_counter;
              }
            }
       }

         if((g->pp.rb) && (g->lb_progress == 4))
           use_light_beam_ability(g);

      }
  }


  if(get_game_state(g->st) == INSTRUCTIONS){
    updateCursor(g->cursor, g->pp);

    if(mouse_check_clicks(g) == 1){ //back button
      set_game_event(g->st, BACK);
      game_event_handler(g->st);
    }
  }


  if(get_game_state(g->st) == HIGHSCORES){

    updateCursor(g->cursor, g->pp);

    if(mouse_check_clicks(g) == 1){ //back button
      set_game_event(g->st, BACK);
      game_event_handler(g->st);
    }
  }


  if(get_game_state(g->st) == GAME_OVER){

    updateCursor(g->cursor, g->pp);

    if(mouse_check_clicks(g) == 1){ //play again button
      set_game_event(g->st, START_SP);
      game_event_handler(g->st);
    }
    else if(mouse_check_clicks(g) == 2){ //main menu button
      set_game_event(g->st, RETURN_MM);
      game_event_handler(g->st);
    }
  }

}

//-------------------

void timeManager(Game* g){

  if(get_game_state(g->st) == MAIN_MENU){
    highlight_buttons(g);
    update_frame(g);
  }


  if(get_game_state(g->st) == INSTRUCTIONS){
    highlight_buttons(g);
    update_frame(g);
  }


  if(get_game_state(g->st) == HIGHSCORES){
    highlight_buttons(g);
    update_frame(g);
  }


  if(get_game_state(g->st) == GAME_OVER){
    highlight_buttons(g);
    update_frame(g);
  }


  if(get_game_state(g->st) == GAME){

    if(get_player_state(g->st) == NEW_GAME){ //resets everything, for the start of a new game
     
      g->score_counter = 0; //resets score
      global_int_counter = 0;

      delete_bullets(g);

      g->bullets_limit = MAX_NUM_BULLETS_NORMAL;
      g->light_beam = false;

      add_bullet(g); //starts off with a static bullet
      reset_ships(g->ships);

      g->enable_fire = true;
      g->bullet_refresh = 0;
      g->difficulty_level = 1;
      reset_difficulty(g->ships);

      g->lb_progress = 0;
      g->light_beam_timer = 0;

      set_player_event(g->st, START);
      player_event_handler(g->st);

    }
  
    else if(get_player_state(g->st) == PLAY){

      if((global_int_counter % SHIP_ANIMATION_RATE) == 0){
        animate_ships(g->ships); //animates enemies and explosions
      }

      if((global_int_counter % BULLET_ANIMATION_RATE) == 0){
        animate_bullets_array(g); //animates the bullets
      }

      check_all_collisions(g); //checks colisions; adds explosions if enemies were destroyed
      
      //updates the objects positions
      update_bullets_array(g);
      update_ships(g->ships);


      if(!g->enable_fire){

        if(global_int_counter == (g->bullet_refresh + BULLET_REFRESH_TIME)){
          
          g->enable_fire = true; //after a certain period of time, enables fire again
        }
      }


      if(g->light_beam){ //if the special attack is active

        if((global_int_counter % LB_LAUNCH_RATE) == 0){
          launch_bullet_array(g); //keeps launching bullets
          add_bullet(g);
        }

        if(global_int_counter == (g->light_beam_timer + (LB_DURATION * sys_hz()))){
          end_light_beam_ability(g); //after a certain period of time, ends the special attack
        }
      }


      handle_difficulty(g);


      if(((global_int_counter % get_spawn_rate(g->ships)) == 0)){
        add_enemy(g->ships); //from time to time, adds a new enemy
      }


      if((global_int_counter % (sys_hz() / 2)) == 0){
        toggle_move_down(g->ships); //from time to time, tells the enemies to go down
      }

      remove_oob_bullets(g); //removes out of bounds bullets

      if(player_lost(g->ships)){
        global_int_counter = 0;
        set_player_event(g->st, LOST);
        player_event_handler(g->st);
      }
      
    }
  
    else if(get_player_state(g->st) == END){
  
      if((global_int_counter % SHIP_ANIMATION_RATE) == 0){
        animate_ships(g->ships);
      }

      if((global_int_counter % BULLET_ANIMATION_RATE) == 0){
        animate_bullets_array(g);
      }


      if((global_int_counter % (sys_hz() * 2)) == 0){ //waits 2 seconds

        update_highscores(g->highscores, g->score_counter); //updates the highscores accordingly

        set_player_event(g->st, RESET);
        player_event_handler(g->st);

        set_game_event(g->st, GO_GAMEOVER);
        game_event_handler(g->st);
      }
    }

    update_frame(g);
  }  
  

  DBtoVM();
}  
  
//-------------------

void play_game(Game* g){

  int ipc_status;
	message msg;
	int r;
    
   while (get_game_state(g->st) != EXIT) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & g->irq_set_kbd) {
            kbc_asm_ih();

            if (!ih_check)
              return;
           
            kbdManager(g);
          }

          if (msg.m_notify.interrupts & g->irq_set_mouse) {
           mouse_asm_ih();

           if(!mouse_ih_check)
              return;

                if( (g->currentByte == 0) && (!check_if_first_byte(packet_byte)) ){ //if the first byte does not have bit 3 set
                  continue;
                }

                g->pp.bytes[g->currentByte] = packet_byte;
                
                if(g->currentByte == 2)
                  g->currentByte = 0;
                else g->currentByte++;

                if(g->currentByte == 0){  //packet is complete
                  parse_packet(&(g->pp));

                  mouseManager(g);
                }

          }

          if (msg.m_notify.interrupts & g->irq_set_timer) {
             timer_asm_ih();

             timeManager(g);
          }
            break;
            default:
              break;
          }
      }  
    
    }

}

//-------------------

void draw_moving_background(Game* g){

  int index = g->currentIndexForMovBack;

  for(unsigned i = 0; i < get_v_res(); i++){

    char* ptr = get_st_map(g->background) + (index * get_h_res() * get_bytespp());
    copy_line_db(ptr, get_v_res() - i - 1);
    
    index--;
    if(index < 0)
      index = get_st_height(g->background) - 1;
  }

  g->currentIndexForMovBack--;
  if(g->currentIndexForMovBack < 0)
      g->currentIndexForMovBack = get_st_height(g->background) - 1;
}

//-------------------

void draw_background(Game* g){

  if(get_game_state(g->st) == INSTRUCTIONS){
    copy_db(get_st_map(g->background_insts));
  }
  else{
    draw_moving_background(g);
  }
}

//-------------------

Sprite* num_to_sprite(Game* g, int number){

  switch(number){

    case 0:
      return g->zero;
    case 1:
      return g->one;
    case 2:
      return g->two;
    case 3:
      return g->three;
    case 4:
      return g->four;
    case 5:
      return g->five;
    case 6:
      return g->six;
    case 7:
      return g->seven;
    case 8:
      return g->eight;
    case 9:
      return g->nine;
    default:
      return NULL;
  }
}

//-------------------

void display_score(Game* g){

  int firstNum = g->score_counter / 100;
  int secondNum = (g->score_counter % 100) / 10;
  int thirdNum = g->score_counter % 10;

  Sprite* firstSprite = num_to_sprite(g, firstNum);
  Sprite* secondSprite = num_to_sprite(g, secondNum);
  Sprite* thirdSprite = num_to_sprite(g, thirdNum);

  if(get_game_state(g->st) == GAME){

      draw_sprite(g->score);
      draw_sprite_coords(firstSprite, NUM_1ST_X_VAL, NUM_1ST_Y_VAL);
      draw_sprite_coords(secondSprite, NUM_2ND_X_VAL, NUM_2ND_Y_VAL);
      draw_sprite_coords(thirdSprite, NUM_3RD_X_VAL, NUM_3RD_Y_VAL);
  }

  else if(get_game_state(g->st) == GAME_OVER){

      draw_sprite_coords(g->score, SCORE_G_OVER_X_VAL, SCORE_G_OVER_Y_VAL);
      draw_sprite_coords(firstSprite, NUM_1ST_G_OVER_X_VAL, NUM_1ST_G_OVER_Y_VAL);
      draw_sprite_coords(secondSprite, NUM_2ND_G_OVER_X_VAL, NUM_2ND_G_OVER_Y_VAL);
      draw_sprite_coords(thirdSprite, NUM_3RD_G_OVER_X_VAL, NUM_3RD_G_OVER_Y_VAL);
  }

}

//-------------------

void highlight_buttons(Game * g){

  int cursor_x = get_cursor_x(g->cursor);
  int cursor_y = get_cursor_y(g->cursor);

  if(get_game_state(g->st) == MAIN_MENU){

       //for single player button
       if((cursor_x >= get_bt_x(g->SP_button)) && (cursor_x <= (get_bt_x(g->SP_button) + get_bt_width(g->SP_button)))){
         if((cursor_y >= get_bt_y(g->SP_button)) && (cursor_y <= (get_bt_y(g->SP_button) + get_bt_height(g->SP_button)))){
           highlight_button(g->SP_button);
             
         }else unhighlight_button(g->SP_button);
       }else unhighlight_button(g->SP_button);

     
       //for instructions button
       if((cursor_x >= get_bt_x(g->insts_button)) && (cursor_x <= (get_bt_x(g->insts_button) +      get_bt_width(g->insts_button)))){
         if((cursor_y >= get_bt_y(g->insts_button)) && (cursor_y <= (get_bt_y(g->insts_button) +      get_bt_height(g->insts_button)))){
           highlight_button(g->insts_button);
           
         }else unhighlight_button(g->insts_button);
        }else unhighlight_button(g->insts_button);
     
     
       //for exit button
       if((cursor_x >= get_bt_x(g->exit_button)) && (cursor_x <= (get_bt_x(g->exit_button) + get_bt_width(g->exit_button)))){
         if((cursor_y >= get_bt_y(g->exit_button)) && (cursor_y <= (get_bt_y(g->exit_button) +      get_bt_height(g->exit_button)))){
           highlight_button(g->exit_button);
         
         }else unhighlight_button(g->exit_button);
        }else unhighlight_button(g->exit_button);
     

       //for highscores button
       if((cursor_x >= get_bt_x(g->hs_button)) && (cursor_x <= (get_bt_x(g->hs_button) + get_bt_width(g->hs_button)))){
         if((cursor_y >= get_bt_y(g->hs_button)) && (cursor_y <= (get_bt_y(g->hs_button) + get_bt_height(g->hs_button)))){
           highlight_button(g->hs_button);
           
         }else unhighlight_button(g->hs_button);
        }else unhighlight_button(g->hs_button);
       
 
  }

  if(get_game_state(g->st) == INSTRUCTIONS){

       //for back button
       if((cursor_x >= get_bt_x(g->back_button)) && (cursor_x <= (get_bt_x(g->back_button) + get_bt_width(g->back_button)))){
         if((cursor_y >= get_bt_y(g->back_button)) && (cursor_y <= (get_bt_y(g->back_button) +      get_bt_height(g->back_button)))){
           highlight_button(g->back_button);
     
         }else unhighlight_button(g->back_button);
        }else unhighlight_button(g->back_button);


  }


  if(get_game_state(g->st) == HIGHSCORES){

       //for back button
       if((cursor_x >= get_bt_x(g->back_button)) && (cursor_x <= (get_bt_x(g->back_button) + get_bt_width(g->back_button)))){
         if((cursor_y >= get_bt_y(g->back_button)) && (cursor_y <= (get_bt_y(g->back_button) +      get_bt_height(g->back_button)))){
           highlight_button(g->back_button);
         
         }else unhighlight_button(g->back_button);
        }else unhighlight_button(g->back_button);


  }


  if(get_game_state(g->st) == GAME_OVER){

       //for play again button
       if((cursor_x >= get_bt_x(g->play_again_button)) && (cursor_x <= (get_bt_x(g->play_again_button) + get_bt_width(g->play_again_button)))){
         if((cursor_y >= get_bt_y(g->play_again_button)) && (cursor_y <= (get_bt_y(g->play_again_button) + get_bt_height(g->play_again_button)))){
           highlight_button(g->play_again_button);
         
         }else unhighlight_button(g->play_again_button);
        }else unhighlight_button(g->play_again_button);


      //for main menu button
       if((cursor_x >= get_bt_x(g->return_mm_button)) && (cursor_x <= (get_bt_x(g->return_mm_button) + get_bt_width(g->return_mm_button)))){
         if((cursor_y >= get_bt_y(g->return_mm_button)) && (cursor_y <= (get_bt_y(g->return_mm_button) + get_bt_height(g->return_mm_button)))){
           highlight_button(g->return_mm_button);
         
         }else unhighlight_button(g->return_mm_button);
        }else unhighlight_button(g->return_mm_button);

  }


}

//-------------------

int mouse_check_clicks(Game* g){

  int cursor_x = get_cursor_x(g->cursor);
  int cursor_y = get_cursor_y(g->cursor);
  bool click = get_lb_status(g->cursor);

  if(get_game_state(g->st) == MAIN_MENU){

       //for single player button
       if((cursor_x >= get_bt_x(g->SP_button)) && (cursor_x <= (get_bt_x(g->SP_button) + get_bt_width(g->SP_button))))
         if((cursor_y >= get_bt_y(g->SP_button)) && (cursor_y <= (get_bt_y(g->SP_button) + get_bt_height(g->SP_button))))
            if(click)
              return 1;

     
       //for instructions button
       if((cursor_x >= get_bt_x(g->insts_button)) && (cursor_x <= (get_bt_x(g->insts_button) + get_bt_width(g->insts_button))))
         if((cursor_y >= get_bt_y(g->insts_button)) && (cursor_y <= (get_bt_y(g->insts_button) + get_bt_height(g->insts_button))))
            if(click)
              return 2;
     

       //for exit button
       if((cursor_x >= get_bt_x(g->exit_button)) && (cursor_x <= (get_bt_x(g->exit_button) + get_bt_width(g->exit_button))))
         if((cursor_y >= get_bt_y(g->exit_button)) && (cursor_y <= (get_bt_y(g->exit_button) + get_bt_height(g->exit_button))))
            if(click)
              return 3;


       //for highscores button
       if((cursor_x >= get_bt_x(g->hs_button)) && (cursor_x <= (get_bt_x(g->hs_button) + get_bt_width(g->hs_button))))
         if((cursor_y >= get_bt_y(g->hs_button)) && (cursor_y <= (get_bt_y(g->hs_button) + get_bt_height(g->hs_button))))
            if(click)
              return 4;


       return 0; //mouse not clicking in any button
  }

  if(get_game_state(g->st) == INSTRUCTIONS){

       //for back button
       if((cursor_x >= get_bt_x(g->back_button)) && (cursor_x <= (get_bt_x(g->back_button) + get_bt_width(g->back_button))))
         if((cursor_y >= get_bt_y(g->back_button)) && (cursor_y <= (get_bt_y(g->back_button) + get_bt_height(g->back_button))))
            if(click)
              return 1;


      return 0; //mouse not clicking in any button 
  }


  if(get_game_state(g->st)== HIGHSCORES){

       //for back button
       if((cursor_x >= get_bt_x(g->back_button)) && (cursor_x <= (get_bt_x(g->back_button) + get_bt_width(g->back_button))))
         if((cursor_y >= get_bt_y(g->back_button)) && (cursor_y <= (get_bt_y(g->back_button) + get_bt_height(g->back_button))))
            if(click)
              return 1;


      return 0; //mouse not clicking in any button 
  }


  if(get_game_state(g->st) == GAME_OVER){

       //for play again button
       if((cursor_x >= get_bt_x(g->play_again_button)) && (cursor_x <= (get_bt_x(g->play_again_button) + get_bt_width(g->play_again_button))))
         if((cursor_y >= get_bt_y(g->play_again_button)) && (cursor_y <= (get_bt_y(g->play_again_button) + get_bt_height(g->play_again_button))))
            if(click)
              return 1;


       //for main menu button
       if((cursor_x >= get_bt_x(g->return_mm_button)) && (cursor_x <= (get_bt_x(g->return_mm_button) + get_bt_width(g->return_mm_button))))
         if((cursor_y >= get_bt_y(g->return_mm_button)) && (cursor_y <= (get_bt_y(g->return_mm_button) + get_bt_height(g->return_mm_button))))
            if(click)
              return 2;


      return 0; //mouse not clicking in any button 
  }


  return 0;
}

//-------------------

int check_pixmap_collision(Bullet* b, Enemy* enemy){

  //verifies if the sprite "rectangles" are one on top of the other (overlaped)

  if((get_x(b) >= get_enemy_x(enemy)) && (get_x(b) <= (get_enemy_x(enemy) + get_enemy_width(enemy)))){
    if((get_y(b) >= get_enemy_y(enemy)) && (get_y(b) <= (get_enemy_y(enemy) + get_enemy_height(enemy)))){
      return 1;
    }else{
      
      if(((get_y(b) + get_height(b)) >= get_enemy_y(enemy)) && ((get_y(b) + get_height(b)) <= (get_enemy_y(enemy) + get_enemy_height(enemy)))){
      return 1;
      }
    }
  }


  if(((get_x(b) + get_width(b)) >= get_enemy_x(enemy)) && ((get_x(b)+ get_width(b)) <= (get_enemy_x(enemy) + get_enemy_width(enemy)))){
    if((get_y(b) >= get_enemy_y(enemy)) && (get_y(b) <= (get_enemy_y(enemy) + get_enemy_height(enemy)))){
      return 1;
    }else{
      
      if(((get_y(b)+ get_height(b)) >= get_enemy_y(enemy)) && ((get_y(b) + get_height(b)) <= (get_enemy_y(enemy)+ get_enemy_height(enemy)))){
        return 1;
      }
    }
  }

  return 0; //there was no collision
}

//-------------------

int check_pixel_collision(Bullet* b, Enemy* enemy){

    char* bulletPixmap = get_current_pixmap(b);

    char* enemyPixmap = get_enemy_current_pixmap(enemy);


    if(get_x(b) >= get_enemy_x(enemy)){ //bullet is the sprite in the right or level with the enemy

       if(get_y(b) >= get_enemy_y(enemy)){ //bullet is in the right, and below or level with the enemy

            int x_rel = get_x(b) - get_enemy_x(enemy); //first x position for the enemy pixmap
            int y_rel = get_y(b) - get_enemy_y(enemy); //first y position for the enemy pixmap


            int x_limit, y_limit;

            if((get_enemy_x(enemy) + get_enemy_width(enemy)) > (get_x(b) + get_width(b)))
              x_limit = get_width(b);
            else x_limit = get_enemy_width(enemy) - (get_x(b) - get_enemy_x(enemy));

            if((get_enemy_y(enemy) + get_enemy_height(enemy)) > (get_y(b) + get_height(b)))
              y_limit = get_height(b);
            else y_limit = get_enemy_height(enemy) - (get_y(b) - get_enemy_y(enemy));



            for(int j = 0; j < y_limit; j++){
              for(int i = 0; i < x_limit; i++){

                //if both corresponding pixels are not transparent, then there was an actual collision
                if((!check_pixel_transp(bulletPixmap, i, j, get_width(b))) && (!check_pixel_transp(enemyPixmap, x_rel + i, y_rel + j, get_enemy_width(enemy))))
                  return 1;
              }
            }

            return 0; //no actual collision
       
       }
       else{ //bullet is in the right, and above the enemy

         int x_rel = get_x(b) - get_enemy_x(enemy); //first x position for the enemy pixmap
         int y_rel = get_enemy_y(enemy) - get_y(b); //first y position for the bullet pixmap

            int x_limit, y_limit;

            if((get_enemy_x(enemy) + get_enemy_width(enemy)) > (get_x(b) + get_width(b)))
              x_limit = get_width(b);
            else x_limit = get_enemy_width(enemy) - (get_x(b) - get_enemy_x(enemy));

            y_limit = (get_y(b) + get_height(b)) - get_enemy_y(enemy);


          for(int j = 0; j < y_limit; j++){
              for(int i = 0; i < x_limit; i++){

                //if both corresponding pixels are not transparent, then there was an actual collision
                if((!check_pixel_transp(bulletPixmap, i, j + y_rel, get_width(b))) && (!check_pixel_transp(enemyPixmap, x_rel + i, j, get_enemy_width(enemy))))
                  return 1;
              }
            }

            return 0; //no actual collision

       }

    }


    else{ //bullet is the sprite in the left



      if(get_y(b) >= get_enemy_y(enemy)){ //bullet is in the left, and below or even with the enemy

        int x_rel = get_enemy_x(enemy) - get_x(b); //first x position for the bullet pixmap
        int y_rel = get_y(b) - get_enemy_y(enemy); //first y position for the enemy pixmap

            int x_limit, y_limit;

            x_limit = (get_x(b) + get_width(b)) - get_enemy_x(enemy);

            if((get_enemy_y(enemy) + get_enemy_height(enemy)) > (get_y(b) + get_height(b)))
              y_limit = get_height(b);
            else y_limit = get_enemy_height(enemy) - (get_y(b) - get_enemy_y(enemy));


        for(int j = 0; j < y_limit; j++){
            for(int i = 0; i < x_limit; i++){

                //if both corresponding pixels are not transparent, then there was an actual collision
                if((!check_pixel_transp(bulletPixmap, i + x_rel, j, get_width(b))) && (!check_pixel_transp(enemyPixmap, i, j + y_rel, get_enemy_width(enemy))))
                  return 1;
            }
          }

          return 0; //no actual collision

       }

       else{ //bullet is in the left, and above the obstacle

        int x_rel = get_enemy_x(enemy) - get_x(b); //first x position for the bullet pixmap
        int y_rel = get_enemy_y(enemy) - get_y(b); //first y position for the bullet pixmap

          int x_limit, y_limit;

            x_limit = (get_x(b) + get_width(b)) - get_enemy_x(enemy);

            y_limit = (get_y(b) + get_height(b)) - get_enemy_y(enemy);


        for(int j = 0; j < y_limit; j++){
            for(int i = 0; i < x_limit; i++){

                //if both corresponding pixels are not transparent, then there was an actual collision
                if((!check_pixel_transp(bulletPixmap, i + x_rel, j + y_rel, get_width(b))) && (!check_pixel_transp(enemyPixmap, i, j, get_enemy_width(enemy))))
                  return 1;
           }
         }

          return 0; //no actual collision

       }

    }


}

//-------------------

bool check_ship_collisions(Game* g, Enemy* enemy){

  bool shipDestroyed = false; //is going to be set, if the ship needs to be destroyed (removed from the array)


  for(int j = 0; j < g->bullets_size; j++){  //checks collisions for each bullet

        if(get_launched(g->bullets[j])){

          if(check_pixmap_collision(g->bullets[j], enemy) == 1){
            if(check_pixel_collision(g->bullets[j], enemy) == 1){

              if(g->light_beam){

                  shipDestroyed = true;
                  increase_score(g);

                  remove_bullet(g, j); //there was collision, bullet needs to be removed from the array
                  j--;


              }else{
                    
                    if(get_enemy_color(enemy) == get_bullet_color(g->bullets[j])){ //spaceship hit has the same color as the bullet

                        shipDestroyed = true;
                        increase_score(g);

                        if((g->score_counter % LB_PROG_POINTS) == 0){
                            increase_lb_progress(g);
                        }

                      }

                    remove_bullet(g, j); //there was collision, bullet needs to be removed from the array
                    j--;

                  }
              }
          
            }

        }
          
  }

  return shipDestroyed;
}

//-------------------

void check_all_collisions(Game * g){

    Enemy** array = get_enemies(g->ships); //gets the enemies array


    for(int i = 0; i < get_enemies_size(g->ships); i++){

        if(check_ship_collisions(g, array[i])){ //if enemy was destroyed...

          //creates an explosion, in the right place
          add_explosion(g->ships, get_enemy_x(array[i]) - 8, get_enemy_y(array[i]) - 3);

          //removes the ship from the array
          remove_ship(g->ships, i);
          i--;
        }

    }
}

//-------------------

void display_highscores(Game* g){

  draw_sprite(g->hs_number1);
  draw_sprite(g->hs_number2);
  draw_sprite(g->hs_number3);
  draw_sprite(g->hs_number4);
  draw_sprite(g->hs_number5);


  if(get_hs_exists(g->highscores, 1)){

    Sprite* digit1_year = num_to_sprite(g, (int)get_year(g->highscores, 1) / 10);
    Sprite* digit2_year = num_to_sprite(g, (int)get_year(g->highscores, 1) % 10);
    Sprite* digit1_month = num_to_sprite(g, (int)get_month(g->highscores, 1) / 10);
    Sprite* digit2_month = num_to_sprite(g, (int)get_month(g->highscores, 1) % 10);
    Sprite* digit1_day = num_to_sprite(g, (int)get_day(g->highscores, 1) / 10);
    Sprite* digit2_day = num_to_sprite(g, (int)get_day(g->highscores, 1) % 10);
    Sprite* digit1_hour = num_to_sprite(g, (int)get_hours(g->highscores, 1)  / 10);
    Sprite* digit2_hour = num_to_sprite(g, (int)get_hours(g->highscores, 1) % 10);
    Sprite* digit1_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 1) / 10);
    Sprite* digit2_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 1) % 10);

    draw_sprite_coords(digit1_year, YEAR_FIRST_HS1_X_POS, YEAR_FIRST_HS1_Y_POS);
    draw_sprite_coords(digit2_year, YEAR_SECOND_HS1_X_POS, YEAR_SECOND_HS1_Y_POS);
    draw_sprite_coords(g->slash, FIRST_SLASH_HS1_X_POS, FIRST_SLASH_HS1_Y_POS);
    draw_sprite_coords(digit1_month, MONTH_FIRST_HS1_X_POS, MONTH_FIRST_HS1_Y_POS);
    draw_sprite_coords(digit2_month, MONTH_SECOND_HS1_X_POS, MONTH_SECOND_HS1_Y_POS);
    draw_sprite_coords(g->slash, SECOND_SLASH_HS1_X_POS, SECOND_SLASH_HS1_Y_POS);
    draw_sprite_coords(digit1_day, DAY_FIRST_HS1_X_POS, DAY_FIRST_HS1_Y_POS);
    draw_sprite_coords(digit2_day, DAY_SECOND_HS1_X_POS, DAY_SECOND_HS1_Y_POS);
    draw_sprite_coords(digit1_hour, HOUR_FIRST_HS1_X_POS, HOUR_FIRST_HS1_Y_POS);
    draw_sprite_coords(digit2_hour, HOUR_SECOND_HS1_X_POS, HOUR_SECOND_HS1_Y_POS);
    draw_sprite_coords(g->dois_pontos, TWODOTS_HS1_X_POS, TWODOTS_HS1_Y_POS);
    draw_sprite_coords(digit1_mins, MINS_FIRST_HS1_X_POS, MINS_FIRST_HS1_Y_POS);
    draw_sprite_coords(digit2_mins, MINS_SECOND_HS1_X_POS, MINS_SECOND_HS1_Y_POS);

    draw_sprite_coords(g->score, SCORE_HS1_X_POS, SCORE_HS1_Y_POS);
    
    int firstNum = get_highscore(g->highscores, 1) / 100;
    int secondNum = (get_highscore(g->highscores, 1) % 100) / 10;
    int thirdNum = get_highscore(g->highscores, 1) % 10;

    Sprite* firstSprite = num_to_sprite(g, firstNum);
    Sprite* secondSprite = num_to_sprite(g, secondNum);
    Sprite* thirdSprite = num_to_sprite(g, thirdNum);

    draw_sprite_coords(firstSprite, FIRST_NUM_HS1_X_POS, FIRST_NUM_HS1_Y_POS);
    draw_sprite_coords(secondSprite, SECOND_NUM_HS1_X_POS, SECOND_NUM_HS1_Y_POS);
    draw_sprite_coords(thirdSprite, THIRD_NUM_HS1_X_POS, THIRD_NUM_HS1_Y_POS);
  }


  if(get_hs_exists(g->highscores, 2)){

    Sprite* digit1_year = num_to_sprite(g, (int)get_year(g->highscores, 2) / 10);
    Sprite* digit2_year = num_to_sprite(g, (int)get_year(g->highscores, 2) % 10);
    Sprite* digit1_month = num_to_sprite(g, (int)get_month(g->highscores, 2) / 10);
    Sprite* digit2_month = num_to_sprite(g, (int)get_month(g->highscores, 2) % 10);
    Sprite* digit1_day = num_to_sprite(g, (int)get_day(g->highscores, 2) / 10);
    Sprite* digit2_day = num_to_sprite(g, (int)get_day(g->highscores, 2) % 10);
    Sprite* digit1_hour = num_to_sprite(g, (int)get_hours(g->highscores, 2) / 10);
    Sprite* digit2_hour = num_to_sprite(g, (int)get_hours(g->highscores, 2) % 10);
    Sprite* digit1_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 2) / 10);
    Sprite* digit2_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 2) % 10);

    draw_sprite_coords(digit1_year, YEAR_FIRST_HS2_X_POS, YEAR_FIRST_HS2_Y_POS);
    draw_sprite_coords(digit2_year, YEAR_SECOND_HS2_X_POS, YEAR_SECOND_HS2_Y_POS);
    draw_sprite_coords(g->slash, FIRST_SLASH_HS2_X_POS, FIRST_SLASH_HS2_Y_POS);
    draw_sprite_coords(digit1_month, MONTH_FIRST_HS2_X_POS, MONTH_FIRST_HS2_Y_POS);
    draw_sprite_coords(digit2_month, MONTH_SECOND_HS2_X_POS, MONTH_SECOND_HS2_Y_POS);
    draw_sprite_coords(g->slash, SECOND_SLASH_HS2_X_POS, SECOND_SLASH_HS2_Y_POS);
    draw_sprite_coords(digit1_day, DAY_FIRST_HS2_X_POS, DAY_FIRST_HS2_Y_POS);
    draw_sprite_coords(digit2_day, DAY_SECOND_HS2_X_POS, DAY_SECOND_HS2_Y_POS);
    draw_sprite_coords(digit1_hour, HOUR_FIRST_HS2_X_POS, HOUR_FIRST_HS2_Y_POS);
    draw_sprite_coords(digit2_hour, HOUR_SECOND_HS2_X_POS, HOUR_SECOND_HS2_Y_POS);
    draw_sprite_coords(g->dois_pontos, TWODOTS_HS2_X_POS, TWODOTS_HS2_Y_POS);
    draw_sprite_coords(digit1_mins, MINS_FIRST_HS2_X_POS, MINS_FIRST_HS2_Y_POS);
    draw_sprite_coords(digit2_mins, MINS_SECOND_HS2_X_POS, MINS_SECOND_HS2_Y_POS);

    draw_sprite_coords(g->score, SCORE_HS2_X_POS, SCORE_HS2_Y_POS);
    
    int firstNum = get_highscore(g->highscores, 2) / 100;
    int secondNum = (get_highscore(g->highscores, 2) % 100) / 10;
    int thirdNum = get_highscore(g->highscores, 2) % 10;

    Sprite* firstSprite = num_to_sprite(g, firstNum);
    Sprite* secondSprite = num_to_sprite(g, secondNum);
    Sprite* thirdSprite = num_to_sprite(g, thirdNum);

    draw_sprite_coords(firstSprite, FIRST_NUM_HS2_X_POS, FIRST_NUM_HS2_Y_POS);
    draw_sprite_coords(secondSprite, SECOND_NUM_HS2_X_POS, SECOND_NUM_HS2_Y_POS);
    draw_sprite_coords(thirdSprite, THIRD_NUM_HS2_X_POS, THIRD_NUM_HS2_Y_POS);
  }


  if(get_hs_exists(g->highscores, 3)){

    Sprite* digit1_year = num_to_sprite(g, (int)get_year(g->highscores, 3) / 10);
    Sprite* digit2_year = num_to_sprite(g, (int)get_year(g->highscores, 3) % 10);
    Sprite* digit1_month = num_to_sprite(g, (int)get_month(g->highscores, 3) / 10);
    Sprite* digit2_month = num_to_sprite(g, (int)get_month(g->highscores, 3) % 10);
    Sprite* digit1_day = num_to_sprite(g, (int)get_day(g->highscores, 3) / 10);
    Sprite* digit2_day = num_to_sprite(g, (int)get_day(g->highscores, 3) % 10);
    Sprite* digit1_hour = num_to_sprite(g, (int)get_hours(g->highscores, 3) / 10);
    Sprite* digit2_hour = num_to_sprite(g, (int)get_hours(g->highscores, 3) % 10);
    Sprite* digit1_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 3) / 10);
    Sprite* digit2_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 3) % 10);

    draw_sprite_coords(digit1_year, YEAR_FIRST_HS3_X_POS, YEAR_FIRST_HS3_Y_POS);
    draw_sprite_coords(digit2_year, YEAR_SECOND_HS3_X_POS, YEAR_SECOND_HS3_Y_POS);
    draw_sprite_coords(g->slash, FIRST_SLASH_HS3_X_POS, FIRST_SLASH_HS3_Y_POS);
    draw_sprite_coords(digit1_month, MONTH_FIRST_HS3_X_POS, MONTH_FIRST_HS3_Y_POS);
    draw_sprite_coords(digit2_month, MONTH_SECOND_HS3_X_POS, MONTH_SECOND_HS3_Y_POS);
    draw_sprite_coords(g->slash, SECOND_SLASH_HS3_X_POS, SECOND_SLASH_HS3_Y_POS);
    draw_sprite_coords(digit1_day, DAY_FIRST_HS3_X_POS, DAY_FIRST_HS3_Y_POS);
    draw_sprite_coords(digit2_day, DAY_SECOND_HS3_X_POS, DAY_SECOND_HS3_Y_POS);
    draw_sprite_coords(digit1_hour, HOUR_FIRST_HS3_X_POS, HOUR_FIRST_HS3_Y_POS);
    draw_sprite_coords(digit2_hour, HOUR_SECOND_HS3_X_POS, HOUR_SECOND_HS3_Y_POS);
    draw_sprite_coords(g->dois_pontos, TWODOTS_HS3_X_POS, TWODOTS_HS3_Y_POS);
    draw_sprite_coords(digit1_mins, MINS_FIRST_HS3_X_POS, MINS_FIRST_HS3_Y_POS);
    draw_sprite_coords(digit2_mins, MINS_SECOND_HS3_X_POS, MINS_SECOND_HS3_Y_POS);
    
    draw_sprite_coords(g->score, SCORE_HS3_X_POS, SCORE_HS3_Y_POS);
    
    int firstNum = get_highscore(g->highscores, 3) / 100;
    int secondNum = (get_highscore(g->highscores, 3) % 100) / 10;
    int thirdNum = get_highscore(g->highscores, 3) % 10;

    Sprite* firstSprite = num_to_sprite(g, firstNum);
    Sprite* secondSprite = num_to_sprite(g, secondNum);
    Sprite* thirdSprite = num_to_sprite(g, thirdNum);

    draw_sprite_coords(firstSprite, FIRST_NUM_HS3_X_POS, FIRST_NUM_HS3_Y_POS);
    draw_sprite_coords(secondSprite, SECOND_NUM_HS3_X_POS, SECOND_NUM_HS3_Y_POS);
    draw_sprite_coords(thirdSprite, THIRD_NUM_HS3_X_POS, THIRD_NUM_HS3_Y_POS);
  }


  if(get_hs_exists(g->highscores, 4)){

    Sprite* digit1_year = num_to_sprite(g, (int)get_year(g->highscores, 4) / 10);
    Sprite* digit2_year = num_to_sprite(g, (int)get_year(g->highscores, 4) % 10);
    Sprite* digit1_month = num_to_sprite(g, (int)get_month(g->highscores, 4) / 10);
    Sprite* digit2_month = num_to_sprite(g, (int)get_month(g->highscores, 4) % 10);
    Sprite* digit1_day = num_to_sprite(g, (int)get_day(g->highscores, 4) / 10);
    Sprite* digit2_day = num_to_sprite(g, (int)get_day(g->highscores, 4) % 10);
    Sprite* digit1_hour = num_to_sprite(g, (int)get_hours(g->highscores, 4) / 10);
    Sprite* digit2_hour = num_to_sprite(g, (int)get_hours(g->highscores, 4) % 10);
    Sprite* digit1_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 4) / 10);
    Sprite* digit2_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 4) % 10);

    draw_sprite_coords(digit1_year, YEAR_FIRST_HS4_X_POS, YEAR_FIRST_HS4_Y_POS);
    draw_sprite_coords(digit2_year, YEAR_SECOND_HS4_X_POS, YEAR_SECOND_HS4_Y_POS);
    draw_sprite_coords(g->slash, FIRST_SLASH_HS4_X_POS, FIRST_SLASH_HS4_Y_POS);
    draw_sprite_coords(digit1_month, MONTH_FIRST_HS4_X_POS, MONTH_FIRST_HS4_Y_POS);
    draw_sprite_coords(digit2_month, MONTH_SECOND_HS4_X_POS, MONTH_SECOND_HS4_Y_POS);
    draw_sprite_coords(g->slash, SECOND_SLASH_HS4_X_POS, SECOND_SLASH_HS4_Y_POS);
    draw_sprite_coords(digit1_day, DAY_FIRST_HS4_X_POS, DAY_FIRST_HS4_Y_POS);
    draw_sprite_coords(digit2_day, DAY_SECOND_HS4_X_POS, DAY_SECOND_HS4_Y_POS);
    draw_sprite_coords(digit1_hour, HOUR_FIRST_HS4_X_POS, HOUR_FIRST_HS4_Y_POS);
    draw_sprite_coords(digit2_hour, HOUR_SECOND_HS4_X_POS, HOUR_SECOND_HS4_Y_POS);
    draw_sprite_coords(g->dois_pontos, TWODOTS_HS4_X_POS, TWODOTS_HS4_Y_POS);
    draw_sprite_coords(digit1_mins, MINS_FIRST_HS4_X_POS, MINS_FIRST_HS4_Y_POS);
    draw_sprite_coords(digit2_mins, MINS_SECOND_HS4_X_POS, MINS_SECOND_HS4_Y_POS);
    
    draw_sprite_coords(g->score, SCORE_HS4_X_POS, SCORE_HS4_Y_POS);
    
    int firstNum = get_highscore(g->highscores, 4) / 100;
    int secondNum = (get_highscore(g->highscores, 4) % 100) / 10;
    int thirdNum = get_highscore(g->highscores, 4) % 10;

    Sprite* firstSprite = num_to_sprite(g, firstNum);
    Sprite* secondSprite = num_to_sprite(g, secondNum);
    Sprite* thirdSprite = num_to_sprite(g, thirdNum);

    draw_sprite_coords(firstSprite, FIRST_NUM_HS4_X_POS, FIRST_NUM_HS4_Y_POS);
    draw_sprite_coords(secondSprite, SECOND_NUM_HS4_X_POS, SECOND_NUM_HS4_Y_POS);
    draw_sprite_coords(thirdSprite, THIRD_NUM_HS4_X_POS, THIRD_NUM_HS4_Y_POS);
  }


  if(get_hs_exists(g->highscores, 5)){

    Sprite* digit1_year = num_to_sprite(g, (int)get_year(g->highscores, 5) / 10);
    Sprite* digit2_year = num_to_sprite(g, (int)get_year(g->highscores, 5) % 10);
    Sprite* digit1_month = num_to_sprite(g, (int)get_month(g->highscores, 5) / 10);
    Sprite* digit2_month = num_to_sprite(g, (int)get_month(g->highscores, 5) % 10);
    Sprite* digit1_day = num_to_sprite(g, (int)get_day(g->highscores, 5) / 10);
    Sprite* digit2_day = num_to_sprite(g, (int)get_day(g->highscores, 5) % 10);
    Sprite* digit1_hour = num_to_sprite(g, (int)get_hours(g->highscores, 5) / 10);
    Sprite* digit2_hour = num_to_sprite(g, (int)get_hours(g->highscores, 5) % 10);
    Sprite* digit1_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 5) / 10);
    Sprite* digit2_mins = num_to_sprite(g, (int)get_minutes(g->highscores, 5) % 10);

    draw_sprite_coords(digit1_year, YEAR_FIRST_HS5_X_POS, YEAR_FIRST_HS5_Y_POS);
    draw_sprite_coords(digit2_year, YEAR_SECOND_HS5_X_POS, YEAR_SECOND_HS5_Y_POS);
    draw_sprite_coords(g->slash, FIRST_SLASH_HS5_X_POS, FIRST_SLASH_HS5_Y_POS);
    draw_sprite_coords(digit1_month, MONTH_FIRST_HS5_X_POS, MONTH_FIRST_HS5_Y_POS);
    draw_sprite_coords(digit2_month, MONTH_SECOND_HS5_X_POS, MONTH_SECOND_HS5_Y_POS);
    draw_sprite_coords(g->slash, SECOND_SLASH_HS5_X_POS, SECOND_SLASH_HS5_Y_POS);
    draw_sprite_coords(digit1_day, DAY_FIRST_HS5_X_POS, DAY_FIRST_HS5_Y_POS);
    draw_sprite_coords(digit2_day, DAY_SECOND_HS5_X_POS, DAY_SECOND_HS5_Y_POS);
    draw_sprite_coords(digit1_hour, HOUR_FIRST_HS5_X_POS, HOUR_FIRST_HS5_Y_POS);
    draw_sprite_coords(digit2_hour, HOUR_SECOND_HS5_X_POS, HOUR_SECOND_HS5_Y_POS);
    draw_sprite_coords(g->dois_pontos, TWODOTS_HS5_X_POS, TWODOTS_HS5_Y_POS);
    draw_sprite_coords(digit1_mins, MINS_FIRST_HS5_X_POS, MINS_FIRST_HS5_Y_POS);
    draw_sprite_coords(digit2_mins, MINS_SECOND_HS5_X_POS, MINS_SECOND_HS5_Y_POS);
    
    draw_sprite_coords(g->score, SCORE_HS5_X_POS, SCORE_HS5_Y_POS);
    
    int firstNum = get_highscore(g->highscores, 5) / 100;
    int secondNum = (get_highscore(g->highscores, 5) % 100) / 10;
    int thirdNum = get_highscore(g->highscores, 5) % 10;

    Sprite* firstSprite = num_to_sprite(g, firstNum);
    Sprite* secondSprite = num_to_sprite(g, secondNum);
    Sprite* thirdSprite = num_to_sprite(g, thirdNum);

    draw_sprite_coords(firstSprite, FIRST_NUM_HS5_X_POS, FIRST_NUM_HS5_Y_POS);
    draw_sprite_coords(secondSprite, SECOND_NUM_HS5_X_POS, SECOND_NUM_HS5_Y_POS);
    draw_sprite_coords(thirdSprite, THIRD_NUM_HS5_X_POS, THIRD_NUM_HS5_Y_POS);
  }
}

//-------------------

void update_frame(Game* g){

  if(get_game_state(g->st) == MAIN_MENU){
    draw_background(g);
    draw_sprite(g->title);
    draw_button(g->SP_button);
    draw_button(g->hs_button);
    draw_button(g->insts_button);
    draw_button(g->exit_button);
    drawCursor(g->cursor);
  }


  if(get_game_state(g->st) == HIGHSCORES){
    draw_background(g);
    draw_button(g->back_button);
    display_highscores(g);
    drawCursor(g->cursor);
  }


  if(get_game_state(g->st) == INSTRUCTIONS){
    draw_background(g);
    draw_button(g->back_button);
    drawCursor(g->cursor);
  }


  if(get_game_state(g->st) == GAME_OVER){
    draw_background(g);
    draw_sprite(g->gameOver_word);
    display_score(g);
    draw_button(g->play_again_button);
    draw_button(g->return_mm_button);
    drawCursor(g->cursor);
  }


  if(get_game_state(g->st) == GAME){

    draw_background(g);
    draw_sprite(g->gun);
    draw_sprite(g->aim);
    draw_bullets(g);
    draw_ships(g->ships);
    display_score(g);
    display_progress_bar(g);
  }

}

//-------------------

void display_progress_bar(Game* g){

  switch(g->lb_progress){

    case 0:
      draw_sprite(g->lb_empty_bar);
      break;

    case 1:
      draw_sprite(g->lb_25_bar);
      break;

    case 2:
      draw_sprite(g->lb_50_bar);
      break;

    case 3:
      draw_sprite(g->lb_75_bar);
      break;

    case 4:
      draw_sprite(g->lb_full_bar);
      break;

    default:
      break;
  }
}

//-------------------

void end_game(Game* g){

  //saves the highscores in a text file (it is the first thing done, because even if something fails and terminates the program, the game still saves the highscores)
  delete_highscores(g->highscores);



  if(sys_irqdisable(&hook_id_mouse) != 0)
    return;


  uint8_t ackByte;

  do{
      if( issue_mouse_cmd(DIS_DATA_REP, &ackByte) != 0) //disables data reporting
          return;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return;
      
  }while(ackByte != ACK);


  if(sys_irqenable(&hook_id_mouse) != 0)
    return;

  
  mouse_unsubscribe_int();
  kbd_unsubscribe_int();
  timer_unsubscribe_int();

  delete_cursor(g->cursor);

  delete_bullets(g);

  for(int i = 0; i < 5; i++){

    free(g->red_bullets[i].bytes);
    free(g->green_bullets[i].bytes);
    free(g->blue_bullets[i].bytes);
    free(g->yellow_bullets[i].bytes);
    free(g->lightBeamBullets[i].bytes);
  }
  
  delete_ships(g->ships);

  delete_button(g->SP_button);
  delete_button(g->insts_button);
  delete_button(g->hs_button);
  delete_button(g->exit_button);
  delete_button(g->back_button);
  delete_button(g->play_again_button);
  delete_button(g->return_mm_button);

  destroy_sprite(g->title);
  destroy_sprite(g->gameOver_word);
  destroy_sprite(g->background);
  destroy_sprite(g->background_insts);

  destroy_sprite(g->lb_empty_bar);
  destroy_sprite(g->lb_25_bar);
  destroy_sprite(g->lb_50_bar);
  destroy_sprite(g->lb_75_bar);
  destroy_sprite(g->lb_full_bar);

  destroy_sprite(g->gun);
  destroy_sprite(g->aim);
  destroy_sprite(g->score);

  destroy_sprite(g->zero);
  destroy_sprite(g->one);
  destroy_sprite(g->two);
  destroy_sprite(g->three);
  destroy_sprite(g->four);
  destroy_sprite(g->five);
  destroy_sprite(g->six);
  destroy_sprite(g->seven);
  destroy_sprite(g->eight);
  destroy_sprite(g->nine);
  destroy_sprite(g->slash);
  destroy_sprite(g->dois_pontos);

  destroy_sprite(g->hs_number1);
  destroy_sprite(g->hs_number2);
  destroy_sprite(g->hs_number3);
  destroy_sprite(g->hs_number4);
  destroy_sprite(g->hs_number5);

  delete_st_machine(g->st);

  free(g);
  g = NULL;
}
