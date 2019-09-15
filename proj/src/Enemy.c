#include <lcom/lcf.h>
#include "Enemy.h"
#include "video.h"
#include "projMacros.h"

struct enemy_t{

  char* pixmaps[5]; ///< pixmaps of all the spaceships (to create an animation)
  int currentPixmap; ///< index that shows the current pixmap of the array that is being used
  int x; ///< enemy's x coordinate
  int y; ///< enemy's y coordinate
  int xspeed; ///< enemy's speed in the x axis
  int yspeed; ///< enemy's speed in the y axis
  int height; ///< enemy's height
  int width; ///< enemy's width
  Color color; ///< color of the enemy spaceship
};


Enemy* create_enemy(xpm_image_t spaceship0, xpm_image_t spaceship1, xpm_image_t spaceship2, xpm_image_t spaceship3, xpm_image_t spaceship4, int x, int y, int xspeed, int yspeed, Color c){

  Enemy* enemy = (Enemy*) malloc(sizeof(Enemy));
  if(enemy == ENEMY_ALLOC_FAILED)
    return ENEMY_ALLOC_FAILED;

  //note: all pixmaps have the same width and height
  enemy->pixmaps[0] = (char*) spaceship0.bytes;  
  enemy->pixmaps[1] = (char*) spaceship1.bytes;
  enemy->pixmaps[2] = (char*) spaceship2.bytes;
  enemy->pixmaps[3] = (char*) spaceship3.bytes;
  enemy->pixmaps[4] = (char*) spaceship4.bytes;

  enemy->currentPixmap = 0;
  enemy->x = x;
  enemy->y = y;
  enemy->height = spaceship0.height;
  enemy->width = spaceship0.width; 
  enemy->color = c;
  enemy->xspeed = xspeed;
  enemy->yspeed = yspeed;

  return enemy;
}

//-------------------

void delete_enemy(Enemy* enemy){
    
    if(enemy == NULL)
        return;

    free(enemy);
    enemy = NULL;
}

//-------------------

int get_enemy_x(Enemy* enemy){

  return enemy->x;
}

//-------------------

int get_enemy_y(Enemy* enemy){

  return enemy->y;
}

//-------------------

int get_enemy_width(Enemy* enemy){

  return enemy->width;
}

//-------------------

int get_enemy_height(Enemy* enemy){

  return enemy->height;
}

//-------------------

Color get_enemy_color(Enemy* enemy){

  return enemy->color;
}

//-------------------

char* get_enemy_current_pixmap(Enemy* enemy){

  return enemy->pixmaps[enemy->currentPixmap];
}

//-------------------

void draw_enemy(Enemy* enemy){
  draw_pixmap_db(enemy->pixmaps[enemy->currentPixmap], enemy->x, enemy->y, enemy->width, enemy->height);
}

//-------------------

void update_enemy(Enemy* enemy, bool move_down){

  enemy->x += enemy->xspeed;
  
  if(move_down)
    enemy->y += enemy->yspeed;

  if(((enemy->x + enemy->width) >= ENEMY_X_MAX_VAL) || (enemy->x <= ENEMY_X_MIN_VAL)){
    enemy->xspeed = -enemy->xspeed;
  }
  
}

//-------------------

void animate_enemy(Enemy* enemy){

  enemy->currentPixmap++;
  if(enemy->currentPixmap >= 5)
    enemy->currentPixmap = 0;
}
