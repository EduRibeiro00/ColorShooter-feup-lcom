#include <lcom/lcf.h>
#include "Ships.h"
#include "xpms.h"

struct ships_t{

Enemy* enemies[MAX_NUM_SHIPS]; ///< array with the current enemies on screen
int enemies_size; ///< size of the enemies array
int ships_yspeed; ///< current y speed value for the enemies created
int spawn_rate; ///< spawn rate of the enemy spaceships
int ships_xspeed_min, ships_xspeed_max; ///< indicate the max and min horizontal speed that a new spaceship can have
bool move_down; ///< indicates if the ships should go down in the current timer interrupt

/* different images for the enemies (one array for each color, 5 different images) */
xpm_image_t red_spaceships[5];
xpm_image_t green_spaceships[5];
xpm_image_t blue_spaceships[5];
xpm_image_t yellow_spaceships[5];


xpm_image_t explosion_images[10]; ///< array with the explosion images

Explosion* explosions[MAX_NUM_SHIPS]; ///< array with the current explosions on screen
int explosions_size; ///< size of the explosions array
};


Ships* create_ships(){

  Ships* ships = (Ships*) malloc(sizeof(Ships));
  if(ships == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  xpm_image_t img0, img1, img2, img3, img4;
  if(xpm_load(red_ship0_xpm, XPM_8_8_8, &img0) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(red_ship1_xpm, XPM_8_8_8, &img1) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(red_ship2_xpm, XPM_8_8_8, &img2) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(red_ship3_xpm, XPM_8_8_8, &img3) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(red_ship4_xpm, XPM_8_8_8, &img4) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  ships->red_spaceships[0] = img0;
  ships->red_spaceships[1] = img1;
  ships->red_spaceships[2] = img2;
  ships->red_spaceships[3] = img3;
  ships->red_spaceships[4] = img4;

  if(xpm_load(green_ship0_xpm, XPM_8_8_8, &img0) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(green_ship1_xpm, XPM_8_8_8, &img1) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(green_ship2_xpm, XPM_8_8_8, &img2) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(green_ship3_xpm, XPM_8_8_8, &img3) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(green_ship4_xpm, XPM_8_8_8, &img4) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  ships->green_spaceships[0] = img0;
  ships->green_spaceships[1] = img1;
  ships->green_spaceships[2] = img2;
  ships->green_spaceships[3] = img3;
  ships->green_spaceships[4] = img4;

  if(xpm_load(blue_ship0_xpm, XPM_8_8_8, &img0) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(blue_ship1_xpm, XPM_8_8_8, &img1) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(blue_ship2_xpm, XPM_8_8_8, &img2) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(blue_ship3_xpm, XPM_8_8_8, &img3) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(blue_ship4_xpm, XPM_8_8_8, &img4) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  ships->blue_spaceships[0] = img0;
  ships->blue_spaceships[1] = img1;
  ships->blue_spaceships[2] = img2;
  ships->blue_spaceships[3] = img3;
  ships->blue_spaceships[4] = img4;

  if(xpm_load(yellow_ship0_xpm, XPM_8_8_8, &img0) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(yellow_ship1_xpm, XPM_8_8_8, &img1) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(yellow_ship2_xpm, XPM_8_8_8, &img2) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(yellow_ship3_xpm, XPM_8_8_8, &img3) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(yellow_ship4_xpm, XPM_8_8_8, &img4) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  ships->yellow_spaceships[0] = img0;
  ships->yellow_spaceships[1] = img1;
  ships->yellow_spaceships[2] = img2;
  ships->yellow_spaceships[3] = img3;
  ships->yellow_spaceships[4] = img4;



  if(xpm_load(explosion0_xpm, XPM_8_8_8, &img0) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion1_xpm, XPM_8_8_8, &img1) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion2_xpm, XPM_8_8_8, &img2) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion3_xpm, XPM_8_8_8, &img3) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion4_xpm, XPM_8_8_8, &img4) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  ships->explosion_images[0] = img0;
  ships->explosion_images[1] = img1;
  ships->explosion_images[2] = img2;
  ships->explosion_images[3] = img3;
  ships->explosion_images[4] = img4;


  if(xpm_load(explosion5_xpm, XPM_8_8_8, &img0) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion6_xpm, XPM_8_8_8, &img1) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion7_xpm, XPM_8_8_8, &img2) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion8_xpm, XPM_8_8_8, &img3) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  if(xpm_load(explosion9_xpm, XPM_8_8_8, &img4) == SHIPS_ALLOC_FAILED)
    return SHIPS_ALLOC_FAILED;

  ships->explosion_images[5] = img0;
  ships->explosion_images[6] = img1;
  ships->explosion_images[7] = img2;
  ships->explosion_images[8] = img3;
  ships->explosion_images[9] = img4;


  ships->explosions_size = 0;
  ships->enemies_size = 0;
  ships->ships_yspeed = ENEMY_YSPEED_INIT;
  ships->move_down = false;
  ships->spawn_rate = INITIAL_SPAWN_RATE;
  ships->ships_xspeed_min = ENEMY_XSPEED_MIN;
  ships->ships_xspeed_max = ENEMY_XSPEED_MAX;

  return ships;
}

