#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "sprite.h"
#include "video.h"
#include "projMacros.h"


struct sprite_t{
  int x,y;             ///< current sprite position
  int width, height;   ///< sprite dimensions
  int xspeed, yspeed;  ///< current speeds in the x and y direction
  char *map;           ///< the sprite pixmap
};


Sprite *create_sprite(xpm_string_t pic[], int x, int y,
int xspeed, int yspeed){

  xpm_image_t img;
  if(xpm_load(pic, XPM_8_8_8, &img) == SPRITE_ALLOC_FAILED)
    return SPRITE_ALLOC_FAILED;

  Sprite* sp = (Sprite*) malloc(sizeof(Sprite));
  if(sp == SPRITE_ALLOC_FAILED)
    return SPRITE_ALLOC_FAILED;

  sp->x = x;
  sp->y = y;
  sp->xspeed = xspeed;
  sp->yspeed = yspeed;
  sp->width = img.width;
  sp->height = img.height;
  sp->map = (char*) img.bytes;
  return sp;
}

//-------------------

int update_aim(Sprite* aim, struct packet pp){

  aim->x += pp.delta_x;

  if(aim->x < AIM_X_MIN_VAL)
    aim->x = AIM_X_MIN_VAL;

  if((aim->x + aim->width) > AIM_X_MAX_VAL)
    aim->x = (AIM_X_MAX_VAL - aim->width);

  return 0;
}

//-------------------

int get_st_x(Sprite* st){
  return st->x;
}

//-------------------

int get_st_y(Sprite* st){
  return st->y;
}

//-------------------

int get_st_width(Sprite* st){
  return st->width;
}

//-------------------

int get_st_height(Sprite* st){
  return st->height;
}

//-------------------

char* get_st_map(Sprite* st){
  return st->map;
}

//-------------------

int draw_sprite(Sprite* sp){

  return draw_pixmap_db(sp->map, sp->x, sp->y, sp->width, sp->height);
}

//-------------------

int draw_sprite_coords(Sprite* sp, int x, int y){

  return draw_pixmap_db(sp->map, x, y, sp->width, sp->height);
}

//-------------------

void destroy_sprite(Sprite* sp){

    if(sp == NULL)
      return;

    if(sp->map)
      free(sp->map);

    free(sp);
    sp = NULL;
}
