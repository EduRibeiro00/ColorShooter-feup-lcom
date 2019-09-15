#include <lcom/lcf.h>
#include "Bullet.h"
#include "video.h"
#include "xpms.h"
#include "projMacros.h"

struct bullet_t{

  int x, y; ///< bullet's leftmost pixel coordinates
  int xspeed, yspeed; ///< current bullet speeds
  int width, height; ///< width and height of the bullet
  
  char* red_ammo[5]; ///< pixmaps of the red bullets
  char* green_ammo[5]; ///< pixmaps of the green bullets
  char* blue_ammo[5]; ///< pixmaps of the blue bullets
  char* yellow_ammo[5]; ///< pixmaps of the yellow bullets
  
  int cur_animation; ///< indicates what is the current bullet pixmap to be used
  bool back; ///< indicates if the animation of the bullet is going from image 0 to 4 (false), or from image 4 to 0 (true)
  
  Color bullet_color; ///< color of the bullet
  bool launched; ///< indicates if the bullet was launched or not
};



Bullet* create_bullet(xpm_image_t red[], xpm_image_t green[], xpm_image_t blue[], xpm_image_t yellow[], int arraySize, int x, int y, int xspeed, int yspeed, Color initialColor, int anim_start){


  Bullet* b = (Bullet*) malloc(sizeof(Bullet));
  if(b == BULLET_ALLOC_FAILED)
    return BULLET_ALLOC_FAILED;

  b->x = x;
  b->y = y;
  b->xspeed = xspeed;
  b->yspeed = yspeed;

  //all the bullets have the same width and height
  b->width = red[0].width;
  b->height = red[0].height;

  for(int i = 0; i < arraySize; i++){

    b->red_ammo[i] = (char*) red[i].bytes;
    b->green_ammo[i] = (char*) green[i].bytes;
    b->blue_ammo[i] = (char*) blue[i].bytes;
    b->yellow_ammo[i] = (char*) yellow[i].bytes;
  }
  
  b->back = false;
  b->cur_animation = anim_start;

  b->bullet_color = initialColor;
  b->launched = false; 

  return b;
}

//-------------------

Color get_bullet_color(Bullet* b){
  return b->bullet_color;
}

//-------------------

void delete_bullet(Bullet* b){

  if(b == NULL)
    return;

  free(b);
  b = NULL;
}

//-------------------

int draw_bullet(Bullet* b){

  switch(b->bullet_color){

    case COLOR_RED:
      return draw_pixmap_db(b->red_ammo[b->cur_animation], b->x, b->y, b->width, b->height);

    case COLOR_GREEN:
      return draw_pixmap_db(b->green_ammo[b->cur_animation], b->x, b->y, b->width, b->height);

    case COLOR_BLUE:
      return draw_pixmap_db(b->blue_ammo[b->cur_animation], b->x, b->y, b->width, b->height);

    case COLOR_YELLOW:
      return draw_pixmap_db(b->yellow_ammo[b->cur_animation], b->x, b->y, b->width, b->height);

    default:
      return 1;
  }
}

//-------------------

void animate_bullet(Bullet* b){

  if(b->cur_animation == 4)
    b->back = true;
  
  if(b->cur_animation == 0)
    b->back = false;

  if(b->back)
    b->cur_animation--;
  else b->cur_animation++;
}

//-------------------

int get_x(Bullet* b){
  return b->x;
}

//-------------------

int get_y(Bullet* b){
  return b->y;
}

//-------------------

bool get_launched(Bullet* b){

  return b->launched;
}

//-------------------

int get_width(Bullet* b){

  return b->width;
}

//-------------------

int get_height(Bullet* b){

  return b->height;
}

//-------------------

int get_cur_animation(Bullet* b){

  return b->cur_animation;
}

//-------------------

char* get_current_pixmap(Bullet* b){

  if(b->bullet_color == COLOR_RED)
    return b->red_ammo[b->cur_animation];

  else if(b->bullet_color == COLOR_GREEN)
    return b->green_ammo[b->cur_animation];

  else if(b->bullet_color == COLOR_BLUE)
    return b->blue_ammo[b->cur_animation];

  else if(b->bullet_color == COLOR_YELLOW)
    return b->yellow_ammo[b->cur_animation];

  else return NULL; //invalid value of bullet color
}

//-------------------

int change_ammo(Bullet* b, uint8_t key_code){

  switch(key_code){

    case RED_AMMO_MAKE:
      b->bullet_color = COLOR_RED;
      break;
    case BLUE_AMMO_MAKE:
      b->bullet_color = COLOR_BLUE;
      break;
    case GREEN_AMMO_MAKE:
      b->bullet_color = COLOR_GREEN;
      break;
    case YELLOW_AMMO_MAKE:
      b->bullet_color = COLOR_YELLOW;
      break;
    default:
      return 1;
  }
  return 0;
}

//-------------------

int update_bullet_pos(Bullet* b){

    b->x += b->xspeed;
    b->y += b->yspeed;

    return 0;
}

//-------------------

void launch_bullet(Bullet* b, Sprite* aim){

  if((b->xspeed != 0) || (b->yspeed != 0)) //if bullet was already launched, don't do anything
    return;

  int yspeed = get_st_y(aim) - b->y;
  int xspeed = get_st_x(aim) - b->x;
  //yspeed /= 8;
  //xspeed /= 15;

  yspeed /= 8;
  xspeed /= 8;

  if((xspeed >= -5) && (xspeed <= 5))
    yspeed -= 2;

  b->xspeed = xspeed;
  b->yspeed = yspeed;
  
  b->launched = true;
}

//-------------------

void launch_bullet_light_beam(Bullet* b, Sprite* aim){
  
  if((b->xspeed != 0) || (b->yspeed != 0)) //if bullet was already launched, don't do anything
    return;

  int yspeed = get_st_y(aim) - b->y;
  int xspeed = get_st_x(aim) - b->x;

  yspeed /= 5;
  xspeed /= 5;

  if((xspeed >= -15) && (xspeed <= 15))
    yspeed -= 10;


  b->xspeed = xspeed;
  b->yspeed = yspeed;
  
  b->launched = true;
}

//-------------------

bool bullet_oob(Bullet* b){
  
  if(((b->x + b->width) < 0) || (b->x > (int) get_h_res()))
    return true;

  if(((b->y + b->height) < 0) || (b->y > (int) get_v_res()))
    return true;

  return false;
}