//-------------------

void reset_ships(Ships* ships){

  for(int i = 0; i < ships->enemies_size; i++){

    delete_enemy(ships->enemies[i]);
  }

  for(int j = 0; j < ships->explosions_size; j++){

    delete_explosion(ships->explosions[j]);
  }

  ships->enemies_size = 0;
  ships->explosions_size = 0;
}

//-------------------

void delete_ships(Ships* ships){

  if(ships == NULL)
    return;

  reset_ships(ships);

  for(int i = 0; i < 5; i++){

    free(ships->red_spaceships[i].bytes);
    free(ships->green_spaceships[i].bytes);
    free(ships->blue_spaceships[i].bytes);
    free(ships->yellow_spaceships[i].bytes);
  }

  for(int j = 0; j < 10; j++){

    free(ships->explosion_images[j].bytes);
  }

  free(ships);
  ships = NULL;
}

//-------------------

void add_enemy(Ships* ships){

    if(ships->enemies_size == MAX_NUM_SHIPS) //no more enemies allowed
      return;

    Color randColor = rand() % COLOR_SIZE; //gets a random color
    
    int randomX = (rand() % ((ENEMY_X_MAX_VAL - 100) - (ENEMY_X_MIN_VAL + 10) + 1)) + (ENEMY_X_MIN_VAL + 10);  //generates a random x spawn for the enemy

    int randomXSpeed = (rand() % (ships->ships_xspeed_max - ships->ships_xspeed_min + 1)) + ships->ships_xspeed_min;  //generates a random x speed for the enemy


    Enemy* newEnemy;

    switch(randColor){

      case COLOR_RED:
        newEnemy = create_enemy(ships->red_spaceships[0], ships->red_spaceships[1], ships->red_spaceships[2], ships->red_spaceships[3], ships->red_spaceships[4], randomX, ENEMY_SPAWN_Y, randomXSpeed, ships->ships_yspeed, randColor);

        ships->enemies[ships->enemies_size] = newEnemy;
        ships->enemies_size++;  
        break;

      case COLOR_GREEN:
        newEnemy = create_enemy(ships->green_spaceships[0], ships->green_spaceships[1], ships->green_spaceships[2], ships->green_spaceships[3], ships->green_spaceships[4], randomX,ENEMY_SPAWN_Y, randomXSpeed, ships->ships_yspeed, randColor);

        ships->enemies[ships->enemies_size] = newEnemy;
        ships->enemies_size++; 
        break;

      case COLOR_BLUE:
        newEnemy = create_enemy(ships->blue_spaceships[0], ships->blue_spaceships[1],   ships->blue_spaceships[2], ships->blue_spaceships[3], ships->blue_spaceships[4], randomX,ENEMY_SPAWN_Y, randomXSpeed, ships->ships_yspeed, randColor);

        ships->enemies[ships->enemies_size] = newEnemy;
        ships->enemies_size++;
        break;

      case COLOR_YELLOW:
        newEnemy = create_enemy(ships->yellow_spaceships[0], ships->yellow_spaceships[1],   ships->yellow_spaceships[2], ships->yellow_spaceships[3], ships->yellow_spaceships[4], randomX, ENEMY_SPAWN_Y, randomXSpeed, ships->ships_yspeed, randColor);

        ships->enemies[ships->enemies_size] = newEnemy;
        ships->enemies_size++;
        break;

      default:
        break;
    }

}

