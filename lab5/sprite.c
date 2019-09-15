#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "sprite.h"
#include "video.h"

Sprite *create_sprite(const char *pic[], int x, int y,
int xspeed, int yspeed){

  Sprite* sp = (Sprite*) malloc(sizeof(Sprite));
  if(sp==NULL)
    return NULL;

  sp->map = read_xpm(pic, &(sp->width), &(sp->height));
  if(sp->map == NULL){
    free(sp);
    return NULL;
  }

  sp->x = x;
  sp->y = y;
  sp->xspeed = xspeed;
  sp->yspeed = yspeed;
  return sp;
}

int draw_sprite(Sprite* sp){

  for(int i = 0; i < sp->height; i++){

    //we have reached the limit of the screen
    if((unsigned) (sp->y + i) >= get_v_res())
      break;

    for(int j = 0; j < sp->width; j++){
      
      //we have reached the limit of the screen
      if((unsigned) (sp->x + j) >= get_h_res())
        break;
      
      //(sprite + i*width + j) -> to access the position w/ the correct color 
      if(color_pixel(sp->x + j, sp->y + i, *(sp->map + i*sp->width + j)) != 0){

        printf("Drawing of the pixmap failed!\n");
        return 1;
     }

    }

 }
  return 0;
}

int erase_sprite(Sprite* sp){

  for(int i = 0; i < sp->height; i++){

    //we have reached the limit of the screen
    if((unsigned) (sp->y + i) >= get_v_res())
      break;

    for(int j = 0; j < sp->width; j++){
      
      //we have reached the limit of the screen
      if((unsigned) (sp->x + j) >= get_h_res())
        break;
      
      //(sprite + i*width + j) -> to access the position w/ the correct color 
      if(color_pixel(sp->x + j, sp->y + i, 0) != 0){

        printf("Drawing of the pixmap failed!\n");
        return 1;
     }

    }

 }
  return 0;

}


void destroy_sprite(Sprite* sp){

    if(sp == NULL)
      return;

    if(sp->map)
      free(sp->map);

    free(sp);
    sp = NULL;
}