//-------------------

void add_explosion(Ships* ships, int x, int y){

  if(ships->explosions_size == MAX_NUM_SHIPS) //no more explosions allowed
    return;

  Explosion* newExplosion = create_explosion(ships->explosion_images, 10, x, y);

  ships->explosions[ships->explosions_size] = newExplosion;
  ships->explosions_size++;

}

//-------------------

void draw_ships(Ships* ships){

  for(int i = 0; i < ships->enemies_size; i++)
    draw_enemy(ships->enemies[i]);

  for(int j = 0; j < ships->explosions_size; j++)
    draw_explosion(ships->explosions[j]);
}

//-------------------

void remove_ship(Ships* ships, int index){

  if(index >= ships->enemies_size)
    return;

  for(int i = index; i < ships->enemies_size - 1; i++){
    Enemy* temp = ships->enemies[i];
    ships->enemies[i] = ships->enemies[i + 1];
    ships->enemies[i + 1] = temp;
  }

  delete_enemy(ships->enemies[ships->enemies_size - 1]);

  ships->enemies_size--;
}

//-------------------

void remove_explosion(Ships* ships, int index){

  if(index >= ships->explosions_size)
    return;

  for(int i = index; i < ships->explosions_size - 1; i++){
    Explosion* temp = ships->explosions[i];
    ships->explosions[i] = ships->explosions[i + 1];
    ships->explosions[i + 1] = temp;
  }

  delete_explosion(ships->explosions[ships->explosions_size - 1]);

  ships->explosions_size--;
}

//-------------------

bool player_lost(Ships* ships){

  for(int i = 0; i < ships->enemies_size; i++){

    if((get_enemy_y(ships->enemies[i]) + get_enemy_height(ships->enemies[i])) >= ENEMY_Y_LOST)
      return true;
  }

  return false;
}

//-------------------

void update_ships(Ships* ships){

  for(int i = 0; i < ships->enemies_size; i++)
    update_enemy(ships->enemies[i], ships->move_down);

}

//-------------------

void animate_ships(Ships* ships){

  for(int i = 0; i < ships->enemies_size; i++)
    animate_enemy(ships->enemies[i]);

  for(int j = 0; j < ships->explosions_size; j++){

    if(animate_explosion(ships->explosions[j])){

      remove_explosion(ships, j);
      j--;
    }
  }
}

//-------------------

void toggle_move_down(Ships* ships){
  if(ships->move_down)
    ships->move_down = false;
  else ships->move_down = true;
}

//-------------------

void reset_difficulty(Ships* ships){
  ships->ships_yspeed = ENEMY_YSPEED_INIT;
  ships->spawn_rate = INITIAL_SPAWN_RATE;
  ships->ships_xspeed_min = ENEMY_XSPEED_MIN;
  ships->ships_xspeed_max = ENEMY_XSPEED_MAX;
}

//-------------------

Enemy** get_enemies(Ships* ships){

  return ships->enemies;
}

//-------------------

void adjust_difficulty(Ships* ships, int dif_level){

  switch (dif_level){

    case 1:
      ships->ships_yspeed++;
      ships->spawn_rate -= sys_hz();
      ships->ships_xspeed_min += 2;
      ships->ships_xspeed_max++;
      break;

    case 2:
      ships->spawn_rate -= sys_hz();
      break;

    case 3:
      ships->ships_yspeed++;
      break;
  
    default:
      break;
  }
}

//-------------------

int get_spawn_rate(Ships* ships){
  
  return ships->spawn_rate;
}

//-------------------

int get_enemies_size(Ships* ships){

  return ships->enemies_size;
}
